#include <gtest/gtest.h>

extern "C" {
    #include "task.h"
}

// case_1
TEST(task, create_task) {
    stdin = freopen("tests/data/in_1.txt", "r", stdin);

    task * tsk = create_task();
    EXPECT_EQ(tsk->id, 201314);
    EXPECT_EQ(tsk->priority, 10);
    EXPECT_EQ(std::string(tsk->description), "Very important task");
    EXPECT_EQ(tsk->date.day, 9);
    EXPECT_EQ(tsk->date.month, 9);
    EXPECT_EQ(tsk->date.year, 1999);

    EXPECT_EQ(free_task_data(tsk), TASK_OK);
    fclose(stdin);
}

// case_0 testing free
TEST(task_manager, create_task_manager) {
    task_manager * task_mngr = create_task_manager();

    EXPECT_EQ(free_task_manager_data(task_mngr), TASK_OK);
    EXPECT_EQ(free_task_manager_data(nullptr), TASK_FAILED);
    EXPECT_EQ(free_task_data(nullptr), TASK_FAILED);

    return;
}

// case_2 adding 2 tasks in task manager
TEST(task_manager, add_task) {
    stdin = freopen("tests/data/in_2.txt", "r", stdin);

    task * task1 = create_task();
    task * task2 = create_task();
    task_manager * task_mngr = create_task_manager();

    EXPECT_EQ(add_task(&task_mngr, nullptr), TASK_FAILED);
    EXPECT_EQ(add_task(nullptr, task1), TASK_FAILED);

    EXPECT_EQ(add_task(&task_mngr, task1), TASK_OK);
    EXPECT_EQ(add_task(&task_mngr, task2), TASK_OK);

    // task1 struct
    EXPECT_EQ(task_mngr->tasks[0]->id, 201314);
    EXPECT_EQ(task_mngr->tasks[0]->priority, 10);
    EXPECT_EQ(std::string(task_mngr->tasks[0]->description), "Very important task 1");
    EXPECT_EQ(task_mngr->tasks[0]->date.day, 9);
    EXPECT_EQ(task_mngr->tasks[0]->date.month, 9);
    EXPECT_EQ(task_mngr->tasks[0]->date.year, 1999);
    // task2 struct
    EXPECT_EQ(task_mngr->tasks[1]->id, 10);
    EXPECT_EQ(task_mngr->tasks[1]->priority, 9);
    EXPECT_EQ(std::string(task_mngr->tasks[1]->description), "Very important task 2");
    EXPECT_EQ(task_mngr->tasks[1]->date.day, 18);
    EXPECT_EQ(task_mngr->tasks[1]->date.month, 12);
    EXPECT_EQ(task_mngr->tasks[1]->date.year, 1998);

    EXPECT_EQ(free_task_manager_data(task_mngr), TASK_OK);

    fclose(stdin);
}

// case_3 sorting tasks on priority
TEST(task_manager, sort_tasks) {
    EXPECT_EQ(output_sorted_tasks(nullptr), TASK_FAILED);

    stdin = freopen("tests/data/in_3.txt", "r", stdin);

    task_manager * task_mngr = create_task_manager();
    for (int i = 0; i != 4; i++) {
        EXPECT_EQ(add_task(&task_mngr, create_task()), TASK_OK);
    }
    EXPECT_EQ(output_sorted_tasks(task_mngr), TASK_OK);

    EXPECT_EQ(task_mngr->tasks[0]->id, 412345);
    EXPECT_EQ(task_mngr->tasks[1]->id, 2323);
    EXPECT_EQ(task_mngr->tasks[2]->id, 189);
    EXPECT_EQ(task_mngr->tasks[3]->id, 33233);

    for (int i = 0; i != 14; i++) {
        EXPECT_EQ(add_task(&task_mngr, create_task()), TASK_OK);
    }
    EXPECT_EQ(output_sorted_tasks(task_mngr), TASK_OK);

    EXPECT_EQ(task_mngr->tasks[0]->id, 6876);
    EXPECT_EQ(task_mngr->tasks[1]->id, 656);
    EXPECT_EQ(task_mngr->tasks[2]->id, 6654);
    EXPECT_EQ(task_mngr->tasks[3]->id, 7651);
    EXPECT_EQ(task_mngr->tasks[4]->id, 5354);
    EXPECT_EQ(task_mngr->tasks[5]->id, 232);
    EXPECT_EQ(task_mngr->tasks[6]->id, 412345);
    EXPECT_EQ(task_mngr->tasks[7]->id, 123);
    EXPECT_EQ(task_mngr->tasks[8]->id, 34);
    EXPECT_EQ(task_mngr->tasks[9]->id, 2323);
    EXPECT_EQ(task_mngr->tasks[10]->id, 454);
    EXPECT_EQ(task_mngr->tasks[11]->id, 578);
    EXPECT_EQ(task_mngr->tasks[12]->id, 189);
    EXPECT_EQ(task_mngr->tasks[13]->id, 33233);
    EXPECT_EQ(task_mngr->tasks[14]->id, 7678);

    EXPECT_EQ(free_task_manager_data(task_mngr), TASK_OK);
    fclose(stdin);
}

int main(int argc, char *argv[]) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
