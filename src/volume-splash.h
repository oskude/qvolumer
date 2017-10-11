#ifndef VOLUME_SPLASH_H
#define VOLUME_SPLASH_H

#include <QDialog>
#include <QQuickWidget>
#include <QQuickItem>

class VolumeSplash : public QDialog
{
	Q_OBJECT
public:
	explicit VolumeSplash(QDialog *parent = nullptr);
	void setMute(bool state);
	bool toggle();
	int setVolume(int vol);
	int addVolume(signed int vol);

private:
	QQuickWidget *w;
	QQuickItem *ui;
	int volume;

signals:

public slots:
};

#endif // VOLUME_SPLASH_H
