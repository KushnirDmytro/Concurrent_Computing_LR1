//
// Created by d1md1m on 12.03.18.
//

#ifndef CONCURRENT_COMPUTING_FILE1_H
#define CONCURRENT_COMPUTING_FILE1_H
#include "time_measurement.h"
#include <chrono>

//using namespace std;

std::chrono::high_resolution_clock::time_point get_current_time_fenced();

template<class D>

long long to_us(const D& d);

#endif //CONCURRENT_COMPUTING_FILE1_H
