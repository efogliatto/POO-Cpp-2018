#include <iostream>

#include "Queue.hpp"

#include <chrono>

#include <thread>

#include <vector>

using myqueue = Queue<int,2>;


using namespace std;

int main( int argc, char **argv ) {


// Codigo para prueba de Queue

    myqueue q;

    vector<thread> tvec;

    
    for( int i = 0 ; i < 10 ; ++i )	
	tvec.push_back( std::thread(&myqueue::put, &q, i) );


    while( !q.empty() ) {

	int a;

	this_thread::sleep_for(chrono::seconds(2));
	cout << endl;
	
	thread t( &Queue<int,2>::get, &q, &a );

	t.join();		
	
    }

    
    for( int i = 0 ; i < 10 ; ++i )
	tvec[i].join();
  
    
}
