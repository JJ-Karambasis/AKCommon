#ifndef ATOMIC_H
#define ATOMIC_H

#ifdef MSVC_COMPILER

#define CompletePreviousReadsBeforeFutureReads _ReadBarrier()
#define CompletePreviousWritesBeforeFutureWrites _WriteBarrier()

inline u64 AtomicAdd(u64 volatile *Value, u64 Addend)
{
    // NOTE(casey): Returns the original value _prior_ to adding
    u64 Result = _InterlockedExchangeAdd64((__int64 volatile *)Value, Addend);    
    return(Result);
}

#endif

struct lock
{
    u64 volatile Target;
    u64 volatile Current;
};

inline b32 
IsLocked(lock* Lock)
{
    b32 Result = (Lock->Target != Lock->Current);
    return Result;
}

inline void
BeginLock(lock* Lock)
{
    u64 Target = AtomicAdd(&Lock->Target, 1);
    while(Target != Lock->Current) { _mm_pause(); }
}

inline void
EndLock(lock* Lock)
{
    AtomicAdd(&Lock->Current, 1);
}


#endif