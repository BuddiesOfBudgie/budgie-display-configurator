// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <QDBusConnection>
#include <QObject>

#include "enums/connectionstate.hpp"
#include "layout/LayoutManager.hpp"
#include "models/outputmodel.hpp"

class Backend : public QObject {
    Q_OBJECT
    Q_PROPERTY(DaemonConnectionState::State daemonConnectionState READ daemonConnectionState NOTIFY daemonConnectionStateChanged)
    Q_PROPERTY(OutputModel* outputs READ outputs NOTIFY outputsChanged)
    Q_PROPERTY(LayoutManager* layoutManager READ layoutManager NOTIFY layoutManagerChanged)

  public:
    explicit Backend(QObject* parent = nullptr);
    void                         connect();
    OutputModel*                 outputs() const;
    LayoutManager*               layoutManager() const;
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
    OutputModel*                    m_outputs;
    LayoutManager*                  m_layoutManager;
};
