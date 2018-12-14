#include "SimSubscriptor.hpp"

#include <iostream>

#include <sstream>

#include <chrono>

#include "TopicsList.hpp"

#include "rndTime.hpp"


using namespace std;


// Constructores

SimSubscriptor::SimSubscriptor(Broker& b) : SimClient(b) {}

SimSubscriptor::SimSubscriptor(Broker& b, const string& name) : SimClient(b,name) {}



// Simulacion de subscripcion

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


	
	// Subscripcion aleatoria a un topico	

	rndTime tsub(500,1500);
	
	this_thread::sleep_for( chrono::milliseconds(tsub.time()) );
	

	TopicsList topics;

	string tp = topics.randomTopic();
	
    
	SubscribeMsg m(tp);

	brops->sendMsg(m);




	// Espera y desubscripcion

	rndTime tdsub(2,4);
	
	this_thread::sleep_for( chrono::seconds( tdsub.time() ) );

	UnsubscribeMsg um(tp);
    
	brops->sendMsg(um);


	
	// Desconexion

	this_thread::sleep_for( chrono::seconds(1) );
    
	brops->sendMsg( DisconnectMsg() );
    

    }

    
}
