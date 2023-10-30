// Available at https://github.com/ofbartels/os-ofbartels/tree/main/Assignments/threads-assignment


#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>       // For O_* constants
#include <sys/mman.h>    // For shared memory
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

const char *shm_name = "/my_shm";
const size_t shm_size = 4096;

int main() {
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, shm_size) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    void *ptr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == 0) {  // Child process
        char *message = "Hello from child!";
        memcpy(ptr, message, strlen(message) + 1);
        cout << "Child added: " << static_cast<char*>(ptr) << " to shared memory." <<endl;
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {  // Parent process
        wait(NULL);  // Wait for child to finish
        cout << "Parent received: " << static_cast<char*>(ptr) << endl;
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Clean up
    if (munmap(ptr, shm_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink(shm_name) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}