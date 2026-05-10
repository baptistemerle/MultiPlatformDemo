#ifndef ALERT_CONTROLLER_H
#define ALERT_CONTROLLER_H

#include <QObject>
#include <QString>

class AlertController : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)

public:
  explicit AlertController(QObject* parent = nullptr);

  QString errorMessage() const;

  Q_INVOKABLE void clearError();

public slots:
  void showError(const QString& msg);

signals:
  void errorMessageChanged();

private:
  QString m_errorMessage;
};

#endif // ALERT_CONTROLLER_H
