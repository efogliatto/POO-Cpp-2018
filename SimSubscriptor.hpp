#ifndef SIMSUBSCRIPTOR_HPP
#define SIMSUBSCRIPTOR_HPP

#include "SimClient.hpp"


class SimSubscriptor : public SimClient {

private:

    void runSim();


public:

    SimSubscriptor(Broker& b);
    
    // void recvMsg(const Message& m);

};

#endif // SIMSUBSCRIPTOR_HPP
