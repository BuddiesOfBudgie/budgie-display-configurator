// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <QObject>
#include <QStringList>

#include "DisplaysInterface.h"
#include "models/layoutmodel.hpp"

class Layout : public QObject {
    Q_OBJECT
    Q_PROPERTY(LayoutModel* model READ model NOTIFY modelChanged)
    Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)
    Q_PROPERTY(QString selectedSerial READ selectedSerial WRITE setSelectedSerial NOTIFY selectedSerialChanged)
    Q_PROPERTY(QRect globalRect READ globalRect NOTIFY globalRectChanged)

  public:
    explicit Layout(QObject* parent = nullptr);
    ~Layout() override;

    void connect(org::buddiesofbudgie::BudgieDaemon::Displays* displaysInterface);

    QRect        globalRect() const;
    LayoutModel* model() const;

    int     selectedIndex() const;
    QString selectedSerial() const;

    // Population helper
    void addOutput(QSharedPointer<Output> output);

  Q_SIGNALS:
    void globalRectChanged();
    void modelChanged();
    void selectedIndexChanged();
    void selectedSerialChanged();
    // Emitted when the visual order changes due to drag-reorder
    void layoutOrderChanged(const QStringList& order);

  public Q_SLOTS:
    void setSelectedIndex(int index);
    void setSelectedSerial(const QString& serial);

  private:
    void setGlobalRect();

    LayoutModel*                                  m_model;
    org::buddiesofbudgie::BudgieDaemon::Displays* m_displaysInterface;
    QRect                                         m_globalRect;
    int                                           m_selectedIndex = -1;
    QString                                       m_selectedSerial;
};
