#include "Broker.hpp"

// #include "threadStream.hpp"

#include <iostream>

using namespace std;


BrokerOpsIF* Broker::registerClient( ClientOpsIF* c ) {


    lock_guard<mutex> lg(mreg);
        
    clients.push_back( new Client(c, *this) );

    return clients.back();

}




// Nueva subscripcion

void Broker::addSubscription( Subscription* sub ) {


    // Acceso al registro de subscripciones a traves del accessor

    unique_access< multiset<Subscription*> > accessSub(subs_cache);

    if( accessSub->find(sub) == accessSub->end() ) {
	
    	accessSub->insert( sub );

    	cout << "Tambien del broker" << endl;

    }
    
}



// Remocion de subscripcion

void Broker::removeSubscription( Subscription* sub ) {


    // Acceso al registro de subscripciones a traves del accessor

    unique_access< multiset<Subscription*> > accessSub(subs_cache);

    if( accessSub->find(sub) != accessSub->end() )
    	accessSub->erase( sub );

}



// Actualizacion de topico retenido

void Broker::updateRTopic( RetainedTopic* rt ) {

    
    // Acceso al registro de topicos a traves del accessor

    unique_access< multiset<RetainedTopic*> > accessTopic(topics_cache);

    
    // Incorporacion al cache de topicos retenidos
    // Si ya existe, actualiza el valor
    
    bool findTopic(false);

    for(auto rtopics : *accessTopic) {

    	if( rtopics->topic == rt->topic ) {

    	    rtopics->value = rt->value;

    	    findTopic = true;

    	}

    }

    if(!findTopic)	
    	accessTopic->insert(rt);           

}





// Envio de topico a subscriptores

void Broker::sendTopic( const TopicName& name, const TopicValue& val ) {

    
    // Distribucion de mensajes a los subscriptores     

    unique_access< multiset<Subscription*> > accessSub(subs_cache);

    for(auto sub : *accessSub) {

    	if( sub->topic == name ) {

	    cout << "Enviando mensaje de topico [" << name << "] a subscriptor [" << "]" << endl;

    	}

    }    

}
