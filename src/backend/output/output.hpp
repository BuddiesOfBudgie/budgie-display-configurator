#pragma once

#include <QDBusConnection>
#include <QObject>
#include "OutputInterface.h"

namespace bd {
    class Output : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString serial READ serial NOTIFY serialChanged)
        Q_PROPERTY(QString name READ name NOTIFY nameChanged)
        Q_PROPERTY(QRect geometry READ geometry NOTIFY geometryChanged)

    public:
        Output(QObject* parent = nullptr, QString serial = QString());
        Q_SLOT void onPropertyChanged(const QString& property, const QDBusVariant& value);
        Q_SIGNAL void serialChanged();
        Q_SIGNAL void nameChanged();
        Q_SIGNAL void geometryChanged();
        
        QString serial() const;
        QString name() const;
        QRect geometry() const;
        void init(QSharedPointer<QDBusConnection> connection);

    private:
        QString m_name;
        QRect m_geometry;
        QString m_serial;

        QSharedPointer<org::buddiesofbudgie::BudgieDaemon::Output> m_output;
    };
}