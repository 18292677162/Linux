all:create exit join detach ticket mutex cond sem sem_mutex rwlock pthread_pool
create:create.c
	gcc $^ -o $@ -lpthread
exit:exit.c
	gcc $^ -o $@ -lpthread
join:join.c
	gcc $^ -o $@ -lpthread
detach:detach.c
	gcc $^ -o $@ -lpthread
mutex:mutex.c
	gcc $^ -o $@ -lpthread
ticket:ticket.c
	gcc $^ -o $@ -lpthread
cond:cond.c
	gcc $^ -o $@ -lpthread
sem:sem.c
	gcc $^ -o $@ -lpthread
sem_mutex:sem_mutex.c
	gcc $^ -o $@ -lpthread
rwlock:rwlock.c
	gcc $^ -o $@ -lpthread
pthread_pool:pthread_pool.cpp
	g++ $^ -o $@ -lpthread
