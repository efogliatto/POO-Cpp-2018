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


    SubscribeMsg m("Topico");

    brops->sendMsg(m);



    this_thread::sleep_for( chrono::seconds(3) );

    brops->sendMsg(m);


    this_thread::sleep_for( chrono::seconds(3) );
    
    brops->sendMsg( DisconnectMsg() );
    

}


void SimSubscriptor::recvMsg(const Message& m) {



}
