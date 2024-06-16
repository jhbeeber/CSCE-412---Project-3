CC = g++
CFLAGS = -Wall -Werror
LDFLAGS = -pthread

all: myprogram

myprogram: main.o LoadBalancer.o Webserver.o
	$(CC) $(LDFLAGS) -o myprogram main.o LoadBalancer.o Webserver.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

LoadBalancer.o: LoadBalancer.cpp
	$(CC) $(CFLAGS) -c LoadBalancer.cpp

Webserver.o: Webserver.cpp
	$(CC) $(CFLAGS) -c Webserver.cpp

clean:
	rm -f myprogram *.o
