#include <stdio.h>
#include "task.h"

int main(int argc, char const *argv[]) {
    puts("Please enter action");
    puts("1      : Create task:");
    puts("2      : Show sorted tasks");
    puts("CTRL^D : exit");

    Task_manager * task_manager = create_task_manager();
    int command = 0;
    while (scanf("%d", &command) == 1) {
        switch (command) {
            case 1:
                add_task(&task_manager, create_task());
                break;
            case 2:
                output_sorted_tasks(task_manager);
                break;

            default:
                puts("Wrong command");
        }
        puts("Please enter action");
        puts("1 : Create task:");
        puts("2 : Show sorted tasks");
    }

    free_task_manager_data(task_manager);
    return 0;
}
