#include <QString>

namespace abi_demo {
class Demo
{
public:
    Demo();
    Demo(Demo &&) = default;
    Demo(const Demo &) = default;
    Demo &operator=(Demo &&) = default;
    Demo &operator=(const Demo &) = default;
    ~Demo();

    void doSome(const QString &str);

private:
};

} // namespace abi_demo
