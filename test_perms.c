#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main()
{
  int fd;
  char buf[100];
  
  printf(1, "\n=== Testing Kernel Permission Enforcement ===\n\n");
  
  // Create a test file
  printf(1, "1. Creating test file...\n");
  fd = open("/test_perms", O_CREATE | O_RDWR);
  if(fd < 0){
    printf(1, "   FAIL: Cannot create file\n");
    exit();
  }
  write(fd, "original data", 13);
  close(fd);
  printf(1, "   File created\n\n");
  
  // Make it read-only (mode 0444)
  printf(1, "2. Making file read-only (mode 0444)...\n");
  if(chmod("/test_perms", 0444) == 0){
    printf(1, "   chmod SUCCESS\n");
  } else {
    printf(1, "   chmod FAILED\n");
  }
  
  // Try to write (should FAIL)
  printf(1, "\n3. Trying to write to read-only file...\n");
  fd = open("/test_perms", O_RDWR);
  if(fd < 0){
    printf(1, "   SUCCESS: Write operation DENIED (correct)\n");
  } else {
    printf(1, "   FAIL: Write operation ALLOWED (incorrect)\n");
    write(fd, "new data", 8);
    close(fd);
  }
  
  // Try to read (should SUCCEED)
  printf(1, "\n4. Trying to read from read-only file...\n");
  fd = open("/test_perms", O_RDONLY);
  if(fd >= 0){
    read(fd, buf, 20);
    printf(1, "   SUCCESS: Read operation ALLOWED (correct)\n");
    printf(1, "   Read data: %s\n", buf);
    close(fd);
  } else {
    printf(1, "   FAIL: Read operation DENIED (incorrect)\n");
  }
  
  printf(1, "\n=== Test Complete ===\n");
  exit();
}
