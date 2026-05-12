#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc < 3){
    printf(1, "Usage: passwd username newpassword\n");
    exit();
  }

  changepass(argv[1], argv[2]);

  printf(1, "Password updated\n");

  exit();
}
