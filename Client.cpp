#include "Client.hpp"

#include <iostream>

using namespace std;


// Constructor

Client::Client(ClientOpsIF* c, Broker& br)
    : broker(br),
      cif(c) {


    // Nombre por defecto

    user = "undefined";
    
    
    // Despacho de mensajes hasta recepcion de DISCONNECT

    th = std::thread( &Client::dispatch, this );

    th.detach();

}



// Destructor

Client::~Client() {


    // Es necesario remover las subscripciones y retained topics que quedan en el broker (por si no se solicito una desconexion)
    
    for( auto sub : subscriptions )
	broker.removeSubscription( sub );
 
    for( auto rt : topics )
	broker.removeRetainedTopic( rt );   
    

    // Join al thread encargado del dispatch de mensajes
    
    if( th.joinable() )
	th.join();

}



// Dispach de mensajes

void Client::dispatch() {


    bool proccess(true);
    

    while( proccess ) {


	// Lectura de mensajes de cola

	Message* msg;

	recvQueue.get( &msg );


	// Tipo de mensaje

	const Message::Type mtype = msg->getType();
	

	switch( mtype ) {


	case Message::Type::CONNECT:

	    processConnect(msg);
	    
	    break;


	case Message::Type::DISCONNECT:

	    proccess = false;

	    cout << "Desconexion de usuario [" << user << "]" << endl;

	    processDisconnect(msg);
	    
	    break;


	case Message::Type::SUBSCRIBE:

	    processSubscribe(msg);
	    
	    break;


	case Message::Type::UNSUBSCRIBE:

	    processUnsubscribe(msg);

	    break;


	case Message::Type::PUBLISH:

	    processPublish(msg);

	    break;
	    

	default:

	    break;

	    
	}
	

    }

}





// Procesamiento de mensajes tipo CONNECT

void Client::processConnect( const Message* msg ) {

    const ConnectMsg* cmsg = dynamic_cast<const ConnectMsg*>(msg);

    user = cmsg->user();

    cout << "Solicitud de conexion de usuario [" + user + "]\n";
    
    broker.connReq( this );
	    
}




// Procesamiento de mensajes tipo DISCONNECT

void Client::processDisconnect( const Message* msg ) {


    // Es necesario remover las subscripciones y retained topics que quedan en el broker
    
    for( auto sub : subscriptions )
	broker.removeSubscription( sub );

    for( auto rt : topics )
	broker.removeRetainedTopic( rt );



    // Pedido de desconexion al broker
    
    broker.removeClient( this );
    

}



// Procesamiento de mensajes tipo SUBSCRIBE

void Client::processSubscribe( const Message* msg ) {

    
    const SubscribeMsg* smsg = dynamic_cast<const SubscribeMsg*>(msg);

    cout << "Subscripcion de usuario [" + user + "] en topico [" + smsg->getTopic() + "]\n";



    // Incorporacion al contenedor local

    bool find(false);

    for( auto sub : subscriptions ) {

	if( sub->topic == smsg->getTopic() )
	    find = true;	    

    }


    if( !find ) {

	Subscription* sub = new Subscription{ smsg->getTopic(), this };
	
	subscriptions.insert( sub );
	
    	broker.addSubscription( sub );
	
    }
    
    
}
    


// Procesamiento de mensajes tipo UNSUBSCRIBE

void Client::processUnsubscribe( const Message* msg ) {
    

    const UnsubscribeMsg* umsg = dynamic_cast<const UnsubscribeMsg *>(msg);

    cout << "Desubscripcion de usuario [" + user + "] en topico [" + umsg->getTopic() + "]\n";

    

    // Remocion de la subscripcion (local y broker)
    
    for( auto sub : subscriptions ) {
	
	if( sub->topic == umsg->getTopic() ) {

	    subscriptions.erase( sub );

	    broker.removeSubscription( sub );
	    
	}

    }

}




// Procesamiento de mensajes tipo PUBLISH

void Client::processPublish( const Message* msg ) {
    

    const PublishMsg* pmsg = dynamic_cast<const PublishMsg*>(msg);

    cout << "Publicacion de usuario [" + user + "] en topico [" + pmsg->getTopic() + "]\n";


    // Si es un topico retenido, agregar a contenedor. Sino distribuir directamente a subscriptores
    
    if( pmsg->isRetained() ) {


	bool findTopic(false);

	for(auto rtopics : topics) {

	    if( rtopics->topic == pmsg->getTopic() ) {

		rtopics->value = pmsg->getValue();

		findTopic = true;
		
	    }

	}
	

	if( !findTopic ) {

	    RetainedTopic* rt = new RetainedTopic{ pmsg->getTopic(), pmsg->getValue(), this };
	    
	    topics.insert( rt );

	    broker.updateRTopic( rt );
	    
	}
	

    }


    // Distribucion a todos los subscriptores

    broker.sendTopic( pmsg->getTopic(), pmsg->getValue() );
    

}





// Envio de mensajes. Incorporacion a la cola

void Client::sendMsg( const Message& msg ) {
    
    recvQueue.put( msg.clone() );
    
}
