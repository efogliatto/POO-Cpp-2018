#include "Client.hpp"

#include <iostream>

using namespace std;


// Constructor

Client::Client(ClientOpsIF* c) {

    
    cif = c;


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

    Message* msg;

    recvQueue.get( &msg );


    // El primer mensaje tiene que ser de conexion

    if( msg->getType() == Message::Type::CONNECT ) {


	// Hay que hacer la conexion correcta y enviar un ConnAck
	
	ConnectMsg* clientMsg = (ConnectMsg*) msg;

	cout << "Conexion del cliente " << clientMsg->user() << endl;


	
	// Procesamiento de mensajes    
    
	while( msg->getType() != Message::Type::DISCONNECT ) {   

	    
	    recvQueue.get( &msg );


	    // Mensaje de publicacion
	    
	    if( msg->getType() == Message::Type::PUBLISH ) {

	    	PublishMsg* pmsg = (PublishMsg *) msg;

	    	cout << "Publicacion de usuario [" << clientMsg->user() << "] en topico [" << pmsg->getTopic() << "]" << endl;

		if( pmsg->isRetained() ) {

		    bool find(false);

		    for( auto &r : topics ) {

			if( r->topic == pmsg->getTopic() ) {
			    
			    r->value = pmsg->getValue();

			    find = true;

			}

		    }

		    if( !find ) {
			
		    	// topics.push_back( new RetainedTopic{ topic = pmsg->getTopic(), value = pmsg->getValue(), *owner = this } );
		    	topics.push_back( new RetainedTopic{ pmsg->getTopic(), pmsg->getValue(), this } );			
			
		    }

		}

	    }



	    // Mensaje de subscripcion

	    if( msg->getType() == Message::Type::SUBSCRIBE ) {

	    	SubscribeMsg* pmsg = (SubscribeMsg *) msg;

		cout << "Subscripcion de usuario [" << clientMsg->user() << "] en topico [" << pmsg->getTopic() << "]" << endl;

	    }


	    
	    // Mensaje de desubscripcion

	    if( msg->getType() == Message::Type::UNSUBSCRIBE ) {

		UnsubscribeMsg* pmsg = (UnsubscribeMsg *) msg;

		cout << "Desubscripcion de usuario [" << clientMsg->user() << "] en topico [" << pmsg->getTopic() << "]" << endl;

	    }	    

	    
	}

	


	cout << "Desconexion del cliente " << clientMsg->user() << endl;

    }    

}





// Envio de mensajes. Incorporacion a la cola

void Client::sendMsg( const Message& msg ) {
    
    recvQueue.put( msg.clone() );
    
}
