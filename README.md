# OpSys-Assignment-1
Fall 2024 Operating Systems (CS-33211-001) Assignment #1
>*Created, ran, and tested on Kent State University's wasp/hornet sever*

## Assignment 1 Details
The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

## Getting started
### Installing
Copy files onto a Linux/Unix machine with C/C++ installed.

### Running
- To start the program use 'make run'.
- To end the program use 'make stop'.
- Inorder to run 'make run' again you must call 'make stop'.
- If you want a different outcome with RANDOM set to 'true' or when you are finished running this program use 'make clean'.
  
## Features
There are two variable you can play with:
- RANDOM - set to 'false' for the output to be content and set to 'true' for the output to be random. Found only in 'producer.cpp'.
- TABLE_SIZE - Allows the storage size to be changed. MUST MATCH WITHIN 'producer.cpp' and 'consumer.cpp'.

---

There are three make commands you can use:
- make run
>This command threads, compiles 'producer.cpp' and 'consumer.cpp', and runs using './producer& ./consumer&'.
- make stop
>This command kills 'producer.cpp' and 'consumer.cpp' with pkill.
- make clean
>This command removes all files created.

## Example of Execution
- Example of code executioning with RANDOM=false TABLE_SIZE=2.
```{bash}
[$PATH]$ make run
g++ -std=c++11 -pthread -c producer.cpp
g++ -std=c++11 -pthread -o producer producer.o -lrt
g++ -std=c++11 -pthread -c consumer.cpp
g++ -std=c++11 -pthread -o consumer consumer.o -lrt
./producer& 
./consumer&
[$PATH]$ 

Table is Empty
Filling Table...
New Table[676,766]
Table is Full
Emptying Table...
Emptied Item[676,766]

Table is Empty
Filling Table...
New Table[611,73]
Table is Full
Emptying Table...
Emptied Item[611,73]

Table is Empty
Filling Table...
New Table[277,633]
Table is Full
Emptying Table...
Emptied Item[277,633]

Table is Empty
Filling Table...
New Table[921,650]
Table is Full
Emptying Table...
Emptied Item[921,650]

Table is Empty
Filling Table...
New Table[74,382]
Table is Full
Emptying Table...
Emptied Item[74,382]

[$PATH]$ make stop
pkill producer
pkill consumer
[$PATH]$ make clean
rm -f *.o producer consumer
rm -f /dev/shm/shared_memory
```

## Contributing
This is a finished assignment uploaded to github for a grade. Do NOT copy and paste my work but feel free to use it as a reference.

## Licensing
The code in this project is licensed under MIT license.
