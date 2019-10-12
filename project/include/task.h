#ifndef PROJECT_INCLUDE_TASK_H_
#define PROJECT_INCLUDE_TASK_H_

#define TASK_OK 0
#define TASK_FAILED -1

typedef struct date_struct Date;
struct date_struct {
    int year;
    int month;
    int day;
};

typedef struct task_struct Task;
struct task_struct {
    int id;
    int priority;
    char * description;
    Date date;
};

typedef struct task_manager_struct Task_manager;
struct task_manager_struct {
    Task ** tasks;  // pointer to array of pointers to struct task
    int size;
    int real_size;
};

Task_manager * create_task_manager();
Task * create_task();

int add_task(Task_manager ** task_manager, Task * task);
int sort_tasks(Task_manager * task_manager);
int output_sorted_tasks(Task_manager * task_manager);

int free_task_data(Task * task);
int free_task_manager_data(Task_manager * task_manager);


#endif  // PROJECT_INCLUDE_TASK_H_
