#include "backend.hpp"
#include <qdbusconnection.h>
#include <qdbusinterface.h>

#include <QString>

#include "DisplaysInterface.h"

namespace bd {

  Backend::Backend(QObject* parent) : QObject(parent) {
    qInfo() << "Initializing backend";
    m_connection = QDBusConnection::sessionBus();

    if (!QDBusConnection::sessionBus().isConnected()) {
      qCritical() << "Failed to connect to session bus";
      setDaemonConnectionState(DaemonConnectionState::Failed);
      return;
    }

    qInfo() << "Connected to session bus";
    
    connect();
  }

  void Backend::connect() {
    qInfo() << "Connecting to displays interface";
    auto iface = new org::buddiesofbudgie::BudgieDaemon::Displays(
        QStringLiteral("org.buddiesofbudgie.BudgieDaemon"),
        QStringLiteral("/org/buddiesofbudgie/BudgieDaemon/Displays"),
        m_connection,
        this
    );
    if (!iface->isValid()) {
      qInfo() << "Failed to get displays interface";
      setDaemonConnectionState(DaemonConnectionState::Failed);
      return;
    }

    qInfo() << "Connected to displays interface";

    setDaemonConnectionState(DaemonConnectionState::Connected);

    auto reply = iface->GetPrimaryOutput();
    if (reply.isError()) {
      qInfo() << "Failed to get primary output";
      setDaemonConnectionState(DaemonConnectionState::Failed);
      return;
    }

    qInfo() << "Primary output: " << reply.value();
  }


  DaemonConnectionState Backend::daemonConnectionState() const {
    return m_daemonConnectionState;
  }

  void Backend::setDaemonConnectionState(DaemonConnectionState daemonConnectionState) {
    m_daemonConnectionState = daemonConnectionState;
    Q_EMIT daemonConnectionStateChanged();
  }

}
