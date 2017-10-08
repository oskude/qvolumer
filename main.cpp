#include <qsingleinstance.h>
#include <QTimer>
#include <QSlider>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSingleInstance instance;
    QTimer *timer = new QTimer();

    QDialog *splash = new QDialog;
    QObject::connect(timer, SIGNAL(timeout()), splash, SLOT(hide()));
    QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setParent(splash);

    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setValue(50);

    //this lambda only gets executed on the first instance
    instance.setStartupFunction([&]() -> int {
        return 0;
    });

    //new instances send their arguments and this signal is received on the main instance
    QObject::connect(&instance, &QSingleInstance::instanceMessage, [&](QStringList args){
        if(args.size() > 1 && args[1] == "-quit") {
            qApp->quit();
            return;
        }

        int addValue = args[1].toInt();
        int newValue = slider->value() + addValue;
        newValue = newValue < 0 ? 0 : newValue;
        newValue = newValue > 100 ? 100 : newValue;

        if (!timer->isActive()) {
            splash->show();
        }

        slider->setValue(newValue);
        timer->start(1000);
    });

    return instance.singleExec();
}
