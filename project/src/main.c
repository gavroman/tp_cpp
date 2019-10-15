#include <stdio.h>
#include "task.h"

#define EXIT_SUCCESS 0

#define CMD_ADD_TASK 1
#define CMD_OUTPUT_SORTED_TASKS 2

int main(int argc, char const *argv[]) {
    puts("Please enter action");
    puts("1      : Create tsk:");
    puts("2      : Show sorted tasks");
    puts("CTRL^D : exit");

    task_manager * manager = create_task_manager();
    int command = 0;
    while (scanf("%d", &command) == 1) {
        switch (command) {
            case CMD_ADD_TASK:
                add_task(&manager, create_task());
                break;
            case CMD_OUTPUT_SORTED_TASKS:
                output_sorted_tasks(manager);
                break;
            default:
                puts("Wrong command");
        }
        puts("Please enter action");
        puts("1 : Create tsk:");
        puts("2 : Show sorted tasks");
    }

    free_task_manager_data(manager);
    return EXIT_SUCCESS;
}
