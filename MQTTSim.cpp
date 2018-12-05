#include <iostream>

#include "Queue.hpp"


using namespace std;

int main( int argc, char **argv ) {


    Queue<int,2> q;

    thread t1( &Queue<int,2>::put, &q, 1 );

    thread t2( &Queue<int,2>::put, &q, 2 );

    thread t3( &Queue<int,2>::put, &q, 3 );   

    t1.join();

    t2.join();

    t3.join();


    int a;
    
    thread t4( &Queue<int,2>::get, &q, &a );

    cout << a << endl;

    t4.join();
    
}
