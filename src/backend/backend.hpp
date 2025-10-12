#pragma once

#include <QObject>
#include <QDBusConnection>
#include "enums.hpp"
#include "output/model.hpp"

namespace bd {

  class Backend : public QObject {
      Q_OBJECT
      Q_PROPERTY(DaemonConnectionState daemonConnectionState READ daemonConnectionState NOTIFY daemonConnectionStateChanged)
      Q_PROPERTY(bd::OutputModel* outputs READ outputs NOTIFY outputsChanged)

    public:
      explicit Backend(QObject* parent = nullptr);
      void connect();
      bd::OutputModel* outputs() const;
      DaemonConnectionState daemonConnectionState() const;
      Q_SIGNAL void daemonConnectionStateChanged();
      Q_SLOT void setDaemonConnectionState(DaemonConnectionState daemonConnectionState);
      Q_SIGNAL void outputsChanged();

    private:
      DaemonConnectionState m_daemonConnectionState = DaemonConnectionState::Disconnected;
      QSharedPointer<QDBusConnection> m_connection = QSharedPointer<QDBusConnection>(new QDBusConnection(QDBusConnection::sessionBus()));
      bd::OutputModel* m_outputs;
  };
}
