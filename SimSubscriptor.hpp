#ifndef SIMSUBSCRIPTOR_HPP
#define SIMSUBSCRIPTOR_HPP

#include "SimClient.hpp"


class SimSubscriptor : public SimClient {

private:

    void runSim();


public:

    SimSubscriptor(Broker& b);

    SimSubscriptor(Broker& b, const std::string& name);
    
    // void recvMsg(const Message& m);

};

#endif // SIMSUBSCRIPTOR_HPP
