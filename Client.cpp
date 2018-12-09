#include "Client.hpp"

#include <iostream>

using namespace std;


// Constructor

Client::Client(ClientOpsIF* c, Broker& br) : broker(br) {

    
    cif = c;


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


	// Tipo de mensaje. Declaracion de variables para uso en switch

	const Message::Type mtype = msg->getType();
	

	switch( mtype ) {


	case Message::Type::CONNECT:

	    processConnect(msg);
	    
	    break;


	case Message::Type::DISCONNECT:

	    proccess = false;

	    cout << "Desconexion de usuario [" << user << "]" << endl;
	    
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

    cout << "Solicitud de conexion de usuario [" << user << "]" << endl;
	    
}



// Procesamiento de mensajes tipo SUBSCRIBE

void Client::processSubscribe( const Message* msg ) {

    const SubscribeMsg* smsg = dynamic_cast<const SubscribeMsg*>(msg);

    cout << "Subscripcion de usuario [" << user << "] en topico [" << smsg->getTopic() << "]: ";


    // Incorporacion al contenedor local
    
    Subscription sub{ smsg->getTopic(), this };

    if( subscriptions.find(&sub) == subscriptions.end() ) {
	
    	subscriptions.insert( &sub );	

    	cout << "OK" << endl;


    	// Incorporacion al broker

    	broker.addSubscription( &sub );	

    }

    else {

    	cout << "Ya existe" << endl;

    }

    

}
    


// Procesamiento de mensajes tipo UNSUBSCRIBE

void Client::processUnsubscribe( const Message* msg ) {

    const UnsubscribeMsg* umsg = dynamic_cast<const UnsubscribeMsg *>(msg);

    cout << "Desubscripcion de usuario [" << user << "] en topico [" << umsg->getTopic() << "]" << endl;


    // Remocion del contenedor local
    
    Subscription sub{ umsg->getTopic(), this };

    if( subscriptions.find(&sub) != subscriptions.end() ) {
	
	subscriptions.erase( &sub );

	broker.removeSubscription( &sub );	

    }

    

}




// Procesamiento de mensajes tipo PUBLISH

void Client::processPublish( const Message* msg ) {

    const PublishMsg* pmsg = dynamic_cast<const PublishMsg*>(msg);

    cout << "Publicacion de usuario [" << user << "] en topico [" << pmsg->getTopic() << "]" << endl;


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

}





// Envio de mensajes. Incorporacion a la cola

void Client::sendMsg( const Message& msg ) {
    
    recvQueue.put( msg.clone() );
    
}
