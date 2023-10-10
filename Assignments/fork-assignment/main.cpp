#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;


int main() {

    cout << "Initial process with PID " << getpid() << " started." << endl;

    for (int i = 0; i < 9; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            cerr << "Fork failed." << endl;
            return 1;
        } else if (pid == 0) {
            // Child process
            cout << "Child process " << i + 1 << " with PID " << getpid() << " created by parent with PID " << getppid() << endl;
            exit(0); // exit child after doing its work
        }
    }

    // Parent waits for all child processes to complete
    for (int i = 0; i < 9; ++i) {
        wait(NULL);
    }

    cout << "Parent process with PID " << getpid() << " exiting." << endl;
    return 0;
}