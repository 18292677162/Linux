#include "data_pool.h"

data_pool::data_pool():pool(CAPACITY), start(0),end(0)
{
    sem_init(&put_sem, 0, CAPACITY);
    sem_init(&get_sem, 0, 0);
}

void data_pool::put_msg(const std::string &_in_msg)
{
    sem_wait(&put_sem);
    pool[end] = _in_msg;
    ++end;
    end %= CAPACITY;
    sem_post(&get_sem);
}

void data_pool::get_msg(std::string &_out_msg)
{
    sem_wait(&get_sem);//P
    _out_msg = pool[start];
    ++start;
    start %= CAPACITY;
    sem_post(&put_sem);//V
}

data_pool::~data_pool()
{}
