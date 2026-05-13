// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr
/*
  mkdir("/patient");
  mkdir("/dosage");
  mkdir("/device");
  mkdir("/audit");
 // /patient/records (owned by patient, uid=1, read-only)
  fd = open("/patient/records", O_CREATE | O_RDWR);
  if(fd >= 0){
    chown("/patient/records", 1, 0);  // uid=1 (patient)
    chmod("/patient/records", 0444);  // read-only for owner, no access for others
    close(fd);
  }
  
  // /dosage/insulin.log (owned by doctor, uid=2)
  fd = open("/dosage/insulin.log", O_CREATE | O_RDWR);
  if(fd >= 0){
    chown("/dosage/insulin.log", 2, 0);  // uid=2 (doctor)
    chmod("/dosage/insulin.log", 0644);  // owner read/write, others read-only
    close(fd);
  }
  
  // /device/config (owned by admin, uid=0)
  fd = open("/device/config", O_CREATE | O_RDWR);
  if(fd >= 0){
    chown("/device/config", 0, 0);  // uid=0 (admin)
    chmod("/device/config", 0600);   // only admin can read/write
    close(fd);
  }
  
  // /audit/syscall.log (owned by admin, uid=0)
  fd = open("/audit/syscall.log", O_CREATE | O_RDWR);
  if(fd >= 0){
    chown("/audit/syscall.log", 0, 0);  // uid=0 (admin)
    chmod("/audit/syscall.log", 0600);   // only admin can read/write
    close(fd);
  }
  
  // Write initial header to audit log
  fd = open("/audit/syscall.log", O_RDWR);
  if(fd >= 0){
    write(fd, "=== Audit Log Initialized ===\n", 30);
    close(fd);
  }
*/
  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
