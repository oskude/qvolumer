#include <qsingleinstance.h>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSingleInstance instance;

    QTimer *timer = new QTimer();
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("/data/projects/qt/qvolumer/splash.png"));
    QObject::connect(timer, SIGNAL(timeout()), splash, SLOT(close()));
    QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));

    //this lambda only gets executed on the first instance
    instance.setStartupFunction([&]() -> int {
        qDebug() << "Instance running! Start another with -quit as first argument to exit";
        return 0;
    });

    //new instances send their arguments and this signal is received on the main instance
    QObject::connect(&instance, &QSingleInstance::instanceMessage, [&](QStringList args){
        qDebug() << "New Instance:" << args;
        if(args.size() > 1 && args[1] == "-quit") {
            qApp->quit();
        }
        if (!timer->isActive()) {
            splash->show();
        }
        timer->start(1000);
    });

    return instance.singleExec();
}
