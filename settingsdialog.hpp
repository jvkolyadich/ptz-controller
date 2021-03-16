#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QCloseEvent>
#include <QMessageBox>
#include <QRegExpValidator>

#include <QDebug>
#define DEBUG_SETTINGS false

class SettingsDialog : public QWidget {
	Q_OBJECT
public:
	SettingsDialog(QWidget *parent = nullptr,
		       Qt::WindowFlags f = Qt::Window);
	void sendPowerOff();

public slots:
	void loadSettings();
	void saveSettings();
	void onOkClicked();
	void onCancelClicked();
	void onIpChanged(QString ip)
	{
		m_needsToSave = true;
		if (m_ipRegex.exactMatch(ip)) {
			m_ipField->setStyleSheet("");
			emit changedIp(ip);
			if (DEBUG_SETTINGS)
				qDebug() << "Changed IP to" << ip;
		} else {
			m_ipField->setStyleSheet("color: red");
		}
	};
	void onPortChanged(QString port)
	{
		m_needsToSave = true;
		if (m_portRegex.exactMatch(port)) {
			m_portField->setStyleSheet("");
			emit changedPort(port.toInt());
			if (DEBUG_SETTINGS)
				qDebug() << "Changed port to" << port;
		} else {
			m_portField->setStyleSheet("color: red");
		}
	};
	void onMoveAdjChanged(int val)
	{
		m_needsToSave = true;
		float adjustment = (float)val / 100;
		emit changedMoveAdjustment(adjustment);
		if (DEBUG_SETTINGS)
			qDebug() << "Changed move adjustment to" << adjustment;
	};
	void onMoveAdjWeightChanged(int val)
	{
		m_needsToSave = true;
		float weight = (float)val / 100;
		emit changedMoveAdjWeight(weight);
		if (DEBUG_SETTINGS)
			qDebug() << "Changed move adjustment weight to"
				 << weight;
	};
	void onZoomAdjChanged(int val)
	{
		m_needsToSave = true;
		float adjustment = (float)val / 100;
		emit changedZoomAdjustment(adjustment);
		if (DEBUG_SETTINGS)
			qDebug() << "Changed move adjustment to" << adjustment;
	};
	void onZoomAdjWeightChanged(int val)
	{
		m_needsToSave = true;
		float weight = (float)val / 100;
		emit changedZoomAdjWeight(weight);
		if (DEBUG_SETTINGS)
			qDebug() << "Changed zoom adjustment weight to"
				 << weight;
	};
	void onDegPerZoomChanged(int val)
	{
		m_needsToSave = true;
		emit changedDegPerZoom(val);
		if (DEBUG_SETTINGS)
			qDebug() << "Changed scroll degrees per zoom to" << val;
	};
	void onZoomArcSpanChanged(int val)
	{
		m_needsToSave = true;
		emit changedZoomArcSpan(val);
		if (DEBUG_SETTINGS)
			qDebug() << "Changed zoom indicator degrees to" << val;
	};
	void onAutoPowerChanged() { m_needsToSave = true; };
	void onPresetRowsChanged(int val)
	{
		m_needsToSave = true;
		emit changedPresetRows(val);
		if (DEBUG_SETTINGS)
			qDebug() << "Changed preset rows to" << val;
	};
	void onPresetColumnsChanged(int val)
	{
		m_needsToSave = true;
		emit changedPresetColumns(val);
		if (DEBUG_SETTINGS)
			qDebug() << "Changed preset columns to" << val;
	};

signals:
	void changedIp(QString ip);
	void changedPort(int port);
	void changedMoveAdjustment(float adjustment);
	void changedMoveAdjWeight(float weight);
	void changedZoomAdjustment(float adjustment);
	void changedZoomAdjWeight(float weight);
	void changedDegPerZoom(int degPerZoom);
	void changedZoomArcSpan(int zoomArcSpan);
	void autoPowerOn();
	void autoPowerOff();
	void changedPresetRows(int rows);
	void changedPresetColumns(int columns);

protected:
	void closeEvent(QCloseEvent *event) override;

private:
	bool m_isInitialLoad = true;
	bool m_needsToSave = false;

	QRegExp m_ipRegex;
	QRegExp m_portRegex;
	QLineEdit *m_ipField;
	QLineEdit *m_portField;

	QSlider *m_moveAdjSlider;
	QSlider *m_moveAdjWeightSlider;
	QSlider *m_zoomAdjSlider;
	QSlider *m_zoomAdjWeightSlider;
	QSlider *m_degPerZoomSlider;
	QSlider *m_zoomArcSpanSlider;

	QCheckBox *m_autoPowerOn;
	QCheckBox *m_autoPowerOff;

	QSpinBox *m_presetRowsBox;
	QSpinBox *m_presetColumnsBox;
};

#endif // SETTINGSDIALOG_H
