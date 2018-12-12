#include "Client.hpp"

#include "threadStream.hpp"

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

    if( th.joinable() )
	th.join();

}




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

	    thout << "Desconexion de usuario [" << user << "]" << endl;
	    
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

    thout << "Solicitud de conexion de usuario [" << user << "]" << endl;
	    
}




// Procesamiento de mensajes tipo DISCONNECT

void Client::processDisconnect( const Message* msg ) {


    // Es necesario remover las subscripciones y retained topics que quedan en el broker
    
    for( auto sub : subscriptions )
	broker.removeSubscription( sub );	    

    

}



// Procesamiento de mensajes tipo SUBSCRIBE

void Client::processSubscribe( const Message* msg ) {

    
    const SubscribeMsg* smsg = dynamic_cast<const SubscribeMsg*>(msg);

    thout << "Subscripcion de usuario [" << user << "] en topico [" << smsg->getTopic() << "]: ";


    // Incorporacion al contenedor local
    
    Subscription sub{ smsg->getTopic(), this };

    if( subscriptions.find(&sub) == subscriptions.end() ) {
	
    	subscriptions.insert( &sub );	

    	thout << "OK" << endl;


    	// Incorporacion al broker

    	broker.addSubscription( &sub );	

    }
    
}
    


// Procesamiento de mensajes tipo UNSUBSCRIBE

void Client::processUnsubscribe( const Message* msg ) {

    const UnsubscribeMsg* umsg = dynamic_cast<const UnsubscribeMsg *>(msg);

    thout << "Desubscripcion de usuario [" << user << "] en topico [" << umsg->getTopic() << "]" << endl;


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

    thout << "Publicacion de usuario [" << user << "] en topico [" << pmsg->getTopic() << "]" << endl;


    // Si es un topico retenido, agregar a contenedor. Sino distribuir directamente a subscriptores
    
    if( pmsg->isRetained() ) {

	RetainedTopic rt{ pmsg->getTopic(), pmsg->getValue(), this };

	bool findTopic(false);

	for(auto rtopics : topics) {

	    if( rtopics->topic == rt.topic ) {

		rtopics->value = rt.value;

		findTopic = true;

	    }

	}

	if(!findTopic)
	    topics.insert(&rt);

	
	broker.updateRTopic( &rt );

    }


    // Distribucion a todos los subscriptores

    broker.sendTopic( pmsg->getTopic(), pmsg->getValue() );
    

}





// Envio de mensajes. Incorporacion a la cola

void Client::sendMsg( const Message& msg ) {
    
    recvQueue.put( msg.clone() );
    
}
