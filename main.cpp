//
// Created by d1md1m on 15.03.18.
//

#include <iostream>
#include "time_measurement.h"
#include "file2.h"
#include <chrono>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

//Знайти кількість цілих додатних розв'язків рівняння (іншими словами -- розв'язків в натуральних числах) для n рівного 500:
//1/x+1/y=1/n

int is_a_solution(uint64_t x, uint64_t y, uint64_t n){
    return  ( n * (x + y) == x * y);
}

int diaphant_roots_number_of_3_args_to_border(uint64_t from, uint64_t upto, uint64_t border, uint64_t &cnt){

    for (uint64_t x_i = from; x_i < upto; x_i ++ ){

        for (uint64_t y_i = 1; y_i < border; y_i ++ ){
            for (uint64_t n_i = 1; n_i < border; n_i ++ ){
                cnt += is_a_solution(x_i, y_i, n_i);
            }
        }

    }

    return 0;
}



inline bool str2Ulong(const char* str,uint64_t & arValue)
{
    char *tempptr=NULL;
    arValue=strtoul(str,&tempptr,10);

    return ! (arValue==0 && tempptr==str);

}


int main(int argc, char *argv[])
{
    int ntreads = 2;
    uint64_t  diapasone = 1000;

    if (argc > 1) {

        if  ( ! str2Ulong(argv[1], diapasone) ) {
            perror("Bad argument #1 value\n");
            return 1;
        }

        if (argc>2){
            try {
                ntreads = atoi(argv[2]);
            } catch (std::exception const &e) {
                perror("failed to parse ARG#2");
                return 1;
                // This could not be parsed into a number so an exception is thrown.
                // atoi() would return 0, which is less helpful if it could be a valid value.
            }

        }
    }



    std :: cout << "diapasone " << diapasone << std::endl;
    std :: cout << "test threads " << ntreads << std::endl;



    auto stage1_start_time = get_current_time_fenced();


    uint64_t counter = 0;

    vector<thread> threads_v (0);
    threads_v.reserve(ntreads);

    vector<uint64_t> threads_counters(ntreads);

//    ................... ваш код ....................

    diaphant_roots_number_of_3_args_to_border( 1, diapasone, diapasone, counter);

    auto stage2_start_time = get_current_time_fenced();


    uint64_t task_split = diapasone / ntreads;
    uint64_t first_thread_extratask = diapasone % ntreads;


    uint64_t proceed_from = 0 ;
    uint64_t proceed_to = task_split + first_thread_extratask ;


    for(std::vector<int>::size_type i = 0; i != ntreads; i++) {
        // weird move to optimise overall iterations span

//        cout << "from " << proceed_from << endl;
//        cout << "to " << proceed_to << endl;



        threads_v.push_back(  thread (diaphant_roots_number_of_3_args_to_border,
                     proceed_from,
                     proceed_to,
                     diapasone,
                     std::ref(threads_counters[i]))
        );

        proceed_from = proceed_to+1;
        proceed_to+=task_split;

    }

    for(std::vector<int>::size_type i = 0; i != threads_v.size(); i++){
        threads_v[i].join();
    }



//    ................... ваш код ....................

    auto finish_time = get_current_time_fenced();

    auto total_time = finish_time - stage1_start_time;
    auto stage1_time = stage2_start_time - stage1_start_time;
    auto stage2_time = finish_time - stage2_start_time;




    cout << "thread " << counter << endl;


    uint64_t threads_sum = 0;
    for(std::vector<int>::size_type i = 0; i != threads_v.size(); i++){
        cout << "thread " << i << ": " << threads_counters[i]<< endl;
        threads_sum += threads_counters[i];
    }

    cout << "thread sum: " << threads_sum << endl;

    cout << "check " << counter << " ?= " << threads_sum << endl;

//    cout << "Total time: " << to_us(total_time) << endl;
    cout << "Consequent time: " << to_us(stage1_time) << endl;
    cout << "Parallel time: " << to_us(stage2_time) << endl;


    return 0;
}