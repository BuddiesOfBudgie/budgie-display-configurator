// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

#include "layout.hpp"

Layout::Layout(QObject* parent) : QObject(parent) {
  m_model = new LayoutModel(this);
}

Layout::~Layout() = default;

void Layout::connect(org::buddiesofbudgie::Services::Outputs* outputsInterface) {
  m_outputsInterface = outputsInterface;
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
  auto rect = m_outputsInterface->globalRect();

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
