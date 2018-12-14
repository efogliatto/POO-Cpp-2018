#include "SimSubscriptor.hpp"

#include <iostream>

#include <sstream>

#include <chrono>

using namespace std;




SimSubscriptor::SimSubscriptor(Broker& b) : SimClient(b) {}

SimSubscriptor::SimSubscriptor(Broker& b, const string& name) : SimClient(b,name) {}


void SimSubscriptor::runSim() {


    // Registro en el broker y solicitud de conexion
    
    BrokerOpsIF* brops = broker.registerClient(this);

    if( username == "undefined" ) {
    
	stringstream ss;

	ss << this_thread::get_id();

	username = ss.str();

    }

    brops->sendMsg(  ConnectMsg( username, "pass" )  );


    
    // Simulacion si la conexion es correcta

    waitConnAck();

    unique_access<ConnAckMsg::Status> stAccess( status );

    if( *stAccess == ConnAckMsg::Status::CONNECTION_OK ) {

    

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

    
}
