#include "volume-splash.h"

VolumeSplash::VolumeSplash(QDialog *parent) : QDialog(parent)
{
	this->setWindowFlag(Qt::SplashScreen);

	this->w = new QQuickWidget;
	this->w->setSource(QUrl("qrc:volume-splash.qml"));
	this->w->setParent(this);

	QQuickItem *rootObject = this->w->rootObject();
	this->ui = rootObject;

	// TODO: is this the correct way for initial resize and position?
	this->show();
	this->hide();

	this->volume = 0;
}

void VolumeSplash::setMute(bool state)
{
	this->ui->setProperty("muted", state);
}

bool VolumeSplash::toggle()
{
	bool state = this->ui->property("muted").toBool();
	this->ui->setProperty("muted", !state);
	return !state;
}

int VolumeSplash::setVolume(int vol)
{
	if (vol < 0) vol = 0;
	else if (vol > 100) vol = 100;
	this->ui->setProperty("volume", vol / 100.0);
	this->volume = vol;
	return this->volume;
}

int VolumeSplash::addVolume(signed int vol)
{
	this->setVolume(this->volume + vol);
	return this->volume;
}
