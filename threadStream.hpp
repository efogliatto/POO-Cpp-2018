#ifndef THREADSTREAM
#define THREADSTREAM

#include <iostream>
#include <sstream>
#include <mutex>

/*

Implementacion sencilla de cout thread safe
Esta en stackoverflow

 */

#define thout ThreadStream( std::cout )


class ThreadStream : public std::ostringstream {
    
public:
    
    ThreadStream(std::ostream& os) : os_(os) {}

    ~ThreadStream() {
	
	std::lock_guard<std::mutex> guard(_mutex_threadstream);
	
	os_ << this->str();
	    
    }
    

private:
    
    static std::mutex _mutex_threadstream;
    
    std::ostream& os_;
    
};

std::mutex ThreadStream::_mutex_threadstream{};

#endif
