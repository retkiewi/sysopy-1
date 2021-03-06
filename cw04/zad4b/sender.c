#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

bool catching_signals = true;
int received_count = 0;
int pid;

void sigusr1_handle() {
    received_count++;
}

int main(int argc, char** argv) {
    pid = atoi(argv[1]);
    int sig_count = atoi(argv[2]);

    signal(SIGUSR1, sigusr1_handle);

    for(int i = 0; i < sig_count; i++) {
        usleep(1000);
        kill(pid, SIGUSR1);
        pause();
    }
    kill(pid, SIGUSR2);

    printf("Received %d signals, expected %d.\n", received_count, sig_count);

    return 0;
}