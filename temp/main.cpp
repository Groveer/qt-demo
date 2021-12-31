#include <stdio.h>
#include <deepin_pw_check.h>

int main(int argc, char **argv)
{
    PW_ERROR_TYPE error = deepin_pw_check("root", "uos123!!", LEVEL_STRICT_CHECK, nullptr);
    printf("error:%d", error);
    return 0;
}
