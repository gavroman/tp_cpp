#ifndef PROJECT_INCLUDE_TASK_H_
#define PROJECT_INCLUDE_TASK_H_

#define TASK_OK 0
#define TASK_FAILED -1

typedef struct date_struct task_date;
struct date_struct {
    int year;
    int month;
    int day;
    int (*print_func)(const task_date * date);
};

typedef struct task_struct task;
struct task_struct {
    int id;
    int priority;
    char * description;
    task_date date;
};

typedef struct task_manager_struct task_manager;
struct task_manager_struct {
    task ** tasks;  // pointer to array of pointers to struct tsk
    int size;
    int real_size;
};

task_manager * create_task_manager();
task * create_task();

int add_task(task_manager ** manager, task * tsk);
int sort_tasks(task_manager * manager);
int output_sorted_tasks(const task_manager * manager);

int free_task_data(task * tsk);
int free_task_manager_data(task_manager * manager);


#endif  // PROJECT_INCLUDE_TASK_H_
