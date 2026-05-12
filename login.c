#include "types.h"
#include "stat.h"
#include "user.h"

char user[20];
char pass[20];

int
main(void)
{
  int uid;

  while(1){
    printf(1, "Username: ");
    gets(user, sizeof(user));

    printf(1, "Password: ");
    gets(pass, sizeof(pass));

    user[strlen(user)-1] = 0;
    pass[strlen(pass)-1] = 0;

    if(strcmp(user, "admin") == 0 &&
   strcmp(pass, "admin123") == 0)
  uid = 0;

else if(strcmp(user, "doctor") == 0 &&
        strcmp(pass, "doctor123") == 0)
  uid = 2;

else if(strcmp(user, "patient") == 0 &&
        strcmp(pass, "patient123") == 0)
  uid = 1;

else
  uid = -1;

    if(uid >= 0){
      printf(1, "Login successful. UID=%d\n", uid);
      break;
    }

    printf(1, "Invalid credentials\n");
  }

  exec("sh", 0);

  exit();
}
