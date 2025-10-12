#pragma once

#include <QAbstractListModel>

#include "output.hpp"

namespace bd {
    class OutputModel : public QAbstractListModel {
        Q_OBJECT

    public:
        explicit OutputModel(QObject* parent = nullptr);
        void addOutput(QSharedPointer<Output> output);
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

        enum Roles {
            SerialRole = Qt::UserRole + 1,
            NameRole,
            GeometryRole,
        };

        Q_ENUM(Roles)

    private:
        QList<QSharedPointer<Output>> m_outputs;
    };
}
