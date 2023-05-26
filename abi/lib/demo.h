#include <QString>

namespace abi_demo {
class Arg
{
public:
    Arg() { printf("Arg(%d)\n", a); }

private:
    int a = 0;
};

class Demo
{
public:
    Demo();
    Demo(Demo &&) = default;
    Demo(const Demo &) = default;
    Demo &operator=(Demo &&) = default;
    Demo &operator=(const Demo &) = default;
    ~Demo();

    // void doSome(const QString &str);
    void doSome(QString str, Arg size);
    QString some();
    QString some1(QChar c);

private:
};

} // namespace abi_demo
