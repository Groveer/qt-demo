#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void manual_malloc()
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
}

void auto_malloc()
{
    char *p = nullptr;
    unsigned long i = 20000;
    i *= 1024 * 1024;
    p = (char *)malloc(i * sizeof(char));
    memset(p, 65, i);
    while (true) {
        unsigned long n = 100;
        n *= 1024 * 1024;
        // 动态申请内存
        p = (char *)malloc(n * sizeof(char));
        memset(p, 65, n);
        sleep(3);
    }
    // 释放内存
    free(p);
}

int main(int argc, char *argv[])
{
    auto_malloc();
    return 0;
}
