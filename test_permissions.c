#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main()
{
  int fd;
  char buf[100];
  
  printf(1, "\n=== Phase 2.3: Kernel Permission Enforcement ===\n\n");
  
  // Test 1: Create a read-only file
  printf(1, "1. Creating read-only file...\n");
  fd = open("/ro_test", O_CREATE | O_RDWR);
  if(fd < 0){
    printf(1, "   FAIL: Cannot create file\n");
    exit();
  }
  write(fd, "secret data", 11);
  close(fd);
  chmod("/ro_test", 0444);  // Read-only for everyone
  printf(1, "   File created with mode 0444 (read-only)\n\n");
  
  // Test 2: Try to write to read-only file (should FAIL)
  printf(1, "2. Trying to write to read-only file...\n");
  fd = open("/ro_test", O_RDWR);
  if(fd < 0){
    printf(1, "   SUCCESS: Write operation was DENIED (correct)\n");
  } else {
    printf(1, "   FAIL: Write operation was ALLOWED (incorrect)\n");
    close(fd);
  }
  
  // Test 3: Try to read from read-only file (should SUCCEED)
  printf(1, "\n3. Trying to read from read-only file...\n");
  fd = open("/ro_test", O_RDONLY);
  if(fd >= 0){
    read(fd, buf, 10);
    printf(1, "   SUCCESS: Read operation was ALLOWED (correct)\n");
    close(fd);
  } else {
    printf(1, "   FAIL: Read operation was DENIED (incorrect)\n");
  }
  
  printf(1, "\n=== Permission Tests Complete ===\n");
  exit();
}
