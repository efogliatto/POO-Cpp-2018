#include <iostream>

#include "SimPublisher.hpp"


using namespace std;

int main( int argc, char **argv ) {


    // Broker
    
    Broker broker;


    // Ejemplo de publisher
    
    SimPublisher pub(broker);

    pub.start();
    
}
