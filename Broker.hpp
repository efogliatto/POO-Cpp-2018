#ifndef BROKER_HPP
#define BROKER_HPP

#include "Client.hpp"


class Broker {

    
private:

    std::vector<Client*> clients;

    std::vector<Subscription*> subs_cache;

    std::vector<RetainedTopic*> topics_cache;


public:

    BrokerOpsIF* registerClient( ClientOpsIF* c );
    

};


#endif // BROKER_HPP
