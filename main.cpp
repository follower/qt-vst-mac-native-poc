
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


  switch( _opcode )
  {
    case audioMasterVersion:
      return 2300;

    default:
      qDebug() << "unhandled opcode: " << _opcode;
      break;
  }

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

      if (m_plugin) {

	qDebug() << "magic: " << m_plugin->magic;

	qDebug() << "correct magic: " << (m_plugin->magic == kEffectMagic);

	if (m_plugin->magic == kEffectMagic) {

	  qDebug() << "";
	  qDebug() << "numPrograms" << m_plugin->numPrograms;
	  qDebug() << "numParams" << m_plugin->numParams;
	  qDebug() << "numInputs" << m_plugin->numInputs;
	  qDebug() << "numOutputs" << m_plugin->numOutputs;
	  qDebug() << "";

	  // From LMMS:
	  for( int i = 0; i < m_plugin->numParams; ++i )
	    {
	      char paramName[32];
	      memset( paramName, 0, sizeof( paramName ) );
	      m_plugin->dispatcher( m_plugin, effGetParamName, i, 0, paramName, 0 );
	      paramName[sizeof(paramName)-1] = 0;
	      qDebug() << i << paramName << m_plugin->getParameter( m_plugin, i );
	    }
	}
      }

    }


  }


  return app.exec();
}