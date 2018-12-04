#ifndef BROKEROPSIF_HPP
#define BROKEROPSIF_HPP

#include "Message.hpp"


class BrokerOpsIF {

public:

    virtual void sendMsg( const Message& msg ) = 0;

};

#endif // BROKEROPSIF_HPP
