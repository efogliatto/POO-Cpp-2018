#include <iostream>

#include "SimPublisher.hpp"

#include "SimSubscriber.hpp"

#include "rndTime.hpp"



using namespace std;



int main( int argc, char **argv ) {


    // Broker

    Broker broker;

    
    
    // Clientes aleatorios
    // Numero total por linea de comandos. Por defecto es 4
    
    rndTime gen(0,1);

    int nclients(4),
    	npub(0),
    	nsub(0);
    
    if(argc == 2)
    	nclients = std::atoi(argv[1]);



    // Creacion de los clientes
    
    std::vector<SimClient*> Clients;

    std::vector<std::thread> thclient;    

    for( int i = 0 ; i < nclients ; i++ ) {

    	if( gen.time() ) {
	    
    	    Clients.push_back( new SimPublisher(broker, "Pub_" + std::to_string(npub)) );

    	    npub++;

    	}

    	else {

    	    Clients.push_back( new SimSubscriber(broker, "Sub_" + std::to_string(nsub)) );

    	    nsub++;

    	}


    	// Comienzo de la simulacion para el cliente

    	thclient.push_back( std::thread(&SimClient::start, Clients[i]) );	

    }




    // Join clients

    for(auto &th : thclient)
    	if(th.joinable())
    	    th.join();
    
        
}
