// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QSharedPointer>
#include <QStringList>

#include "output/output.hpp"

class LayoutModel : public QAbstractListModel {
    Q_OBJECT

  public:
    explicit LayoutModel(QObject* parent = nullptr);
    ~LayoutModel() override;

    int                    rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant               data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void             addOutput(QSharedPointer<Output> output);
    Q_INVOKABLE void moveItem(int from, int to);

    QStringList currentOrder() const;

    enum Roles {
      SerialRole = Qt::UserRole + 1,
      NameRole,
      GeometryRole,
    };
    Q_ENUM(Roles)

  Q_SIGNALS:
    void orderChanged(const QStringList& order);

  private:
    QList<QSharedPointer<Output>> m_items;
};
