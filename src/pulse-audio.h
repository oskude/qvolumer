#ifndef PULSE_AUDIO_H
#define PULSE_AUDIO_H

#include <QProcess>
#include <QRegularExpression>

class PulseAudio
{
public:
	PulseAudio();
	int getVolume ();
	void setVolume (int volume);
	bool getMute ();
	void setMute (bool mute);

private:
	QString runCli (QString cmd);
	QRegularExpression *reVolume;
	QRegularExpression *reMute;
};

#endif // PULSE_AUDIO_H
