#ifndef SIMCLIENT_HPP
#define SIMCLIENT_HPP

#include "ClientOpsIF.hpp"

#include "Broker.hpp"

#include <thread>


class SimClient : public ClientOpsIF {

protected:

    
    // Own thread
    
    std::thread simth;

    
    // Referencia al broker
    
    Broker& broker;


    // Interfase para simulacion

    virtual void runSim() = 0;


    // Nombre de usuario (usado para mensajes de recepcion)

    std::string username;


    // Estado de la conexion

    ConnAckMsg::Status status;


public:

    SimClient(Broker& b);

    void start();

    void recvMsg(const Message& m);

};


#endif // SIMCLIENT_HPP
