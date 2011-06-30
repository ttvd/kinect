win32:TEMPLATE = vcapp
unix:TEMPLATE = app

CONFIG += qt debug_and_release thread
QT += gui core opengl

win32 {

	RC_FILE = kinect.rc

	# Fix Qt complaining about arch not found (related to adding a resource file?).
	contains(QMAKE_HOST.arch, x86):{
		QMAKE_LFLAGS *= /MACHINE:X86
	}

	contains(QMAKE_HOST.arch, x86_64):{
		QMAKE_LFLAGS *= /MACHINE:X64
	}

	# We include GLEW's source, so static linkage.
	DEFINES += GLEW_STATIC

	INCLUDEPATH += "C:/Program Files (x86)/Microsoft Research KinectSDK/inc"
	LIBS += "C:/Program Files (x86)/Microsoft Research KinectSDK/lib/MSRKinectNUI.lib"
}

HEADERS += \
			dialog.h kinectthread.h display.h

SOURCES += \
			core.cpp dialog.cpp kinectthread.cpp display.cpp

FORMS += \
			kinect.ui

win32 {
	
	HEADERS += \
				GL/glew.h \
				GL/wglew.h
	
	SOURCES += \
				GL/glew.c
}

RESOURCES = kinect.qrc

TARGET = 03_OpenGL
DESTDIR = ../_bin
