// Copyright 2019 Ogrebatel <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <string>


#define DIRECT 0
#define BACKWARD 1
#define RANDOM 2

#define l1 262144
#define l3 6291456
#define iter 1000

using std::vector;
using std::string;
using std::cout;
using std::endl;


class cache {
public:
    cache();

    void start();

    //--------------------------------------EXPERIMENT-----------------------------------------------

    void entry(unsigned number_of_experiment, int type_of_pass);

    void creating(unsigned num_of_experiment);

    void heating(unsigned num_of_experiment);

    //-------------------------------------PASSES-----------------------------------------

    clock_t direct_pass(unsigned num_of_experiment);

    clock_t backward_pass(unsigned num_of_experiment);

    clock_t random_pass(unsigned num_of_experiment);

    //----------------------------------ALL_PASSES_HIGHER------------------------------------------

    void clearing();

    //---------------------------------------------------------------------------------------------

    void print_header(unsigned type_of_pass);

    void results(unsigned number_of_experiment, clock_t time);

    vector<unsigned> cache_size_of_experiment;
    char* buffer;
};

#endif // INCLUDE_HEADER_HPP_
