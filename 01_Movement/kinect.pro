win32:TEMPLATE = vcapp
unix:TEMPLATE = app

CONFIG += qt debug_and_release thread
QT += gui core opengl

win32 {

	# Fix Qt complaining about arch not found (related to adding a resource file?).
	contains(QMAKE_HOST.arch, x86):{
		QMAKE_LFLAGS *= /MACHINE:X86
	}

	contains(QMAKE_HOST.arch, x86_64):{
		QMAKE_LFLAGS *= /MACHINE:X64
	}


	INCLUDEPATH += "C:/Program Files (x86)/Microsoft Research KinectSDK/inc"
	LIBS += "C:/Program Files (x86)/Microsoft Research KinectSDK/lib/MSRKinectNUI.lib"
}

HEADERS += \
			dialog.h

SOURCES += \
			core.cpp dialog.cpp

FORMS += \
			kinect.ui

TARGET = 01_movement
DESTDIR = ../_bin
