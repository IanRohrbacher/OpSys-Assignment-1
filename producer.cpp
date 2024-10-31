// Ian Rohrbacher
// Operating Systems
// Programming Assignment #1
// 11/1/2024

#include <iostream>
#include <semaphore.h>
#include <thread>
#include <ctime>
#include <sys/mman.h>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>

// define colors for error message | Works with UBUNTU/LINUX and MacOS ONLY!
#define ERROR "\033[1m\033[31m"
#define INCOMPLETE  "\033[33m"
#define RESET   "\033[0m"

const bool RANDOM = false; // set true for a random set of tables and false for a set list of tables
const int TABLE_SIZE = 2; // sets size of table for data storage | MUST MATCH WITH CONSUMER.CPP

struct shared_data {
    sem_t empty;
    sem_t full;
    sem_t mutex;
    int table[TABLE_SIZE]; // "The table can only hold two items at the same time."
};

void producer(shared_data* data) {
    while (true) {
        sem_wait(&data->empty); // wait for the table to be empty
        sem_wait(&data->mutex); // wait for independent access to the table

        // produces items in the table and prints it
        std::cout << "\nTable is Empty\nFilling Table...\nNew Table[";
        for (int i = 0; i < TABLE_SIZE; i++) {
            data->table[i] = ((rand() % 1000) + 1); // fulls the table with 'TABLE_SIZE' random numbers, 1-1000 | 0 is null
            std::cout << data->table[i];
            if(i!=(TABLE_SIZE-1)) { std::cout << ",";}
        }
        std::cout << "]\nFilled!";

        sem_post(&data->mutex); // release the table
        sem_post(&data->full); // signals that the table is full and item has been produced

        sleep(1);
    }
}

int main() {
    // using rand() for table insertion
    if(RANDOM) {
        srand(int(time(0))); // sets seed for random numbers
    } else {
        srand(5); // sets seed to static number
    }

    // creates/locates shared memory
    int shm_fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
    // error out if shared memory failed to open
    if (shm_fd == -1) {
        std::cerr << ERROR << "\nProducer Error! Shared memory failed to open\n" << RESET;
        std::cerr << ERROR << "Please run \'make stop\' and try running \'make run\' again!\nIf the error persists run \'make clean\'!\n" << RESET;
        return 1;
    }

    // set the size of the shared memory
    ftruncate(shm_fd, sizeof(shared_data));
    //check that shared memory was created
    if (shm_fd == -1) {
        std::cerr << ERROR << "\nProducer Error! Shared memory failed to create\n" << RESET;
        std::cerr << ERROR << "Please run \'make stop\' and try running \'make run\' again!\nIf the error persists run \'make clean\'!\n" << RESET;
        return 1;
    }

    // map the shared memory
    shared_data* data = (shared_data*) mmap(0, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); 
    // error out if the map failed
    if (data == MAP_FAILED) {
        std::cerr << ERROR << "\nProducer Error! Map failed to create\n" << RESET;
        std::cerr << ERROR << "Please run \'make stop\' and try running \'make run\' again!\nIf the error persists run \'make clean\'!\n" << RESET;
        return 1;
    }

    // initialize the semaphores
    sem_init(&data->empty, 1, TABLE_SIZE); // table is empty
    sem_init(&data->full, 1, 0); // nothing in the table at the start
    sem_init(&data->mutex, 1, 1); // mutex for the table - ensure mutual exclusion

    // start the process
    std::thread producer_thread(producer, data);
    producer_thread.join();

    return 0;
}
