#include "Broker.hpp"

#include <iostream>

using namespace std;


BrokerOpsIF* Broker::registerClient( ClientOpsIF* c ) {


    lock_guard<mutex> lg(mreg);
        
    clients.push_back( new Client(c, *this) );

    return clients.back();

}




// Nueva subscripcion

void Broker::addSubscription( Subscription* sub ) {

    lock_guard<mutex> lg(msub);

    if( subs_cache.find(sub) == subs_cache.end() ) {
	
	subs_cache.insert( sub );

	// cout << "Tambien del broker" << endl;

    }

}



// Remocion de subscripcion

void Broker::removeSubscription( Subscription* sub ) {

    lock_guard<mutex> lg(msub);

    if( subs_cache.find(sub) != subs_cache.end() )
	subs_cache.erase( sub );

}



// Actualizacion de topico retenido

void Broker::updateRTopic( RetainedTopic* rt ) {

    lock_guard<mutex> lg(mtop);


    // Incorporacion al cache de topicos retenidos
    
    bool findTopic(false);

    for(auto rtopics : topics_cache) {

	if( rtopics->topic == rt->topic ) {

	    rtopics->value = rt->value;

	    findTopic = true;

	}

    }

    if(!findTopic)
	topics_cache.insert(rt);



    // Distribucion a los subscriptores

    

}
