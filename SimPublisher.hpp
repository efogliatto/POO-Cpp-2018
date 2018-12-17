#ifndef SIMPUBLISHER_HPP
#define SIMPUBLISHER_HPP

#include "SimClient.hpp"


class SimPublisher : public SimClient {

private:

    void runSim();


public:

    SimPublisher(Broker& b);

    SimPublisher(Broker& b, const std::string& name);

};

#endif // SIMPUBLISHER_HPP
