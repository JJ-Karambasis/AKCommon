ak_bool ak_lock::IsLocked()
{
    ak_bool Result = (Target != Current);
    return Result;
}

void ak_lock::Begin()
{
    ak_i64 PrevTarget = AK_AtomicAdd64(&Target, 1);
    while(PrevTarget != Current) { _mm_pause(); }
}

void ak_lock::End()
{
    AK_AtomicAdd64(&Current, 1);
}
    
    