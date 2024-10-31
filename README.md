# OpSys-Assignment-1
Fall 2024 Operating Systems (CS-33211-001) Assignment #1
>*Created, ran, and tested on Kent State University's wasp/hornet sever*

## Assignment 1 Details
The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

## Getting started
### Installing
Copy files onto a Linux/Unix machine with C/C++ installed.

### Running
There are three commands you will be using:
```{bash}
make run
```
>This command threads, compiles 'producer.cpp' and 'consumer.cpp', and runs using './producer& ./consumer&'.
```{bash}
make stop
```
>This command kills 'producer.cpp' and 'consumer.cpp' with pkill.
```{bash}
make clean
```
>This command removes all files created.

## Features
There are two variable you can play with:
1. RANDOM - set to 'false' for the output to be constent and set to 'true' for the output to be random. Found only in 'producer.cpp'.
2. TABLE_SIZE - Allows the storage size to be changed. MUST MATCH WITHIN 'producer.cpp' and 'consumer.cpp'.

## Contributing
This is a finnished assignment uploaded to github for a grade. You should NOT copy and paste this work but feel free to use it as a refrence.

## Licensing
The code in this project is licensed under MIT license.
