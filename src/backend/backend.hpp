#pragma once

#include <QObject>
#include <QDBusConnection>
#include "enums.hpp"

namespace bd {

  class Backend : public QObject {
      Q_OBJECT
      Q_PROPERTY(DaemonConnectionState daemonConnectionState READ daemonConnectionState NOTIFY daemonConnectionStateChanged)

    public:
      explicit Backend(QObject* parent = nullptr);
      void connect();
      DaemonConnectionState daemonConnectionState() const;
      Q_SIGNAL void daemonConnectionStateChanged();
      Q_SLOT void setDaemonConnectionState(DaemonConnectionState daemonConnectionState);

    private:
      DaemonConnectionState m_daemonConnectionState = DaemonConnectionState::Disconnected;
      QDBusConnection m_connection = QDBusConnection::sessionBus();
  };
}
