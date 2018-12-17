#ifndef SIMSUBSCRIBER_HPP
#define SIMSUBSCRIBER_HPP

#include "SimClient.hpp"


class SimSubscriber : public SimClient {

private:

    void runSim();


public:

    SimSubscriber(Broker& b);

    SimSubscriber(Broker& b, const std::string& name);    

};

#endif // SIMSUBSCRIBER_HPP
