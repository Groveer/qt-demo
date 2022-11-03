#include <iostream>
#include <string>
#include <fmt/core.h>

int main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    // VERSION 宏使用示例，可使用‘cmake -DVERSION=1.1.1’来指定不同的值
    std::string version;
#ifdef VERSION
    version = VERSION;
#else
    version = "1.0.1"
#endif  // DEBUG
    fmt::print("test version: {}!\n", version);
    return 0;
}
