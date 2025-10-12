#include "backend.hpp"

namespace bd {

  Backend::Backend(QObject* parent) : QObject(parent) {}

  QString Backend::test() const {
    return m_test;
  }

  void Backend::setTest(const QString& test) {
    m_test = test;
    Q_EMIT testChanged();
  }

}
