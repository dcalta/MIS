# Makefile
# Drew Caltagirone
# Anthony Awaida
# Roberto Chavez
# CMPS 109

# COMMANDS
# make - creates executables
# make clean - removes object files and executable
# make check - ues valgrind to check for memory leaks

# use with either 'make' or 'make all'
all : MIS MISClient

# Creates MIS executable 
MIS : MIS.o MISServer.o
	g++ -std=c++11 -o MIS MISServer.o MIS.o

MIS.o : MIS.cpp MIS.h
	g++ -std=c++11 -c MIS.cpp

MISServer.o : MISServer.cpp MIS.h
	g++ -std=c++11 -c MISServer.cpp

MISClient : MISClient.o
	g++ -std=c++11 -o MISClient MISClient.o

MISClient.o : MISClient.cpp
	g++ -std=c++11 -c MISClient.cpp

# Removes MIS objects and executables
clean:
	rm -f MIS MIS.o MISServer.o

# Checks for memoru leaks for executable
check:
	valgrind --leak-check=full MIS