
// Configure with: CMAKE_PREFIX_PATH="$(brew --prefix qt55)" cmake .
// Compile with: make

// Run with: ./vster /Library/Audio/Plug-Ins/VST/u-he/TyrellN6.vst/Contents/MacOS/TyrellN6

#include <QCoreApplication>

#include <QDebug>

#include "include/aeffectx.h"


int main(int argc, char *argv[]) {

  qDebug("app: vster");

  QCoreApplication app(argc, argv);

  QString filepath = QCoreApplication::arguments().value(1);

  if (!filepath.isEmpty()) {
    qDebug() << "filepath: " << filepath;

  }


  return app.exec();
}