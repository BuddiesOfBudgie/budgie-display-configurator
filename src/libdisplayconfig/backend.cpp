// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#include "backend.hpp"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QString>

#include "OutputsInterface.h"

Backend::Backend(QObject* parent) : QObject(parent) {
  qInfo() << "Initializing backend";
  m_connection = QSharedPointer<QDBusConnection>(new QDBusConnection(QDBusConnection::sessionBus()));

  if (!QDBusConnection::sessionBus().isConnected()) {
    qCritical() << "Failed to connect to session bus";
    setConnectionState(ConnectionState::Failed);
    return;
  }

  qInfo() << "Connected to session bus";
  m_outputs = new OutputModel(this);
  m_layout  = new Layout(this);
  connect();
}

Backend::~Backend() = default;

void Backend::connect() {
  qInfo() << "Connecting to displays interface";
  auto iface = new org::buddiesofbudgie::Services::Outputs(
      QStringLiteral("org.buddiesofbudgie.Services.Outputs"), QStringLiteral("/org/buddiesofbudgie/Services/Outputs"), *m_connection.data(), this);

  if (!iface->isValid()) {
    qInfo() << "Failed to get displays interface";
    setConnectionState(ConnectionState::Failed);
    return;
  }

  qInfo() << "Connected to displays interface";

  m_layout->connect(iface);

  setConnectionState(ConnectionState::Connected);

  auto reply = iface->GetPrimaryOutput();
  if (reply.isError()) {
    qInfo() << "Failed to get primary output";
    setConnectionState(ConnectionState::Failed);
    return;
  }

  qInfo() << "Primary output: " << reply.value();

  auto outputsReply = iface->GetAvailableOutputs();
  outputsReply.waitForFinished();
  if (!outputsReply.isError()) {
    const auto ids = outputsReply.value();
    for (const auto& id : ids) {
      auto output = new Output(this, id);
      output->init(m_connection);
      auto sharedOutput = QSharedPointer<Output>(output);
      m_outputs->addOutput(sharedOutput);
      m_layout->addOutput(sharedOutput);
    }
  } else {
    qWarning() << "GetAvailableOutputs error:" << outputsReply.error();
  }
}

ConnectionState::State Backend::connectionState() const {
  return m_connectionState;
}

OutputModel* Backend::outputs() const {
  return m_outputs;
}

Layout* Backend::layout() const {
  return m_layout;
}

void Backend::setConnectionState(ConnectionState::State daemonConnectionState) {
  m_connectionState = daemonConnectionState;
  Q_EMIT connectionStateChanged();
}
