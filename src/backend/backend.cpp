#include "backend.hpp"
#include <QDBusConnection>
#include <QDBusInterface>

#include <QString>

#include "DisplaysInterface.h"
#include "output/model.hpp"
#include "layout/LayoutManager.hpp"

namespace bd {

  Backend::Backend(QObject* parent) : QObject(parent) {
    qInfo() << "Initializing backend";
    m_connection = QSharedPointer<QDBusConnection>(new QDBusConnection(QDBusConnection::sessionBus()));

    if (!QDBusConnection::sessionBus().isConnected()) {
      qCritical() << "Failed to connect to session bus";
      setDaemonConnectionState(DaemonConnectionState::Failed);
      return;
    }

    qInfo() << "Connected to session bus";
    m_outputs = new bd::OutputModel(this);
    m_layoutManager = new bd::LayoutManager(this);
    connect();
  }

  void Backend::connect() {
    qInfo() << "Connecting to displays interface";
    auto iface = new org::buddiesofbudgie::BudgieDaemon::Displays(
        QStringLiteral("org.buddiesofbudgie.BudgieDaemon"),
        QStringLiteral("/org/buddiesofbudgie/BudgieDaemon/Displays"),
        *m_connection.data(),
        this
    );
    if (!iface->isValid()) {
      qInfo() << "Failed to get displays interface";
      setDaemonConnectionState(DaemonConnectionState::Failed);
      return;
    }

    qInfo() << "Connected to displays interface";

    m_layoutManager->connect(iface);

    setDaemonConnectionState(DaemonConnectionState::Connected);

    auto reply = iface->GetPrimaryOutput();
    if (reply.isError()) {
      qInfo() << "Failed to get primary output";
      setDaemonConnectionState(DaemonConnectionState::Failed);
      return;
    }

    qInfo() << "Primary output: " << reply.value();

    auto outputsReply = iface->GetAvailableOutputs();
    outputsReply.waitForFinished();
    if (!outputsReply.isError()) {
      const auto ids = outputsReply.value();
      for (const auto &id : ids) {
        auto output = new bd::Output(this, id);
        output->init(m_connection);
        auto sharedOutput = QSharedPointer<Output>(output);
        m_outputs->addOutput(sharedOutput);
        m_layoutManager->addOutput(sharedOutput);
      }
    } else {
      qWarning() << "GetAvailableOutputs error:" << outputsReply.error();
    }
  }


  DaemonConnectionState Backend::daemonConnectionState() const {
    return m_daemonConnectionState;
  }

  bd::OutputModel* Backend::outputs() const {
    return m_outputs;
  }

  bd::LayoutManager* Backend::layoutManager() const {
    return m_layoutManager;
  }

  void Backend::setDaemonConnectionState(DaemonConnectionState daemonConnectionState) {
    m_daemonConnectionState = daemonConnectionState;
    Q_EMIT daemonConnectionStateChanged();
  }

}
