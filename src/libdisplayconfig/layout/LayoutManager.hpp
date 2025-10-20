#pragma once

#include <QObject>
#include <QStringList>

#include "DisplaysInterface.h"
#include "LayoutManagerModel.hpp"

namespace bd {
  class LayoutManager : public QObject {
      Q_OBJECT
      Q_PROPERTY(bd::LayoutManagerModel* model READ model NOTIFY modelChanged)
      Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)
      Q_PROPERTY(QString selectedSerial READ selectedSerial WRITE setSelectedSerial NOTIFY selectedSerialChanged)
      Q_PROPERTY(QRect globalRect READ globalRect NOTIFY globalRectChanged)

    public:
      LayoutManager(QObject* parent = nullptr);

      void connect(org::buddiesofbudgie::BudgieDaemon::Displays * displaysInterface);

      QRect globalRect() const;
      bd::LayoutManagerModel* model() const;

      int selectedIndex() const;
      QString selectedSerial() const;

      Q_SLOT void setSelectedIndex(int index);
      Q_SLOT void setSelectedSerial(const QString& serial);

      // Population helper
      void addOutput(QSharedPointer<Output> output);

    Q_SIGNALS:
      void globalRectChanged();
      void modelChanged();
      void selectedIndexChanged();
      void selectedSerialChanged();
      // Emitted when the visual order changes due to drag-reorder
      void layoutOrderChanged(const QStringList& order);

    private:
      void setGlobalRect();

      LayoutManagerModel* m_model;
      org::buddiesofbudgie::BudgieDaemon::Displays * m_displaysInterface;
      QRect m_globalRect;
      int m_selectedIndex = -1;
      QString m_selectedSerial;
  };
}


