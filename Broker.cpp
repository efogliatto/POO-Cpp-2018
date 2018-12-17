#include "Broker.hpp"

#include "rndTime.hpp"

#include <iostream>

using namespace std;




// Constructor por defecto

Broker::Broker() : maxClients(100) {}


// Constructor con maximos clientes

Broker::Broker(const int& maxc) : maxClients(maxc) {}



// Registro de cliente en el broker

BrokerOpsIF* Broker::registerClient( ClientOpsIF* c ) {
    

    unique_access< multiset<Client*> > accessClient( clients );

    Client* client = nullptr;

    if( (int)accessClient->size() <= maxClients ) {

	client = new Client(c, *this);
    
	accessClient->insert( client );

    }


    
    return client;

    
}




// Nueva subscripcion

void Broker::addSubscription( Subscription* sub ) {


    // Acceso al registro de subscripciones a traves del accessor
    // Cuidado: no vuelve a buscar. Queda a cargo de Client

    unique_access< multiset<Subscription*> > accessSub(subs_cache);

    accessSub->insert( sub );



    // Acceso al registro de retained topics para ver si esta disponible

    unique_access< multiset<RetainedTopic*> > accessTopic(topics_cache);

    for(auto rtopics : *accessTopic) {

    	if( rtopics->topic == sub->topic ) {


	    unique_access< ClientOpsIF* > cif = sub->owner->CIF();
	    
	    PublishMsg m( "Enviando mensaje de topico [" + rtopics->topic + "] a subscriptor", "" );

	    (*cif)->recvMsg(m);	 
	    

    	}

    }    
    
    
}



// Remocion de subscripcion

void Broker::removeSubscription( Subscription* sub ) {

    
    // Acceso al registro de subscripciones a traves del accessor

    unique_access< multiset<Subscription*> > accessSub(subs_cache);

    for( auto rsub : *accessSub ) {

    	if( (sub->topic == rsub->topic)  &&  (sub->owner == rsub->owner) )
	    accessSub->erase( rsub );

    }
    

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





// Remocion de subscripcion

void Broker::removeRetainedTopic( RetainedTopic* rt ) {


    // Acceso al registro de subscripciones a traves del accessor

    unique_access< multiset<RetainedTopic*> > accessRT( topics_cache );

    for( auto rsub : *accessRT ) {

    	if( rt->owner == rsub->owner )
	    accessRT->erase( rsub );

    }    
    

}




// Envio de topico a subscriptores

void Broker::sendTopic( const TopicName& name, const TopicValue& val ) {

    
    // Distribucion de mensajes a los subscriptores     

    unique_access< multiset<Subscription*> > accessSub(subs_cache);

    for(auto sub : *accessSub) {

    	if( sub->topic == name ) {

	    unique_access< ClientOpsIF* > cif = sub->owner->CIF();
	    
	    PublishMsg m( "Enviando mensaje de topico [" + name + "] a subscriptor", val );

	    (*cif)->recvMsg(m);	    

    	}

    }
    

}





// Solicitud de conexion

void Broker::connReq( Client* c ) {

    unique_access< ClientOpsIF* > cif = c->CIF();

    ConnAckMsg m;


    // 20% de conexiones erroneas
    
    rndTime rnd(1,10);

    if( rnd.time() <= 8 ) {
	
	m.setStatus( ConnAckMsg::Status::CONNECTION_OK );

    }

    else {

	m.setStatus( ConnAckMsg::Status::LOGIN_ERROR );

    }
    

    (*cif)->recvMsg(m);	    

}






// Remocion de cliente

void Broker::removeClient( Client* c ) {

    unique_access< multiset<Client*> > accessClient( clients );

    for( auto client : *accessClient ) {
	
    	if( client == c )
    	    accessClient->erase(client);    

    }


}
