#include "pulse-audio.h"

PulseAudio::PulseAudio()
{
	// TODO: yeah, in my system its the first percent value, and im lazy...
	this->reVolume = new QRegularExpression("([0-9]+)%");
	this->reMute = new QRegularExpression("Mute: (yes|no)");
}

QString PulseAudio::runCli (QString cmd)
{
	QProcess process;
	process.start(cmd);
	process.waitForFinished(-1);
	return process.readAllStandardOutput();
}

int PulseAudio::getVolume ()
{
	QString ret = this->runCli("pactl list sinks");
	QRegularExpressionMatch mat = this->reVolume->match(ret);
	return mat.captured(1).toInt();
}

void PulseAudio::setVolume (int volume)
{
	QString cmd = QString("pactl set-sink-volume @DEFAULT_SINK@ %1\%").arg(volume);
	this->runCli(cmd);
}

bool PulseAudio::getMute ()
{
	QString ret = this->runCli("pactl list sinks");
	QRegularExpressionMatch mat = this->reMute->match(ret);
	if (mat.captured(1) == "yes") {
		return true;
	}
	return false;
}

void PulseAudio::setMute (bool mute)
{
	QString cmd = QString("pactl set-sink-mute @DEFAULT_SINK@ %1");
	if (mute) {
		cmd = cmd.arg(1);
	} else {
		cmd = cmd.arg(0);
	}
	this->runCli(cmd);
}
