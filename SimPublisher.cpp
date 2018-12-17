#include "SimPublisher.hpp"

#include <iostream>

#include <sstream>

#include <chrono>

#include "TopicsList.hpp"

#include "rndTime.hpp"

using namespace std;



// Constructores

SimPublisher::SimPublisher(Broker& b) : SimClient(b) {}

SimPublisher::SimPublisher(Broker& b, const string& name) : SimClient(b,name) {}



// Simulacion de publicacion

void SimPublisher::runSim() {


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


	    // Topico de publicacion aleatorio
	
	    TopicsList topics;

	    string tp = topics.randomTopic();



	    // Tiempo de demora entre publicaciones aleatorio: entre 500 y 2000 milisegundos

	    rndTime rt(500, 2000);
	    // rndTime rt(50, 200);
	
    

	    for( int i = 0 ; i < 10 ; ++i ) {
	    
		this_thread::sleep_for(  chrono::milliseconds( rt.time() )  );

		PublishMsg m(tp, "Valor");

		brops->sendMsg(m);

	    }

    
	    brops->sendMsg( DisconnectMsg() );

	}
    

    }


    else {

	cout << "Error de registro del usuario [" + username + "]\n";
	
    }
    
}
