#include <qsingleinstance.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSingleInstance instance;

    //this lambda only gets executed on the first instance
    instance.setStartupFunction([&]() -> int {
        qDebug() << "Instance running! Start another with -quit as first argument to exit";
        return 0;
    });

    //new instances send their arguments and this signal is received on the main instance
    QObject::connect(&instance, &QSingleInstance::instanceMessage, [&](QStringList args){
        qDebug() << "New Instance:" << args;
        if(args.size() > 1 && args[1] == "-quit")
            qApp->quit();
    });

    return instance.singleExec();
}
