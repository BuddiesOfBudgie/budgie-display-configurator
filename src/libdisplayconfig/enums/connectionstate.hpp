// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <QObject>
#include <QQmlEngine>

/**
 * @class DaemonConnectionState
 *
 * This class defines the DaemonConnectionState enumeration.
 */
class DaemonConnectionState : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

  public:
    /**
     * @brief The connection states of the Daemon.
     */
    enum State {
      Failed = 0,   /**< Failed state. */
      Disconnected, /**< Disconnected from the daemon. */
      Connecting,   /**< Connecting to the daemon. */
      Connected,    /**< Connected to the daemon. */
      Disconnecting /**< Disconnecting from the daemon. */
    };
    Q_ENUM(State);
};
