// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#include "layoutmodel.hpp"

LayoutModel::LayoutModel(QObject* parent) : QAbstractListModel(parent) {}

LayoutModel::~LayoutModel() = default;

int LayoutModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return m_items.size();
}

QVariant LayoutModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size()) { return QVariant(); }

  const auto output = m_items[index.row()].data();
  switch (role) {
    case SerialRole:
      return output->serial();
    case NameRole:
      return output->name();
    case GeometryRole:
      return output->geometry();
    default:
      return QVariant();
  }
}

QHash<int, QByteArray> LayoutModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[SerialRole]   = "serial";
  roles[NameRole]     = "name";
  roles[GeometryRole] = "geometry";
  return roles;
}

void LayoutModel::addOutput(QSharedPointer<Output> output) {
  beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
  m_items.append(output);
  endInsertRows();
  Q_EMIT orderChanged(currentOrder());
}

void LayoutModel::moveItem(int from, int to) {
  if (from == to) { return; }
  if (from < 0 || from >= m_items.size() || to < 0 || to >= m_items.size()) { return; }

  const int sourceRow      = from;
  const int destinationRow = to > from ? to + 1 : to;

  beginMoveRows(QModelIndex(), sourceRow, sourceRow, QModelIndex(), destinationRow);
  m_items.move(from, to);
  endMoveRows();

  Q_EMIT orderChanged(currentOrder());
}

QStringList LayoutModel::currentOrder() const {
  QStringList order;
  order.reserve(m_items.size());
  for (const auto& item : m_items) { order.append(item->serial()); }
  return order;
}
