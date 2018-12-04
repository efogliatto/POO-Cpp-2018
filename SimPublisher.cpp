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

    brops->sendMsg(  ConnectMsg( ss.str(), "pass" )  );



    // Simulacion si la conexion es correcta

    
    // Esperar connack

    for( int i = 0 ; i < 10 ; ++i ) {

	int sleep = 500 + rand() / (RAND_MAX / 1001 + 1);
	
    	this_thread::sleep_for( chrono::milliseconds(sleep) );

    	PublishMsg m("Topico", "Valor");

    	brops->sendMsg(m);

    }

    brops->sendMsg( DisconnectMsg() );
    

}


void SimPublisher::recvMsg(const Message& m) {



}