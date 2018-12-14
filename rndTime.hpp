#ifndef RNDTIME_HPP
#define RNDTIME_HPP

/*
Generador de enteros aleatorios uniformemente distribuidos
 */

#include <random>

class rndTime {

private:

    std::random_device rd;

    std::mt19937 rng;

    std::uniform_int_distribution<int> rnt;


public:

    rndTime(const int& start, const int& end) : rng(rd()), rnt(start,end) {}

    const int time() { return rnt( rng ); }	

};

#endif // RNDTIME_HPP

