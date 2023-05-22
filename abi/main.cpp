#include "lib/demo.h"

#include <cxxabi.h>
#include <dapplication.h>

#include <QCoreApplication>

#include <iostream>

#include <dlfcn.h>

template<class T, class R = void, typename... Args>
R call(T *obj, const std::string func_name, Args... args)
{
    std::map<std::string, std::string> funcMap = {
        { "abi_demo::Demo::doSome", "_ZN8abi_demo4Demo6doSomeERK7QString" },
        { "Dtk::Widget::DApplication::setApplicationLicense",
          "_ZN3Dtk6Widget12DApplication21setApplicationLicenseERK7QString" },
        { "Dtk::Widget::DApplication::applicationLicense",
          "_ZNK3Dtk6Widget12DApplication18applicationLicenseEv" }
    };
    std::string class_name(abi::__cxa_demangle(typeid(T).name(), 0, 0, 0));
    auto search = funcMap.find(class_name + "::" + func_name);
    if (search != funcMap.end()) {
        void *funcPtr = dlsym(RTLD_DEFAULT, search->second.c_str());
        if (funcPtr) {
            typedef R (T::*FuncPtr)(typename std::decay<Args>::type...);

            union {
                FuncPtr member;
                void *ptr;
            } Caster;

            Caster.member = nullptr;
            Caster.ptr = funcPtr;
            auto func = Caster.member;
            return (obj->*(func))(args...);
        } else {
            std::cerr << "Function not found in sym: " << func_name;
        }
    } else {
        std::cerr << "Function not found in map: " << func_name;
    }
    return R();
}

int main(int argc, char *argv[])
{
    using abi_demo::Demo;
    using Dtk::Widget::DApplication;
    DApplication app(argc, argv);
    // app.setApplicationLicense("test");
    call<DApplication>(&app, "setApplicationLicense", QString("test"));
    qDebug() << call<DApplication, QString>(&app, "applicationLicense");
    // call<Demo>(&a, "doSome", QString("hello world!"));``
    qDebug() << "end!";
    return app.exec();
}
