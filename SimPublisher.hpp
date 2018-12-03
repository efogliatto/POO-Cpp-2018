#ifndef SIMPUBLISHER_HPP
#define SIMPUBLISHER_HPP

#include "SimClient.hpp"

class SimPublisher : public SimClient {

private:

    void runSim();


public:

    void recvMsg(const Message& m);

};

#endif // SIMPUBLISHER_HPP
