#include "SimSubscriber.hpp"

#include <iostream>

#include <sstream>

#include <chrono>

#include "TopicsList.hpp"

#include "rndTime.hpp"


using namespace std;


// Constructores

SimSubscriber::SimSubscriber(Broker& b) : SimClient(b) {}

SimSubscriber::SimSubscriber(Broker& b, const string& name) : SimClient(b,name) {}



// Simulacion de subscripcion

void SimSubscriber::runSim() {


    // Registro en el broker y solicitud de conexion
    
    BrokerOpsIF* brops = broker.registerClient(this);


    if( brops != nullptr ) {
	

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


	
	    // Subscripcion aleatoria a 2 topicos

	    rndTime tsub(500,1500);
	    // rndTime tsub(50,150);
	
	    this_thread::sleep_for( chrono::milliseconds(tsub.time()) );
	

	    TopicsList topics;
	    
	    vector<string> subTopics = { topics.randomTopic(), topics.randomTopic() };
	    
	    for(auto tp : subTopics) {

		SubscribeMsg m(tp);

		brops->sendMsg(m);

	    }
	    
	    

	    // Espera y desubscripcion

	    rndTime tdsub(4000,8000);
	    // rndTime tdsub(400,800);
	    
	
	    this_thread::sleep_for( chrono::milliseconds( tdsub.time() ) );

	    for(auto tp : subTopics) {

		UnsubscribeMsg m(tp);

		brops->sendMsg(m);

	    }	   

	    
	
	    // Desconexion

	    this_thread::sleep_for( chrono::milliseconds(1000) );
    
	    brops->sendMsg( DisconnectMsg() );
    

	}


    }


    else {

	cout << "Error de registro del usuario [" + username + "]\n";
	
    }    

    
}
