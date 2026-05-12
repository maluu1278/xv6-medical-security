#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf(1, "Usage: userdel username\n");
    exit();
  }

  if(deluser(argv[1]) == 0)
    printf(1, "User deleted\n");
  else
    printf(1, "User not found\n");

  exit();
}
