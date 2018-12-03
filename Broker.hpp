#ifndef BROKER_HPP
#define BROKER_HPP


#include "Client.hpp"

#include "Subscription.hpp"

#include "RetainedTopic.hpp"


class Broker {

private:

    std::vector<Client*> clients;

    std::vector<Subsciption*> subs_cache;

    std::vector<RetainedTopic*> topics_cache;


public:

    BrokerOpsIF* registerClient( ClientOpsIF* c );
    

};


#endif // BROKER_HPP
