#include <qsingleinstance.h>
#include <QTimer>
#include <QSlider>
#include <QDialog>
#include <QProcess>
#include <QRegularExpression>

// TODO: yeah, in my system its the first percent value, and im lazy...
QRegularExpression reVolume("([0-9]+)%");

QString runCli (QString cmd)
{
    QProcess process;
    process.start(cmd);
    process.waitForFinished(-1);
    return process.readAllStandardOutput();
}

int getVolume ()
{
    QString ret = runCli("pactl list sinks");
    QRegularExpressionMatch mat = reVolume.match(ret);
    return mat.captured(1).toInt();
}

void setVolume (int volume)
{
    QString cmd = QString("pactl set-sink-volume 0 %1\%").arg(volume);
    runCli(cmd);
}

int main (int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSingleInstance instance;
    QTimer *timer = new QTimer();
    QDialog *splash = new QDialog(Q_NULLPTR, Qt::SplashScreen);
    QSlider *slider = new QSlider(Qt::Horizontal);

    slider->setParent(splash);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setValue(getVolume());

    QObject::connect(timer, SIGNAL(timeout()), splash, SLOT(hide()));
    QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));

    // TODO: is this the correct way for initial resize and position?
    splash->show();
    splash->hide();

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
        setVolume(newValue);
        timer->start(1000);
    });

    return instance.singleExec();
}
