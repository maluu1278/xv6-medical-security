#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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

int
sys_sleep(void)
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
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_whoami(void)
{
  return myproc()->uid;
}



int
sys_adduser(void)
{
  char *u;
  char *p;
  int uid;

  if(argstr(0, &u) < 0)
    return -1;

  if(argstr(1, &p) < 0)
    return -1;

  if(argint(2, &uid) < 0)
    return -1;

  return adduser(u, p, uid);
}


int
sys_changepass(void)
{
  char *u;
  char *p;

  if(argstr(0, &u) < 0)
    return -1;

  if(argstr(1, &p) < 0)
    return -1;

  return changepass(u, p);
}


int
sys_deluser(void)
{
  char *u;

  if(argstr(0, &u) < 0)
    return -1;

  return deluser(u);
}




int
sys_auditread(void)
{
  int i;

  cprintf("CURRENT UID = %d\n", myproc()->uid);

  if(myproc()->uid != 0){
    cprintf("Access denied: admin only\n");
    return -1;
  }

  for(i = 0; i < AUDIT_SIZE; i++){
    cprintf("LOG pid=%d uid=%d trap=%d tick=%d\n",
      audit_buffer[i].pid,
      audit_buffer[i].uid,
      audit_buffer[i].trapno,
      audit_buffer[i].tick);
  }

  return 0;
}



int
sys_setuid(void)
{
  int uid;

  if(argint(0, &uid) < 0)
    return -1;

  myproc()->uid = uid;
  myproc()->gid = uid;

  return 0;
}
