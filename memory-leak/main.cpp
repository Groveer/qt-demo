#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *p = nullptr;
    while (true) {
        unsigned long n;
        printf("请输入需要申请的内存数量：");
        scanf("%lu", &n);
        if (n <= 0) {
            continue;
        }
        n *= 1024 * 1024;
        // 动态申请内存
        p = (char *)malloc(n * sizeof(char));
        memset(p, 65, n);
        printf("申请的内存地址：%p\n", p);
    }
    // 释放内存
    free(p);
    return 0;
}
