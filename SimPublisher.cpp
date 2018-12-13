#include "SimPublisher.hpp"

#include <iostream>

#include <sstream>

#include <chrono>

using namespace std;




SimPublisher::SimPublisher(Broker& b) : SimClient(b) {}


void SimPublisher::runSim() {


    // Registro en el broker y solicitud de conexion
    
    BrokerOpsIF* brops = broker.registerClient(this);

    stringstream ss;

    ss << this_thread::get_id();

    username = ss.str();

    brops->sendMsg(  ConnectMsg( username, "pass" )  );



    // Simulacion si la conexion es correcta

    if( status == ConnAckMsg::Status::CONNECTION_OK ) {
    


	for( int i = 0 ; i < 5 ; ++i ) {

	    int sleep = 500 + rand() / (RAND_MAX / 1001 + 1);
	
	    this_thread::sleep_for( chrono::milliseconds(sleep) );

	    PublishMsg m("Topico", "Valor");

	    brops->sendMsg(m);

	}

    
	brops->sendMsg( DisconnectMsg() );


    }
    

}


// void SimPublisher::recvMsg(const Message& m) {

    
//     const Message::Type mtype = m.getType();

//     const PublishMsg* pmsg;


//     switch( mtype ) {


//     case Message::Type::PUBLISH:

//     	pmsg = dynamic_cast<const PublishMsg*>(&m);

//     	cout << pmsg->getTopic() + "\n";

//     	break;
	    

//     default:

//     	break;

	    
//     }
	

// }
