#include "LayoutManager.hpp"

namespace bd {
  LayoutManager::LayoutManager(QObject* parent) : QObject(parent) {
    m_model = new LayoutManagerModel(this);
  }

  void LayoutManager::connect(org::buddiesofbudgie::BudgieDaemon::Displays * displaysInterface) {
    m_displaysInterface = displaysInterface;
    QObject::connect(m_model, &LayoutManagerModel::orderChanged, this, &LayoutManager::layoutOrderChanged);
    setGlobalRect();
  }

  QRect LayoutManager::globalRect() const {
    return m_globalRect;
  }

  bd::LayoutManagerModel* LayoutManager::model() const {
    return m_model;
  }

  void LayoutManager::addOutput(QSharedPointer<Output> output) {
    m_model->addOutput(output);
  }

  int LayoutManager::selectedIndex() const {
    return m_selectedIndex;
  }

  QString LayoutManager::selectedSerial() const {
    return m_selectedSerial;
  }

  void LayoutManager::setGlobalRect() {
    auto globalRectReply = m_displaysInterface->GetGlobalRect();
    if (globalRectReply.isError()) return;

    auto rect = globalRectReply.value();

    m_globalRect = QRect(
      rect[QStringLiteral("X")].toInt(),
      rect[QStringLiteral("Y")].toInt(),
       rect[QStringLiteral("Width")].toInt(),
        rect[QStringLiteral("Height")].toInt()
    );

    Q_EMIT globalRectChanged();
  }

  void LayoutManager::setSelectedIndex(int index) {
    if (m_selectedIndex == index) {
      return;
    }
    m_selectedIndex = index;
    Q_EMIT selectedIndexChanged();
  }

  void LayoutManager::setSelectedSerial(const QString& serial) {
    if (m_selectedSerial == serial) {
      return;
    }
    m_selectedSerial = serial;
    Q_EMIT selectedSerialChanged();
  }
}


