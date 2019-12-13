// Copyright 2019 Ogrebatel <your_email>

#include <header.hpp>

cache::cache() {
    int x = 1;

    for (; pow(2, x) < 0.5 * l1; ++x){
        continue;
    }

    int n = 0;
    while (pow(2, x + n) < (1.5) * l3) {
        cache_size_of_experiment.push_back(pow(2, x + n));
        ++n;
    }

    cache_size_of_experiment.push_back(1.5 * l3);

    for (unsigned i = 0; i < cache_size_of_experiment.size(); ++i)
        cout << i << " experiment: size = "
    << cache_size_of_experiment[i] << endl;
}

void cache::start() {
    for (int j = 0; j < 3; ++j){
        print_header(j);
        for (int i = 0; i < 8; ++i) {
            entry(i, j);
        }
    }
}

//--------------------------------------EXPERIMENT-----------------------------------------------

void cache::entry(unsigned number_of_experiment, int type_of_pass) {
    clock_t time;
    creating(number_of_experiment);
    heating(number_of_experiment);
    switch (type_of_pass) {
        case DIRECT:
            time = direct_pass(number_of_experiment);
            results(number_of_experiment, time);
            break;
        case BACKWARD:
            time = backward_pass(number_of_experiment);
            results(number_of_experiment, time);
            break;
        case RANDOM:
            time = random_pass(number_of_experiment);
            results(number_of_experiment, time);
            break;
    }
    clearing();
}

void cache::creating(unsigned num_of_experiment) {
    buffer = new char [cache_size_of_experiment[num_of_experiment]];
}

void cache::heating(unsigned num_of_experiment) {
    for (unsigned i = 0; i < 10; ++i) {
        for (unsigned num = 0;
        num < cache_size_of_experiment[num_of_experiment]; ++num) {
            buffer[num] = static_cast<char>(rand_r(&i) % 255 - 128);
        }
    }
}

//-------------------------------------PASSES-----------------------------------------

clock_t cache::direct_pass(unsigned num_of_experiment) {
    clock_t start = clock();
    for (unsigned i = 0; i < iter; ++i) {
        for (unsigned num = 0;
        num < cache_size_of_experiment[num_of_experiment]; ++num) {
            buffer[num] = static_cast<char>(rand_r(&i) % 255 - 128);
        }
    }
    clock_t stop = clock();
    return stop - start;
}

clock_t cache::backward_pass(unsigned num_of_experiment) {
    clock_t start = clock();
    for (unsigned i = 0; i < iter; ++i) {
        for (unsigned num = cache_size_of_experiment[num_of_experiment] - 1;
        num > 0; --num) {
            buffer[num] = static_cast<char>(rand_r(&i) % 255 - 128);
        }
    }
    clock_t stop = clock();
    return stop - start;
}

clock_t cache::random_pass(unsigned num_of_experiment) {
    vector<int> current_num;

    for (unsigned i = 0;
    i < cache_size_of_experiment[num_of_experiment]; ++i) {
        current_num.push_back(i);
    }

    srand(time(NULL));
    random_shuffle(current_num.begin(), current_num.end());

    clock_t start = clock();
    for (unsigned i = 0; i < iter; ++i) {
        for (unsigned num = 0;
        num < cache_size_of_experiment[num_of_experiment]; ++num) {
        buffer[current_num[num]] = static_cast<char>(rand_r(&i) % 255 - 128);
        }
    }
    clock_t stop = clock();
    return stop - start;
}

//----------------------------------ALL_PASSES_HIGHER------------------------------------------

void cache::clearing() {
    cache_size_of_experiment.clear();
    delete [] buffer;
}

//---------------------------------------------------------------------------------------------

void cache::print_header(unsigned type_of_pass) {
    cout << "investigation:" << endl;
    switch (type_of_pass)
    {
        case DIRECT:
            cout << "  travel_variant: direct" << endl;
            break;
        case BACKWARD:
            cout << "  travel_variant: backward" << endl;
            break;
        case RANDOM:
            cout << "  travel_variant: random" << endl;
            break;
    }
    cout << "  experiments: " << endl;
}

void cache::results(unsigned number_of_experiment, clock_t time) {
    cout << "     - experiment: " << endl;
    cout << "  number: " << number_of_experiment + 1 << endl;
    cout << "  input_data: " << endl;
    cout << "    buffer_size: "
         << cache_size_of_experiment[number_of_experiment] << " bytes" << endl;
    cout << "  results: " << std::endl;
    cout << "duration: " << time << " ms" << endl << endl;
}
