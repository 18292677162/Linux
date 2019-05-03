all:udp_server udp_client ntoa more_ntoa thread_ntoa
udp_server:udp_server.c
	gcc $^ -o $@
udp_client:udp_client.c
	gcc $^ -o $@
ntoa:ntoa.c
	gcc $^ -o $@
more_ntoa:more_ntoa.c
	gcc $^ -o $@
thread_ntoa:thread_ntoa.c
	gcc $^ -o $@ -lpthread
