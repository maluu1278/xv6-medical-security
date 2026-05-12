#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc < 4){
    printf(1, "Usage: useradd username password uid\n");
    exit();
  }

  int uid = atoi(argv[3]);

  adduser(argv[1], argv[2], uid);

  printf(1, "User added\n");

  exit();
}
