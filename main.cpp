
// Configure with: CMAKE_PREFIX_PATH="$(brew --prefix qt55)" cmake .
// Compile with: make

#include <QCoreApplication>

int main(int argc, char *argv[]) {

  qDebug("app: vster");

  QCoreApplication app(argc, argv);

  QString filepath = QCoreApplication::arguments().value(1);

  if (!filepath.isEmpty()) {
    qDebug() << "filepath: " << filepath;

  }


  return app.exec();
}