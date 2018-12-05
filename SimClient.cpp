#include "SimClient.hpp"

using namespace std;


SimClient::SimClient(Broker& b) : broker(b) {}



void SimClient::start() {
       
    simth = std::move( thread(&SimClient::runSim, this) );

    simth.join();
    
}