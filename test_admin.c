#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
  printf(1, "Current UID: %d\n", getuid());
  
  if(getuid() == 0){
    printf(1, "Admin mode - can access all files\n");
  } else {
    printf(1, "Regular user - permissions enforced\n");
  }
  exit();
}

