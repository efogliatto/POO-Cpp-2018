#ifndef CLIENTOPSIF_HPP
#define CLIENTOPSIF_HPP

class ClientOpsIF {

public:

    virtual void recvMsg( const Message& msg ) = 0;

};

#endif // CLIENTOPSIF_HPP
