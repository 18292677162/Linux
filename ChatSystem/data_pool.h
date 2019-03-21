#pragma once
#include <iostream>
#include <string>
#include <semaphore.h>
#include <vector>
#define CAPACITY 1024

class data_pool{
    public:
        data_pool();
        void put_msg(const std::string &_in_msg);
        void get_msg(std::string &_out_msg);
        ~data_pool();
    private:
        sem_t put_sem;
        sem_t get_sum;
        std::vector<std::string> pool;
        int start;
        int end;
};
