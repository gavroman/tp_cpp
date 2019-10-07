#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "task.h"

Task_manager * create_task_manager() {
    Task_manager * task_mngr = (Task_manager *)malloc(sizeof(Task_manager));
    task_mngr->real_size = 0;
    task_mngr->size = 4;
    task_mngr->tasks = (Task **)malloc(task_mngr->size * sizeof(Task*));
    return task_mngr;
}

Task * create_task() {
    Task * task = (Task *)malloc(sizeof(Task));

    puts("Enter task ID :");
    scanf("%d", &task->id);

    puts("Enter task priority :");
    scanf("%d", &task->priority);

    puts("Enter task description :");
    getchar();  // removing '\n' after scanf() in stdin
    task->description = NULL;
    size_t len = 0;
    ssize_t nread = getline(&task->description, &len, stdin);
    task->description[nread - 1] = '\0';

    puts("Enter task creation date in format DD MM YYYY :");
    scanf("%d%d%d", &task->date.day, &task->date.month, &task->date.year);

    return task;
}

void add_task(Task_manager ** task_manager, Task * task) {
    if ((*task_manager)->real_size == (*task_manager)->size) {
        (*task_manager)->size *= 2;
        Task ** new_tasks = (Task **)malloc((*task_manager)->size * sizeof(Task*));
        memcpy(new_tasks, (*task_manager)->tasks, (*task_manager)->real_size * sizeof(Task*));
        free((*task_manager)->tasks);
        (*task_manager)->tasks = new_tasks;
        puts("ZALUPA");
    }

    (*task_manager)->tasks[(*task_manager)->real_size] = task;
    (*task_manager)->real_size++;
    puts("Added");
}

int comparator(Task * task1, Task * task2) {
    if (task1->priority > task2->priority) {
        return 1;
    } else if (task1->priority < task2->priority) {
        return -1;
    } else {  // need to compare date
        if (task1->date.year < task2->date.year) {
            return 1;
        } else if (task1->date.year > task2->date.year) {
            return -1;
        } else {
            if (task1->date.month < task2->date.month) {
                return 1;
            } else if (task1->date.month > task2->date.month) {
                return -1;
            } else {
                if (task1->date.day < task2->date.day) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }
    return 0;
}


void sort_tasks(Task_manager * task_manager) {
    qsort(task_manager->tasks,
          task_manager->real_size,
          sizeof(Task*),
          (int(*)(const void *, const void *))comparator);
}

void output_tasks(Task_manager * task_manager) {
    sort_tasks(task_manager);
    for (int i = 0; i != task_manager->real_size; i++) {
        puts("_________________________________________");
        Task * task = task_manager->tasks[i];
        printf("Task ID: %d\n", task->id);
        printf("Priority: %d\n", task->priority);
        printf("Description: %s\n", task->description);
        printf("Date: %d.%d.%d\n", task->date.day, task->date.month, task->date.year);
    }
    puts("_________________________________________");
}


void free_task_manager_data(Task_manager * task_manager) {
    for (int i = 0; i != task_manager->real_size; i++) {
        free(task_manager->tasks[i]->description);
        free(task_manager->tasks[i]);
    }
    free(task_manager->tasks);
    free(task_manager);
}
