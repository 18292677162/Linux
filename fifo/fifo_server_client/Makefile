.PHONY:all
all:clientPipe serverPipe

clientPipe:clientPipe.c
	gcc -o $@ $^
serverPipe:serverPipe.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f clientPipe serverPipe
