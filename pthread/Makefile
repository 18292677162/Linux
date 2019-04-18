all:create exit join detach ticket mutex cond
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
