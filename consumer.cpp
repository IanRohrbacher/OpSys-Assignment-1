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

#define ERROR "\033[1m\033[31m"
#define INCOMPLETE  "\033[33m"
#define RESET   "\033[0m"

const int TABLE_SIZE = 2; // sets size of table for data storage | MUST MATCH WITH PRODUCER.CPP

struct shared_data {
    sem_t empty;
    sem_t full;
    sem_t mutex;
    int table[TABLE_SIZE];
};

void consumer(shared_data* data) {
    while (true) {
        sem_wait(&data->full); // wait for the table to be full
        sem_wait(&data->mutex); // wait for independent access to the table

        // prints and removes items from the table
        std::cout << "Table is Full\nEmptying Table...\nEmptyed Item[";
        for (int i = 0; i < TABLE_SIZE; i++) {
            std::cout << data->table[i];
            if(i!=(TABLE_SIZE-1)) { std::cout << ",";}
            data->table[i] = 0; // sets value to 0, 'NULL', to indicate item removed
        }
        std::cout << "]\nRemoved!\n";

        sem_post(&data->mutex); // release the table
        sem_post(&data->empty); // signals that the table is empty and item has been removed

        sleep(1);
    }
}

int main() {
    // creates/locates shared memory
    int shm_fd = shm_open("/shared_memory", O_RDWR, 0666);
    // error out if shared memory failed to open
    if (shm_fd == -1) {
        std::cerr << ERROR << "\nConsumer Error! Shared memory failed to open\n" << RESET;
        std::cerr << ERROR << "Please run \'make stop\' and try running \'make run\' again!\nIf the error persists run \'make clean\'!\n" << RESET;
        return 1;
    }

    // map the shared memory
    shared_data* data = (shared_data*) mmap(0, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    // error out if the map failed
    if (data == MAP_FAILED) {
        std::cerr << ERROR << "\nConsumer Error! Map failed to create\n" << RESET;
        std::cerr << ERROR << "Please run \'make stop\' and try running \'make run\' again!\nIf the error persists run \'make clean\'!\n" << RESET;
        return 1;
    }
    std::cout << std::endl;

    // start the process
    std::thread consumer_thread(consumer, data);
    consumer_thread.join();

    return 0;
}
