#include "lib/demo.h"

#include <cxxabi.h>
#include <dapplication.h>

#include <QCoreApplication>

#include <iostream>
#include <regex>
#include <type_traits>
#include <typeinfo>

#include <dlfcn.h>

// std::vector<std::string> string_split(const std::string &str, const std::string &delim)
// {
//     std::regex reg(delim);
//     std::vector<std::string> elems(std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
//                                    std::sregex_token_iterator());
//     return elems;
// }

void replace(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return;
    str.replace(start_pos, from.length(), to);
}

#define Func(func)

template<typename R, typename T, typename... Args>
R call(T *obj, R (T::*func)(Args...), const std::string &func_name, Args &&...args)
{
    std::string func_name_mangled = typeid(func).name();
    const auto is_void = std::is_same<R, void>::value;
    if (!is_void) {
        replace(func_name_mangled, typeid(R).name(), "");
    }
    { // get mangled name
        const auto str = is_void ? "EFv" : "EF";
        std::string ss = "";
        ss += typeid(T).name();
        ss.pop_back();
        replace(func_name_mangled,
                "M" + ss + str,
                "_Z" + ss + std::to_string((int)func_name.size()) + func_name + 'E');
        func_name_mangled.pop_back();
        std::cout << func_name_mangled << std::endl;
    }
    void *funcPtr = dlsym(RTLD_DEFAULT, func_name_mangled.c_str());
    qDebug() << funcPtr;
    if (funcPtr) {
        return (obj->*(func))(std::forward<Args>(args)...);
    } else {
        std::cerr << "Function not found in sym: " << func_name << std::endl;
    }
    return R();
}

int main(int argc, char *argv[])
{
    using abi_demo::Demo;
    using Dtk::Widget::DApplication;
    DApplication app(argc, argv);
    // const QString license = "test";
    // call(&app, &DApplication::setApplicationLicense, "setApplicationLicense", license);
    // qDebug() << app.applicationLicense();
    // qDebug() << call(&app, &DApplication::applicationLicense, "applicationLicense");
    Demo a;
    qDebug() << "begin";
    call(&a, &Demo::doSome, "doSome", QString("hello world!"), abi_demo::Arg());
    qDebug() << call(&a, &Demo::some, "some");
    qDebug() << call(&a, &Demo::some1, "some1", QChar('2'));
    return app.exec();
}
