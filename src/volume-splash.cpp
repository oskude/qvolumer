#include "volume-splash.h"

VolumeSplash::VolumeSplash(QDialog *parent) : QDialog(parent)
{
	this->setWindowFlag(Qt::SplashScreen);

	this->slider = new QSlider(Qt::Horizontal);
	this->slider->setParent(this);
	this->slider->setMinimum(0);
	this->slider->setMaximum(100);

	// TODO: is this the correct way for initial resize and position?
	this->show();
	this->hide();
}

void VolumeSplash::setMute(bool state)
{
	this->slider->setDisabled(state);
}

bool VolumeSplash::toggle()
{
	bool state = this->slider->isEnabled();
	this->slider->setDisabled(state);
	return state;
}

int VolumeSplash::setVolume(int vol)
{
	if (vol < 0) vol = 0;
	else if (vol > 100) vol = 100;
	this->slider->setValue(vol);
	return vol;
}

int VolumeSplash::addVolume(signed int vol)
{
	this->setVolume(this->slider->value() + vol);
	return this->slider->value();
}
