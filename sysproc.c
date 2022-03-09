#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

/* added for project begin 2 */
int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  myproc()->sleepleft = n;
  acquire(&tickslock);
  ticks0 = ticks;
  sleep(&ticks, &tickslock);
  if(myproc()->killed){
    release(&tickslock);
    return -1;
  }
  if (ticks - ticks0 < n) {
    cprintf("sys_sleep: wake up too early!\n");
    release(&tickslock);
    return -1;
  }
  release(&tickslock);
  return 0;
}
/* added for project end 2 */

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

/* added for project begin 1 */
#ifndef DEBUG
#define DEBUG 0
#endif

extern uint rseed;
int
sys_srand(void) {
  uint seed;
  if (argint(0, (int *)(&seed)) == -1) {
    cprintf("sys_srand fetch argument error!\n");
    return -1;
  }
  rseed = seed;
  if (DEBUG == 1)
    cprintf("seed is reset to %d\n", rseed);
  return 0;
}
/* added for project end 1 */