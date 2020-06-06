#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

extern int counter [23];

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
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

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Date
int sys_date(void)
{
  struct rtcdate *r;

  if(argptr(0, (void*)&r, sizeof(struct rtcdate)) < 0)
    return -1;
  cmostime(r);
  return 0;
}

//print number of times a given syscall has been called, if given nothing
//return all syscalls along with the number of times they have bn called

int sys_nsyscall(void) {
  int pid;
  int num;
  char sysnames[23][9] = {
       "fork", "exit", "wait", "pipe", "read", "kill",
       "exec", "fstat", "chdir", "dup", "getpid", "sbrk",
       "sleep", "uptime", "open", "write", "mknod", "unlink",
       "link", "mkdir", "close", "date", "nsyscall"
  };

  if(argint(0, &pid) < 0)
    return -1;

  argptr(0, (void *)&num, sizeof(num));

  if (num >= 0)
    cprintf("%s - %d\n", sysnames[num-1], counter[num-1]);
  else
    for (num=0; num < 23; num++)
      cprintf("%s - %d\n", sysnames[num], counter[num]);
      
  return 0;
}
