#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main()
{
  int fd;
  struct stat st;
  
  printf(1, "=== Testing chown and chmod ===\n\n");
  
  // Create a test file
  fd = open("/chown_test", O_CREATE | O_RDWR);
  if(fd < 0){
    printf(1, "Failed to create file\n");
    exit();
  }
  close(fd);
  
  // Get initial stats
  printf(1, "Initial file stats:\n");
  if(stat("/chown_test", &st) == 0){
    printf(1, "  mode=%d, uid=%d, gid=%d\n", st.mode, st.uid, st.gid);
  }
  
  // Test chown
  printf(1, "\nTesting chown: setting uid=1, gid=0\n");
  if(chown("/chown_test", 1, 0) == 0){
    printf(1, "  chown SUCCESS\n");
  } else {
    printf(1, "  chown FAILED\n");
  }
  
  // Test chmod
  printf(1, "\nTesting chmod: setting mode=0644\n");
  if(chmod("/chown_test", 0644) == 0){
    printf(1, "  chmod SUCCESS\n");
  } else {
    printf(1, "  chmod FAILED\n");
  }
  
  // Get final stats
  printf(1, "\nFinal file stats:\n");
  if(stat("/chown_test", &st) == 0){
    printf(1, "  mode=%d, uid=%d, gid=%d\n", st.mode, st.uid, st.gid);
  }
  
  printf(1, "\n=== Test Complete ===\n");
  exit();
}
