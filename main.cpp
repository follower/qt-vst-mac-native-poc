
// Configure with: CMAKE_PREFIX_PATH="$(brew --prefix qt55)" cmake .
// Compile with: make

// Run with: ./vster /Library/Audio/Plug-Ins/VST/u-he/TyrellN6.vst/Contents/MacOS/TyrellN6

#include <QCoreApplication>
#include <QLibrary>

#include <QDebug>

#include "include/aeffectx.h"



static intptr_t hostCallback( AEffect * _effect, int32_t _opcode,
			      int32_t _index, intptr_t _value,
			      void * _ptr, float _opt );

intptr_t hostCallback( AEffect * _effect, int32_t _opcode,
		       int32_t _index, intptr_t _value,
		       void * _ptr, float _opt ) {

  qDebug() << "hostCallback called with opcode: " << _opcode ;

  return 0;
}


AEffect * m_plugin;


int main(int argc, char *argv[]) {

  qDebug("app: vster");

  QCoreApplication app(argc, argv);

  QString filepath = QCoreApplication::arguments().value(1);

  if (!filepath.isEmpty()) {
    qDebug() << "filepath: " << filepath;


    typedef AEffect * ( /* __stdcall */ * mainEntryPointer )( audioMasterCallback );

    mainEntryPointer mainEntry = (mainEntryPointer) QLibrary::resolve(filepath, "VSTPluginMain");

    qDebug() << "mainEntry found: " << mainEntry;


    if (mainEntry) {

      m_plugin = mainEntry( hostCallback );

      qDebug() << "mainEntry() response: " << m_plugin;

    }


  }


  return app.exec();
}