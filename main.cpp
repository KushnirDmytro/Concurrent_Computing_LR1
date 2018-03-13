#include <iostream>
#include "file1.h"
#include "file2.h"
#include <chrono>
#include <atomic>


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

uint64_t diaphant_roots_number_of_3_args_to_border(uint32_t border){
    uint64_t cnt = 0;

    for (uint64_t x_i = 1; x_i <= border; x_i ++ ){
        for (uint64_t y_i = 1; y_i <= border; y_i ++ ){
            for (uint64_t n_i = 1; n_i <= border; n_i ++ ){
                cnt += is_a_solution(x_i, y_i, n_i);
            }
        }
    }

    return cnt;
}


inline bool str2Ulong(const char* str,unsigned long & arValue)
{
    char *tempptr=NULL;
    arValue=strtoul(str,&tempptr,10);

    return ! (arValue==0 && tempptr==str);

}

int main(int argc, char *argv[])
{
    uint64_t  diapasone = 500;

    if (argc > 1) {

        if  ( ! str2Ulong(argv[1], diapasone) ) {
            return 1;
        }

    }

    std :: cout << argv[0] << std::endl;
    std :: cout << diapasone << std::endl;



    auto stage1_start_time = get_current_time_fenced();

//    ................... ваш код ....................
    uint64_t rez = diaphant_roots_number_of_3_args_to_border(diapasone);
    auto stage2_start_time = get_current_time_fenced();

//    ................... ваш код ....................

    auto finish_time = get_current_time_fenced();

    auto total_time = finish_time - stage1_start_time;
    auto stage1_time = stage2_start_time - stage1_start_time;
    auto stage2_time = finish_time - stage2_start_time;
//
    cout << "Total time: " << to_us(total_time) << endl;
    cout << "Stage 1 time: " << to_us(stage1_time) << endl;
    cout << "Stage 2 time: " << to_us(stage2_time) << endl;



//    uint64_t rez = diaphant_roots_number_of_3_args_to_border(diapasone);

    std :: cout << rez << std::endl;
    return 0;
}