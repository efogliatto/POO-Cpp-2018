#include <iostream>

#include "SimPublisher.hpp"

#include "SimSubscriptor.hpp"

#include <random>



using namespace std;



int main( int argc, char **argv ) {


    // Broker

    Broker broker;

    
    
    // Clientes aleatorios
    // Numero total por linea de comandos. Por defecto es 4
    
    auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());    

    int nclients(4),
    	npub(0),
    	nsub(0);
    
    if(argc == 2)
    	nclients = std::atoi(argv[1]);



    // Creacion de los clientes
    
    std::vector<SimClient*> Clients;

    std::vector<std::thread> thclient;    

    for( int i = 0 ; i < nclients ; i++ ) {

    	if( gen() ) {
	    
    	    Clients.push_back( new SimPublisher(broker, "Pub_" + std::to_string(npub)) );

    	    npub++;

    	}

    	else {

    	    Clients.push_back( new SimSubscriptor(broker, "Sub_" + std::to_string(nsub)) );

    	    nsub++;

    	}


    	// Comienzo de la simulacion para el cliente

    	thclient.push_back( std::thread(&SimClient::start, Clients[i]) );	

    }




    // Join clients

    for(auto &th : thclient)
    	if(th.joinable())
    	    th.join();    



    



    

    // // Publisher threads

    // int npub = 2;

    // std::vector<SimPublisher*> publishers;

    // std::vector<std::thread> tpub;    

    // for( int i = 0 ; i < npub ; i++ )
    // 	publishers.push_back( new SimPublisher(broker, "Pub_" + std::to_string(i)) );

    // for( int i = 0 ; i < npub ; i++ )
    // 	tpub.push_back( std::thread(&SimClient::start, publishers[i]) );


    
    // // Subscriptor threads

    // int nsub = 2;

    // std::vector<SimSubscriptor*> subscriptors;

    // std::vector<std::thread> tsub;    

    // for( int i = 0 ; i < nsub ; i++ )
    // 	subscriptors.push_back( new SimSubscriptor(broker, "Sub_" + std::to_string(i)) );

    // for( int i = 0 ; i < nsub ; i++ )
    // 	tsub.push_back( std::thread(&SimClient::start, subscriptors[i]) );

    

    // // Join publishers

    // for(auto &th : tpub)
    // 	if(th.joinable())
    // 	    th.join();


    // // Join subscriptors

    // for(auto &th : tsub)
    // 	if(th.joinable())
    // 	    th.join();    
        
}
