#include "dashboard_protocol.h"

#include <Protocols/length_payload_formatter.hpp>

#include <QString>

QByteArray DashboardProtocol::encodeLimitMessage(int limit)
{
  QString json = QString("{\"limit\":%1}").arg(limit);

  std::string rawPayload = json.toUtf8().toStdString();

  std::string data = LengthPayloadFormatter<4>::format(rawPayload);

  return QByteArray::fromStdString(data);
}