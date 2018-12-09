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








// Procesamiento de mensajes tipo PUBLISH

void Client::processPublish( const Message* msg ) {

    const PublishMsg* pmsg = dynamic_cast<const PublishMsg*>(msg);

    cout << "Publicacion de usuario [" << user << "] en topico [" << pmsg->getTopic() << "]" << endl;

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

    cout << "Subscripcion de usuario [" << user << "] en topico [" << smsg->getTopic() << "]" << endl;

}
    


// Procesamiento de mensajes tipo UNSUBSCRIBE

void Client::processUnsubscribe( const Message* msg ) {

    const UnsubscribeMsg* umsg = dynamic_cast<const UnsubscribeMsg *>(msg);

    cout << "Desubscripcion de usuario [" << user << "] en topico [" << umsg->getTopic() << "]" << endl;

}









// void Client::dispatch() {

//     Message* msg;

//     recvQueue.get( &msg );


//     // El primer mensaje tiene que ser de conexion

//     if( msg->getType() == Message::Type::CONNECT ) {


// 	// Hay que hacer la conexion correcta y enviar un ConnAck
	
// 	ConnectMsg* clientMsg = (ConnectMsg*) msg;

// 	cout << "Conexion del cliente " << clientMsg->user() << endl;


	
// 	// Procesamiento de mensajes    
    
// 	while( msg->getType() != Message::Type::DISCONNECT ) {   

	    
// 	    recvQueue.get( &msg );


// 	    // Mensaje de publicacion
	    
// 	    if( msg->getType() == Message::Type::PUBLISH ) {

// 	    	PublishMsg* pmsg = (PublishMsg *) msg;

// 	    	cout << "Publicacion de usuario [" << clientMsg->user() << "] en topico [" << pmsg->getTopic() << "]" << endl;

// 		if( pmsg->isRetained() ) {

// 		    bool find(false);

// 		    for( auto &r : topics ) {

// 			if( r->topic == pmsg->getTopic() ) {
			    
// 			    r->value = pmsg->getValue();

// 			    find = true;

// 			}

// 		    }

// 		    if( !find ) {
			
// 		    	// topics.push_back( new RetainedTopic{ topic = pmsg->getTopic(), value = pmsg->getValue(), *owner = this } );
// 		    	topics.push_back( new RetainedTopic{ pmsg->getTopic(), pmsg->getValue(), this } );			
			
// 		    }

// 		}

// 	    }



// 	    // Mensaje de subscripcion

// 	    if( msg->getType() == Message::Type::SUBSCRIBE ) {

// 	    	SubscribeMsg* pmsg = (SubscribeMsg *) msg;

// 		cout << "Subscripcion de usuario [" << clientMsg->user() << "] en topico [" << pmsg->getTopic() << "]" << endl;

// 	    }


	    
// 	    // Mensaje de desubscripcion

// 	    if( msg->getType() == Message::Type::UNSUBSCRIBE ) {

// 		UnsubscribeMsg* pmsg = (UnsubscribeMsg *) msg;

// 		cout << "Desubscripcion de usuario [" << clientMsg->user() << "] en topico [" << pmsg->getTopic() << "]" << endl;

// 	    }	    

	    
// 	}

	


// 	cout << "Desconexion del cliente " << clientMsg->user() << endl;

//     }    

// }





// Envio de mensajes. Incorporacion a la cola

void Client::sendMsg( const Message& msg ) {
    
    recvQueue.put( msg.clone() );
    
}
