#include <iostream>

#include "Broker.hpp"

#include "SimPublisher.hpp"

#include <vector>


// using namespace std;


int main( int argc, char **argv ) {


    // Broker

    Broker broker;


    // Publisher threads

    int npub = 1;

    std::vector<SimPublisher*> publishers;

    std::vector<std::thread> tpub;    

    for( int i = 0 ; i < npub ; i++ )
	publishers.push_back( new SimPublisher(broker) );

    for( int i = 0 ; i < npub ; i++ )
    	tpub.push_back( std::thread(&SimClient::start, publishers[i]) );





    // Join publishers

    for(auto &th : tpub)
    	if(th.joinable())
    	    th.join();
    
    


    
  
    
}
