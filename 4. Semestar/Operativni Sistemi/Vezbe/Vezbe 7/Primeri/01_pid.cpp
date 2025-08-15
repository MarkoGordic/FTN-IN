#include <iostream>
#include <unistd.h>


int main() {
    pid_t roditelj_pid, moj_pid;

    roditelj_pid = getppid();  // dobavlja se PID roditeljskog procesa trenutni procesa

    std::cout << "PID roditelja trenutnog procesa: " << roditelj_pid << std::endl;

    moj_pid = getpid();  // dobavlja se PID trenutnog procesa (proces koji obavlja kod koji vidite ovde)

    std::cout << "PID trenutnog procesa: " << moj_pid << std::endl;

    return 0;
}
