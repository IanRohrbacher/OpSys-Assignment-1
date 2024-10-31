###############################################################
# Fall 2024 OPERATING SYSTEMS (CS-33211-001)
# Programming Assignment #1
# Make file for Programming Assignment #1
#
# Ian Rohrbacher
# Fall 2024
#
###############################################################
msg:
	@echo 'Targets are:'
	@echo 'make run 	- Compiles producer and consumer then outputs producer.o and consumer.o'
	@echo 'make clean	- Ends the running processes and removes all .o files and shared memory'

###############################################################
# Variables
#
CXX = g++
CXXFLAGS = -std=c++11 -pthread
###############################################################
# Names of files running
#
TARGETS = producer consumer
#####################################################
# Used when running 'run' command
#
all: $(TARGETS)

producer: producer.o
	$(CXX) $(CXXFLAGS) -o producer producer.o -lrt

consumer: consumer.o
	$(CXX) $(CXXFLAGS) -o consumer consumer.o -lrt

producer.o: producer.cpp
	$(CXX) $(CXXFLAGS) -c producer.cpp

consumer.o: consumer.cpp
	$(CXX) $(CXXFLAGS) -c consumer.cpp

#####################################################
# Compiles and outputs producer and consumer
#
run: producer consumer
	./producer& ./consumer&
#####################################################
# Removes all .o files, shared memory, and kills the running processes
#
clean:
	rm -f *.o $(TARGETS)
	rm -f /dev/shm/shared_memory
	pkill producer
	pkill consumer
#####################################################
