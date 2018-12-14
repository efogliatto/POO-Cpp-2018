#include <iostream>

#include "Broker.hpp"

#include "SimPublisher.hpp"

#include "SimSubscriptor.hpp"

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
	publishers.push_back( new SimPublisher(broker, "Pub_" + std::to_string(i)) );

    for( int i = 0 ; i < npub ; i++ )
    	tpub.push_back( std::thread(&SimClient::start, publishers[i]) );


    
    // Publisher threads

    int nsub = 1;

    std::vector<SimSubscriptor*> subscriptors;

    std::vector<std::thread> tsub;    

    for( int i = 0 ; i < nsub ; i++ )
	subscriptors.push_back( new SimSubscriptor(broker, "Sub_" + std::to_string(i)) );

    for( int i = 0 ; i < nsub ; i++ )
    	tsub.push_back( std::thread(&SimClient::start, subscriptors[i]) );



    

    // Join publishers

    for(auto &th : tpub)
    	if(th.joinable())
    	    th.join();


    // Join subscriptors

    for(auto &th : tsub)
    	if(th.joinable())
    	    th.join();    
        
}
