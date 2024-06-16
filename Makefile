# Compiler and flags
CC = g++
CFLAGS = -Wall -Werror # Compiler flags, enable all warnings and treat them as errors
LDFLAGS = -pthread # Linker flags, enable multithreading support

# Default target that compiles the entire program
all: clean myprogram

# Linking the program
myprogram: main.o LoadBalancer.o Webserver.o
	$(CC) $(LDFLAGS) -o myprogram main.o LoadBalancer.o Webserver.o

# Compiling main.cpp to produce main.o
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

# Compiling LoadBalancer.cpp to produce LoadBalancer.o
LoadBalancer.o: LoadBalancer.cpp
	$(CC) $(CFLAGS) -c LoadBalancer.cpp

# Compiling Webserver.cpp to produce Webserver.o
Webserver.o: Webserver.cpp
	$(CC) $(CFLAGS) -c Webserver.cpp

# Clean target to remove compiled files
clean:
	rm -f myprogram *.o
