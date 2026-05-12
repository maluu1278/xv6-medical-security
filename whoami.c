#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int uid = whoami();
  printf(1, "UID = %d\n", uid);
  exit();
}
