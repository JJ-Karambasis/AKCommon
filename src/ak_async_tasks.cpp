
#ifdef AK_WINDOWS

struct win32_async_task_queue : ak_async_task_queue
{
    HANDLE Semaphore;
};

ak_bool AK_Internal__PerformTask(win32_async_task_queue* TaskQueue, ak_arena* ThreadArena)
{
    ak_i32 NextEntryToRead = TaskQueue->NextEntryToRead;
    ak_i32 NewNextEntryToRead = (NextEntryToRead+1) % AK_ASYNC_TASK_COUNT;
    if(NextEntryToRead != TaskQueue->NextEntryToWrite)
    {
        ak_i32 Index = InterlockedCompareExchange((LONG volatile*)&TaskQueue->NextEntryToRead, NewNextEntryToRead, NextEntryToRead);
        if(Index == NextEntryToRead)
        {
            TaskQueue->AsyncTasks[Index].State = AK_ASYNC_TASK_STATE_PROCESSING;
            TaskQueue->AsyncTasks[Index].Callback(ThreadArena, TaskQueue->AsyncTasks[Index].UserData);     
            InterlockedIncrement((LONG volatile*)&TaskQueue->CompletionCount);
            TaskQueue->AsyncTasks[Index].State = AK_ASYNC_TASK_STATE_NONE;
        }
    }
    else return false;
    
    return true;
}

ak_async_task* ak_async_task_queue::AddTask(ak_async_task_callback* Callback, void* UserData)
{
    ak_i32 NewNextEntryToWrite = (NextEntryToWrite+1) % AK_ASYNC_TASK_COUNT;
    AK_Assert(NewNextEntryToWrite != NextEntryToRead, "Append to much work for work queue. Please increase MAX_WORK_QUEUE_ENTRIES");            
    ak_async_task* Task = AsyncTasks + NextEntryToWrite;
    Task->Callback = Callback;
    Task->UserData = UserData;
    Task->State = AK_ASYNC_TASK_STATE_STARTED;
    CompletionGoal++;    
    _WriteBarrier();
    NextEntryToWrite = NewNextEntryToWrite;
    ReleaseSemaphore(((win32_async_task_queue*)this)->Semaphore, 1, 0);
    return Task;
}

void ak_async_task_queue::CompleteAllTasks(ak_arena* ThreadArena)
{
    while(CompletionGoal != CompletionCount)    
        AK_Internal__PerformTask((win32_async_task_queue*)this, ThreadArena);    
    
    CompletionGoal  = 0;
    CompletionCount = 0;
}

DWORD WINAPI AK_Internal__PlatformThreadProc(LPVOID lpParameter)
{
    win32_async_task_queue* TaskQueue = (win32_async_task_queue*)lpParameter;    
    
    ak_arena* ThreadArena = AK_CreateArena(AK_Megabyte(1));
    
    for(;;)
    {
        ak_temp_arena TempArena = ThreadArena->BeginTemp();
        if(!AK_Internal__PerformTask(TaskQueue, ThreadArena))
            WaitForSingleObjectEx(TaskQueue->Semaphore, INFINITE, FALSE);
        ThreadArena->EndTemp(&TempArena);
    }
}

ak_async_task_queue* AK_CreateAsyncTaskQueue(ak_u32 NumThreads)
{
    win32_async_task_queue* TaskQueue = (win32_async_task_queue*)AK_Allocate(sizeof(win32_async_task_queue));
    TaskQueue->Semaphore = CreateSemaphoreEx(0, 0, NumThreads, 0, 0, SEMAPHORE_ALL_ACCESS);
    for(ak_u32 ThreadIndex = 0; ThreadIndex < NumThreads; ThreadIndex++)    
        CloseHandle(CreateThread(NULL, 0, AK_Internal__PlatformThreadProc, TaskQueue, 0, NULL));        
    return TaskQueue;
}

#endif

void AK_DeleteAsyncTaskQueue(ak_async_task_queue* TaskQueue)
{
    if(TaskQueue)
        AK_Free(TaskQueue);
}

void ak_async_task::Wait()
{
    while(State != AK_ASYNC_TASK_STATE_NONE) _mm_pause();
}