#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int priority;
} Process;

Process processes[MAX_PROCESSES];
int processCount = 0;

void addProcess(int id, int priority) {
    if (processCount < MAX_PROCESSES) {
        processes[processCount].id = id;
        processes[processCount].priority = priority;
        processCount++;
    } else {
        printf("Process list is full\n");
    }
}

void sortProcessesByPriority() {
    for (int i = 0; i < processCount - 1; i++) {
        for (int j = 0; j < processCount - i - 1; j++) {
            if (processes[j].priority < processes[j + 1].priority) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void executeProcesses() {
    sortProcessesByPriority();
    for (int i = 0; i < processCount; i++) {
        printf("Executing process with ID: %d and priority: %d\n", processes[i].id, processes[i].priority);
    }
}

int main() {
    addProcess(1, 3);
    addProcess(2, 1);
    addProcess(3, 2);
    addProcess(4, 5);
    addProcess(5, 4);

    printf("Executing processes in order of priority:\n");
    executeProcesses();

    return 0;
}
