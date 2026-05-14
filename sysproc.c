#include "types.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
// Function prototypes
extern int argstr(int n, char **p);
extern int argint(int n, int *p);
extern void begin_op(void);
extern void end_op(void);
struct inode* namei(char *path);
void iupdate(struct inode *ip);

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
sys_getuid(void)
{
  return myproc()->uid;
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
sys_chown(void)
{
  char *path;
  int uid, gid;
  struct inode *ip;
  
  if(argstr(0, &path) < 0 || argint(1, &uid) < 0 || argint(2, &gid) < 0)
    return -1;
  
  begin_op();  // ADD THIS
  
  ip = namei(path);
  if(ip == 0){
    end_op();  // ADD THIS
    return -1;
  }
  
  ilock(ip);
  ip->uid = uid;
  ip->gid = gid;
  iupdate(ip);
  iunlock(ip);
  iput(ip);
  
  end_op();  // ADD THIS
  
  return 0;
}

int
sys_chmod(void)
{
  char *path;
  int mode;
  struct inode *ip;
  
  if(argstr(0, &path) < 0 || argint(1, &mode) < 0)
    return -1;
  
  begin_op();  // ADD THIS
  
  ip = namei(path);
  if(ip == 0){
    end_op();  // ADD THIS
    return -1;
  }
  
  ilock(ip);
  ip->mode = mode;
  iupdate(ip);
  iunlock(ip);
  iput(ip);
  
  end_op();  // ADD THIS
  
  return 0;
}

