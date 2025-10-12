#pragma once

#include <QObject>

namespace bd {

  class Backend : public QObject {
      Q_OBJECT
      Q_PROPERTY(QString test READ test WRITE setTest NOTIFY testChanged)

    public:
      explicit Backend(QObject* parent = nullptr);
      QString       test() const;
      void          setTest(const QString& test);
      Q_SIGNAL void testChanged();

    private:
      QString m_test = QStringLiteral("Hello, World!");
  };
}
