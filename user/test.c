#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/thread.h"
struct lock_t lock;
int n_threads, n_passes, cur_turn, cur_pass;
void* thread_fn(void *arg)
{
    int thread_id = (uint64)arg;
    int done = 0;
    while (!done) {
        lock_acquire(&lock);
        if (cur_pass >= n_passes) done = 1;
        else if (cur_turn == thread_id) {
            cur_turn = (cur_turn + 1) % n_threads;
            printf("Round %d: thread %d is passing the token to thread %d\n",++cur_pass, thread_id, cur_turn);
        }
        lock_release(&lock);
        sleep(0);
    }
    return 0;
}
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [N_PASSES] [N_THREADS]\n", argv[0]);
    }
    exit(-1);
}