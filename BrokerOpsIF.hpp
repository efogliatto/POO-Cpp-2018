#ifndef BROKEROPSIF_HPP
#define BROKEROPSIF_HPP

class BrokerOpsIF {

public:

    virtual void sendMsg( const Message& msg ) = 0;

};

#endif // BROKEROPSIF_HPP
