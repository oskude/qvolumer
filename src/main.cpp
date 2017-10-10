#include <qsingleinstance.h>
#include <QTimer>
#include <QProcess>
#include <QRegularExpression>
#include <volume-splash.h>

// TODO: yeah, in my system its the first percent value, and im lazy...
QRegularExpression reVolume("([0-9]+)%");
QRegularExpression reMute("Mute: (yes|no)");

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
	QString cmd = QString("pactl set-sink-volume @DEFAULT_SINK@ %1\%").arg(volume);
	runCli(cmd);
}

bool getMute ()
{
	QString ret = runCli("pactl list sinks");
	QRegularExpressionMatch mat = reMute.match(ret);
	if (mat.captured(1) == "yes") {
		return true;
	}
	return false;
}

void setMute (bool mute)
{
	QString cmd = QString("pactl set-sink-mute @DEFAULT_SINK@ %1");
	if (mute) {
		cmd = cmd.arg(1);
	} else {
		cmd = cmd.arg(0);
	}
	runCli(cmd);
}

int main (int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSingleInstance instance;
	QTimer *timer = new QTimer();
	VolumeSplash *vsplash = new VolumeSplash();

	QObject::connect(timer, SIGNAL(timeout()), vsplash, SLOT(hide()));
	QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));

	vsplash->setVolume(getVolume());
	vsplash->setMute(getMute());

	//this lambda only gets executed on the first instance
	instance.setStartupFunction([&]() -> int {
		return 0;
	});

	//new instances send their arguments and this signal is received on the main instance
	QObject::connect(&instance, &QSingleInstance::instanceMessage, [&](QStringList args){
		if(args.size() < 1) {
			return;
		}

		if(args[1] == "-quit") {
			qApp->quit();
			return;
		}

		if (!timer->isActive()) {
			vsplash->show();
		}

		if (args[1] == "toggle") {
			setMute(vsplash->toggle());
		}
		else {
			int v = args[1].toInt();
			setVolume(vsplash->addVolume(v));
		}

		timer->start(1000);
	});

	return instance.singleExec();
}
