#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64 sys_schedstatistics (void) {
  int n,program_val;
  argint(0, &n);
  argint(1, &program_val);
  print_scheduling_statistics();
  return 0;
}

uint64 sys_schedtickets(void) {
  int n;
  argint(0, &n);
  print_scheduling_tickets(n);
  return 0;
}

uint64 sys_clone(void) {
  uint64 stack_ptr;
  argaddr(0, &stack_ptr);
  return clone((void*)stack_ptr);
}

uint64 sys_hello(void) {
  int n;
  argint(0, &n);
  print_hello(n);
  return 0;
} 

uint64 sys_info(void) {
  int n;
  argint(0, &n);

  return print_info(n);
}


uint64 sys_procinfo(void) {
  uint64 num;
  argaddr(0, &num);
  return print_sysproc(num);
}

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
