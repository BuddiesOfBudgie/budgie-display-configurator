// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#include "output.hpp"

Output::Output(QObject* parent, QString serial) : QObject(parent), m_serial(serial) {}

Output::~Output() = default;

void Output::onPropertyChanged(const QString& property, const QDBusVariant& value) {
  if (property == QStringLiteral("name")) {
    m_name = value.variant().toString();
    Q_EMIT nameChanged();
  } else if (property == QStringLiteral("geometry")) {
    m_geometry = value.variant().toRect();
    Q_EMIT geometryChanged();
  }
}

void Output::init(QSharedPointer<QDBusConnection> connection) {
  const auto path   = QStringLiteral("/org/buddiesofbudgie/Services/Outputs/%1").arg(m_serial);
  auto       output = new org::buddiesofbudgie::Services::Output(QStringLiteral("org.buddiesofbudgie.Services"), path, *connection.data(), this);

  if (!output->isValid()) {
    qWarning() << "Output interface invalid for" << m_serial << "at" << path;
    m_output.clear();
    return;
  }

  qInfo() << "Output interface valid for" << m_serial << "at" << path;

  m_output = QSharedPointer<org::buddiesofbudgie::Services::Output>(output);

  connect(m_output.data(), &org::buddiesofbudgie::Services::Output::PropertyChanged, this, &Output::onPropertyChanged);
}

QRect Output::geometry() const {
  if (!m_output->isValid()) { return QRect(); }
  return QRect(m_output->x(), m_output->y(), m_output->width(), m_output->height());
}

QString Output::name() const {
  return m_output->isValid() ? m_output->name() : QString();
}

QString Output::serial() const {
  return m_output->isValid() ? m_output->serial() : QString();
}
