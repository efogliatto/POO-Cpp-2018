#ifndef SIMCLIENT_HPP
#define SIMCLIENT_HPP

#include "ClientOpsIF.hpp"

#include "Broker.hpp"

#include <thread>


class SimClient : public ClientOpsIF {

protected:

    std::thread simth;

    Broker& broker;

    virtual void runSim() = 0;


public:

    SimClient(Broker& b);

    void start();   

};


#endif // SIMCLIENT_HPP
