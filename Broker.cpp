#include "Broker.hpp"

#include <iostream>

using namespace std;


BrokerOpsIF* Broker::registerClient( ClientOpsIF* c ) {
    
    unique_access< vector<Client*> > accessClient( clients );

    accessClient->push_back( new Client(c, *this) );
    
    return accessClient->back();
    
}




// Nueva subscripcion

void Broker::addSubscription( Subscription& sub ) {


    // Acceso al registro de subscripciones a traves del accessor

    unique_access< multiset<Subscription*> > accessSub(subs_cache);

    accessSub->insert( &sub );



    // Acceso al registro de retained topics para ver si esta disponible

    unique_access< multiset<RetainedTopic*> > accessTopic(topics_cache);

    for(auto rtopics : *accessTopic) {

    	if( rtopics->topic == sub.topic ) {

    	    cout << "FALTA IMPLEMENTAR MENSAJE DE RECEPCION\n";

    	}

    }    
    
    
}



// Remocion de subscripcion

void Broker::removeSubscription( Subscription& sub ) {

    cout << "erased\n";
    
    // Acceso al registro de subscripciones a traves del accessor

    unique_access< multiset<Subscription*> > accessSub(subs_cache);

    for( auto rsub : *accessSub ) {

    	if( (sub.topic == rsub->topic)  &&  (sub.owner == rsub->owner) ) {
	    
    	    accessSub->erase( rsub );

	}

    }
    

    // if( accessSub->find(sub) != accessSub->end() )
    // 	accessSub->erase( sub );


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
