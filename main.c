#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    puts("Please enter action");
    puts("1 : Create task:");
    puts("2 : Show sorted tasks");
    int command = 0;
    while (scanf("%d", &command) == 1) {
        switch (command) {
            case 1:
                createTask();
                break;

            case 2:
                outputTasks();
                break;

            default:
                puts("Wrong command");
        }
    }

    return 0;
}