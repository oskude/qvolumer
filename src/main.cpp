#include <qsingleinstance.h>
#include <QTimer>
#include <volume-splash.h>
#include <pulse-audio.h>

int main (int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSingleInstance instance;
	QTimer *timer = new QTimer();
	VolumeSplash *vsplash = new VolumeSplash();
	PulseAudio *paudio = new PulseAudio();

	QObject::connect(timer, SIGNAL(timeout()), vsplash, SLOT(hide()));
	QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));

	vsplash->setVolume(paudio->getVolume());
	vsplash->setMute(paudio->getMute());

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
			paudio->setMute(vsplash->toggle());
		}
		else {
			int v = args[1].toInt();
			paudio->setVolume(vsplash->addVolume(v));
		}

		timer->start(1000);
	});

	return instance.singleExec();
}
