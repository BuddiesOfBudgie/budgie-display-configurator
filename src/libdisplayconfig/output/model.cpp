#include "model.hpp"

namespace bd {
    OutputModel::OutputModel(QObject* parent) : QAbstractListModel(parent) {}

    void OutputModel::addOutput(QSharedPointer<Output> output) {
        beginInsertRows(QModelIndex(), m_outputs.size(), m_outputs.size());
        m_outputs.append(output);
        endInsertRows();
    }

    int OutputModel::rowCount(const QModelIndex& parent) const {
        Q_UNUSED(parent);
        return m_outputs.size();
    }

    QVariant OutputModel::data(const QModelIndex& index, int role) const {
        Q_UNUSED(role);
        auto output = m_outputs[index.row()].data();
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

    QHash<int, QByteArray> OutputModel::roleNames() const {
        QHash<int, QByteArray> roles;
        roles[SerialRole] = "serial";
        roles[NameRole] = "name";
        roles[GeometryRole] = "geometry";
        return roles;
    }
}