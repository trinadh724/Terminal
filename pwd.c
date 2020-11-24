#include "pwd.h"
#include "headers.h"

char pwdstr[2000];

void pwdcommand()
{
    getcwd(pwdstr,2000);
    printf("%s\n",pwdstr);
}