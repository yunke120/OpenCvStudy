QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += _CRT_SECURE_NO_WARNINGS

DESTDIR = $$PWD/../exe
TARGET = FACE

SOURCES += \
    arc_face.cpp \
    face_bin.cpp \
    face_match.cpp \
    face_sql.cpp \
    main.cpp \
    mainwindow.cpp \
    opencv_video.cpp \
    register_face.cpp \
    test_ui.cpp \
    video2label.cpp \
    video_match.cpp

HEADERS += \
    arc_face.h \
    face_bin.h \
    face_match.h \
    face_sql.h \
    mainwindow.h \
    opencv_video.h \
    register_face.h \
    submain.h \
    test_ui.h \
    video2label.h \
    video_match.h

FORMS += \
    arc_face.ui \
    face_match.ui \
    mainwindow.ui \
    opencv_video.ui \
    register_face.ui \
    test_ui.ui \
    video2label.ui \
    video_match.ui

INCLUDEPATH += $$PWD/opencv/inc/
INCLUDEPATH += $$PWD/opencv/inc/opencv
INCLUDEPATH += $$PWD/opencv/inc/opencv2

INCLUDEPATH += $$PWD/arcface/inc
#LIBS += -L$$PWD/opencv/lib -lopencv_*
LIBS += -L$$PWD/opencv/lib -lopencv_core249     \
#                           -lopencv_core249d    \
                           -lopencv_highgui249  \
#                           -lopencv_highgui249d \
                           -lopencv_imgproc249  \
#                           -lopencv_imgproc249d \
                           -lopencv_objdetect249 \
                           -lopencv_video249



LIBS += -L$$PWD/arcface/lib -llibarcsoft_face_engine

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target







