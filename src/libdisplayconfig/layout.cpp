// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#include "layout.hpp"

Layout::Layout(QObject* parent) : QObject(parent) {
  m_model = new LayoutModel(this);
}

Layout::~Layout() = default;

void Layout::connect(org::buddiesofbudgie::BudgieDaemon::Displays* displaysInterface) {
  m_displaysInterface = displaysInterface;
  QObject::connect(m_model, &LayoutModel::orderChanged, this, &Layout::layoutOrderChanged);
  setGlobalRect();
}

QRect Layout::globalRect() const {
  return m_globalRect;
}

LayoutModel* Layout::model() const {
  return m_model;
}

void Layout::addOutput(QSharedPointer<Output> output) {
  m_model->addOutput(output);
}

int Layout::selectedIndex() const {
  return m_selectedIndex;
}

QString Layout::selectedSerial() const {
  return m_selectedSerial;
}

void Layout::setGlobalRect() {
  auto globalRectReply = m_displaysInterface->GetGlobalRect();
  if (globalRectReply.isError()) return;

  auto rect = globalRectReply.value();

  m_globalRect = QRect(
      rect[QStringLiteral("X")].toInt(), rect[QStringLiteral("Y")].toInt(), rect[QStringLiteral("Width")].toInt(), rect[QStringLiteral("Height")].toInt());

  Q_EMIT globalRectChanged();
}

void Layout::setSelectedIndex(int index) {
  if (m_selectedIndex == index) { return; }
  m_selectedIndex = index;
  Q_EMIT selectedIndexChanged();
}

void Layout::setSelectedSerial(const QString& serial) {
  if (m_selectedSerial == serial) { return; }
  m_selectedSerial = serial;
  Q_EMIT selectedSerialChanged();
}
