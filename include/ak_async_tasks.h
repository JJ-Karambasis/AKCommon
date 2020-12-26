#ifndef AK_ASYNC_TASKS_H
#define AK_ASYNC_TASKS_H

#ifndef AK_ASYNC_TASK_COUNT
#define AK_ASYNC_TASK_COUNT 2048
#endif

#define AK_ASYNC_TASK_CALLBACK(name) void name(struct ak_arena* ThreadArena, void* UserData)
typedef AK_ASYNC_TASK_CALLBACK(ak_async_task_callback);

enum ak_async_task_state
{
    AK_ASYNC_TASK_STATE_NONE,
    AK_ASYNC_TASK_STATE_STARTED,
    AK_ASYNC_TASK_STATE_PROCESSING
};

struct ak_async_task
{
    ak_async_task_state volatile State;
    ak_async_task_callback* Callback;
    void* UserData;
    void Wait();
};

struct ak_async_task_queue
{
    ak_i32 volatile NextEntryToWrite;
    ak_i32 volatile NextEntryToRead;
    ak_i32 volatile CompletionGoal;
    ak_i32 volatile CompletionCount;
    ak_async_task   AsyncTasks[AK_ASYNC_TASK_COUNT];
    
    ak_async_task* AddTask(ak_async_task_callback* Callback, void* UserData);
    void CompleteAllTasks(ak_arena* ThreadArena);
};

ak_async_task_queue* AK_CreateAsyncTaskQueue(ak_u32 NumThreads);
void AK_DeleteAsyncTaskQueue(ak_async_task_queue* TaskQueue);

#endif