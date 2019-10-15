#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "task.h"

task_manager * create_task_manager() {
    task_manager * task_mngr = (task_manager *)malloc(sizeof(task_manager));
    if (task_mngr == NULL) {
        return NULL;
    }
    task_mngr->real_size = 0;
    task_mngr->size = 4;
    task_mngr->tasks = (task **)malloc(task_mngr->size * sizeof(task*));
    if (task_mngr->tasks == NULL) {
        free(task_mngr);
        return NULL;
    }
    return task_mngr;
}

int print_date(const task_date * date) {
    printf("task_date: ");
    if (date->day < 10) {
        printf("0");
    }
    printf("%d.", date->day);
    if (date->month < 10) {
        printf("0");
    }
    printf("%d.%d\n", date->month, date->year);
    return TASK_OK;
}

task * create_task() {
    task * tsk = (task *)malloc(sizeof(task));
    if (tsk == NULL) {
        return NULL;
    }

    puts("Enter tsk ID :");
    scanf("%d", &tsk->id);

    puts("Enter tsk priority :");
    scanf("%d", &tsk->priority);

    puts("Enter tsk description :");
    getchar();  // removing '\n' after scanf() in stdin
    tsk->description = NULL;
    size_t len = 0;
    ssize_t nread = getline(&tsk->description, &len, stdin);
    if (nread) {
        tsk->description[nread - 1] = '\0';
    }

    puts("Enter tsk creation date in format DD MM YYYY :");
    scanf("%d%d%d", &tsk->date.day, &tsk->date.month, &tsk->date.year);
    tsk->date.print_func = print_date;

    return tsk;
}

int add_task(task_manager ** manager, task * tsk) {
    if (!manager || !tsk) {
        return TASK_FAILED;
    }
    if (!(*manager)->tasks) {
        return TASK_FAILED;
    }

    if ((*manager)->real_size == (*manager)->size) {
        (*manager)->size *= 2;
        task ** new_tasks = (task **)malloc((*manager)->size * sizeof(task*));
        memcpy(new_tasks, (*manager)->tasks, (*manager)->real_size * sizeof(task*));
        free((*manager)->tasks);
        (*manager)->tasks = new_tasks;
    }

    (*manager)->tasks[(*manager)->real_size] = tsk;
    (*manager)->real_size++;

    return TASK_OK;
}

int comparator(const task ** task1, const task ** task2) {
    const int left_more = -1;
    const int right_more = 1;
    const int equal = 0;
    if ((*task1)->priority < (*task2)->priority) {
        return right_more;
    } else if ((*task1)->priority > (*task2)->priority) {
        return left_more;
    }

    // need to compare date
    if ((*task1)->date.year > (*task2)->date.year) {
        return right_more;
    } else if ((*task1)->date.year < (*task2)->date.year) {
        return left_more;
    }

    if ((*task1)->date.month > (*task2)->date.month) {
        return right_more;
    } else if ((*task1)->date.month < (*task2)->date.month) {
        return left_more;
    }

    if ((*task1)->date.day > (*task2)->date.day) {
        return right_more;
    } else if ((*task1)->date.day < (*task2)->date.day) {
        return left_more;
    }
    return equal;
}

int output_sorted_tasks(const task_manager * manager) {
    if (!manager) {
        return TASK_FAILED;
    }
    if (!manager->tasks) {
        return TASK_FAILED;
    }

    qsort(manager->tasks, manager->real_size, sizeof(task*), comparator);
    for (int i = 0; i != manager->real_size; i++) {
        if (!manager->tasks[i]) {
            return TASK_FAILED;
        }
        if (!manager->tasks[i]->description) {
            return TASK_FAILED;
        }

        task * tsk = manager->tasks[i];
        printf("\nTask ID: %d\n", tsk->id);
        printf("Priority: %d\n", tsk->priority);
        printf("Description: %s\n", tsk->description);
        tsk->date.print_func(&tsk->date);
    }
    putchar('\n');
    return TASK_OK;
}

int free_task_data(task * tsk) {
    if (!tsk) {
        return TASK_FAILED;
    }
    if (!tsk->description) {
        free(tsk);
        return TASK_FAILED;
    }

    free(tsk->description);
    free(tsk);
    return TASK_OK;
}

int free_task_manager_data(task_manager * manager) {
    if (!manager) {
        return TASK_FAILED;
    }
    if (!manager->tasks) {
        free(manager);
        return TASK_FAILED;
    }

    for (int i = 0; i != manager->real_size; i++) {
        free_task_data(manager->tasks[i]);
    }
    free(manager->tasks);
    free(manager);
    return TASK_OK;
}
