// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <QDBusConnection>
#include <QObject>

#include "enums/connectionstate.hpp"
#include "layout.hpp"
#include "models/outputmodel.hpp"

class Backend : public QObject {
    Q_OBJECT
    Q_PROPERTY(ConnectionState::State connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(OutputModel* outputs READ outputs NOTIFY outputsChanged)
    Q_PROPERTY(Layout* layout READ layout NOTIFY layoutChanged)

  public:
    explicit Backend(QObject* parent = nullptr);
    ~Backend() override;

    void                   connect();
    OutputModel*           outputs() const;
    Layout*                layout() const;
    ConnectionState::State connectionState() const;

  Q_SIGNALS:
    void connectionStateChanged();
    void outputsChanged();
    void layoutChanged();

  public Q_SLOTS:
    void setConnectionState(ConnectionState::State connectionState);

  private:
    ConnectionState::State          m_connectionState = ConnectionState::Disconnected;
    QSharedPointer<QDBusConnection> m_connection      = QSharedPointer<QDBusConnection>(new QDBusConnection(QDBusConnection::sessionBus()));
    OutputModel*                    m_outputs;
    Layout*                         m_layout;
};
