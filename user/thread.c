#include "user/thread.h"
#include "kernel/types.h"
#include "user/user.h"

const int PGSIZE = 4096;

int thread_create(void *(start_routine)(void*), void *arg) {
    void *stack_ptr = (void *)malloc(sizeof(void) * PGSIZE);
    int threadId = clone(stack_ptr);

    if(threadId == 0) {
        (*start_routine)(arg);
        exit(0);
    }

    return 0;
}

void lock_init(struct lock_t* lock) {
    lock->locked = 0;
}

void lock_acquire(struct lock_t*lock) {
    while(__sync_lock_test_and_set(&lock->locked, 1) != 0);
    __sync_synchronize();
}

void lock_release(struct lock_t* lock) {
    __sync_synchronize();
    __sync_lock_test_and_set(&lock->locked, 0);
}