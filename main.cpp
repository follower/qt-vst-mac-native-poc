
// Configure with: CMAKE_PREFIX_PATH="$(brew --prefix qt55)" cmake .
// Compile with: make

#include <QCoreApplication>

int main(int argc, char *argv[]) {

  qDebug("app: vster");

  QCoreApplication app(argc, argv);

  return app.exec();
}