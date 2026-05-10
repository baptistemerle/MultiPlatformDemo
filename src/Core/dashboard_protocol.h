#ifndef DASHBOARD_PROTOCOL_H
#define DASHBOARD_PROTOCOL_H

#include <QByteArray>

class DashboardProtocol
{
public:
  static QByteArray encodeLimitMessage(int limit);
};

#endif // DASHBOARD_PROTOCOL_H
