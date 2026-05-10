#include "alert_controller.h"

AlertController::AlertController(QObject *parent) : QObject(parent)
{
}

QString AlertController::errorMessage() const
{
  return m_errorMessage;
}

void AlertController::clearError()
{
  if (!m_errorMessage.isEmpty())
  {
    m_errorMessage.clear();
    emit errorMessageChanged();
  }
}

void AlertController::showError(const QString& msg)
{
  m_errorMessage = msg;
  emit errorMessageChanged();
}
