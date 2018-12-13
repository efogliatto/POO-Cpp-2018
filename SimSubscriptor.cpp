#include "SimSubscriptor.hpp"

#include <iostream>

#include <sstream>

#include <chrono>

using namespace std;




SimSubscriptor::SimSubscriptor(Broker& b) : SimClient(b) {}


void SimSubscriptor::runSim() {


    // Registro en el broker y solicitud de conexion
    
    BrokerOpsIF* brops = broker.registerClient(this);

    stringstream ss;

    ss << this_thread::get_id();

    brops->sendMsg(  ConnectMsg( ss.str(), "pass" )  );



    // Simulacion si la conexion es correcta

    
    // Esperar connack


    // Envio de mensaje de subscripcion

    int sleep = 1000 + rand() / (RAND_MAX / 2001 + 1);
	
    this_thread::sleep_for( chrono::milliseconds(sleep) );   
    
    SubscribeMsg m("Topico");

    brops->sendMsg(m);



    this_thread::sleep_for( chrono::seconds(2) );

    UnsubscribeMsg um("Topico");
    
    brops->sendMsg(um);


    this_thread::sleep_for( chrono::seconds(1) );
    
    brops->sendMsg( DisconnectMsg() );
    

}


void SimSubscriptor::recvMsg(const Message& m) {

    const Message::Type mtype = m.getType();

    const PublishMsg* pmsg;


    switch( mtype ) {


    case Message::Type::PUBLISH:

    	pmsg = dynamic_cast<const PublishMsg*>(&m);

    	cout << pmsg->getTopic() + "\n";

    	break;
	    

    default:

    	break;

	    
    }

}
