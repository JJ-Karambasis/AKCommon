#ifndef AK_ATOMIC_H
#define AK_ATOMIC_H

#undef AK_ReadBarrier
#undef AK_WriteBarrier

#ifdef AK_MSVC_COMPILER
#define AK_ReadBarrier() _ReadBarrier()
#define AK_WriteBarrier() _WriteBarrier()
#endif

struct ak_lock
{
    ak_i64 volatile Target;
    ak_i64 volatile Current;
    
    ak_bool IsLocked();
    void Begin();
    void End();
};

#endif