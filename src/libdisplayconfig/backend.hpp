#pragma once

#include <QDBusConnection>
#include <QObject>

#include "enums/connectionstate.hpp"
#include "layout/LayoutManager.hpp"
#include "output/model.hpp"

namespace bd {

  class Backend : public QObject {
      Q_OBJECT
      Q_PROPERTY(DaemonConnectionState::State daemonConnectionState READ daemonConnectionState NOTIFY daemonConnectionStateChanged)
      Q_PROPERTY(bd::OutputModel* outputs READ outputs NOTIFY outputsChanged)
      Q_PROPERTY(bd::LayoutManager* layoutManager READ layoutManager NOTIFY layoutManagerChanged)

    public:
      explicit Backend(QObject* parent = nullptr);
      void                         connect();
      bd::OutputModel*             outputs() const;
      bd::LayoutManager*           layoutManager() const;
      DaemonConnectionState::State daemonConnectionState() const;

    Q_SIGNALS:
      void daemonConnectionStateChanged();
      void outputsChanged();
      void layoutManagerChanged();

    public Q_SLOTS:
      void setDaemonConnectionState(DaemonConnectionState::State daemonConnectionState);

    private:
      DaemonConnectionState::State    m_daemonConnectionState = DaemonConnectionState::Disconnected;
      QSharedPointer<QDBusConnection> m_connection            = QSharedPointer<QDBusConnection>(new QDBusConnection(QDBusConnection::sessionBus()));
      bd::OutputModel*                m_outputs;
      bd::LayoutManager*              m_layoutManager;
  };
}
