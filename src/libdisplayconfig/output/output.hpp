// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <QDBusConnection>
#include <QObject>

#include "OutputInterface.h"

class Output : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString serial READ serial NOTIFY serialChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QRect geometry READ geometry NOTIFY geometryChanged)

  public:
    explicit Output(QObject* parent = nullptr, QString serial = QString());
    ~Output() override;

    QString serial() const;
    QString name() const;
    QRect   geometry() const;
    void    init(QSharedPointer<QDBusConnection> connection);

  Q_SIGNALS:
    void serialChanged();
    void nameChanged();
    void geometryChanged();

  public Q_SLOTS:
    void onPropertyChanged(const QString& property, const QDBusVariant& value);

  private:
    QString m_name;
    QRect   m_geometry;
    QString m_serial;

    QSharedPointer<org::buddiesofbudgie::BudgieDaemon::Output> m_output;
};
