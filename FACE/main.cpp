#include "mainwindow.h"
#include "opencv_video.h"
#include "video2label.h"
#include "arc_face.h"
#include "face_match.h"
#include "video_match.h"
#include "register_face.h"
#include "test_ui.h"
#include <QApplication>

#include "submain.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef TEST_UI_TEST_T
    TEST_UI w1;
    w1.show();
#endif

#ifdef IMAGE_TEST_T
    MainWindow w;
//    w.show();
#endif


#ifdef VIDEO_TEST_T
    OPENCV_VIDEO w2;
//    w2.show();
#endif

#ifdef VIDEO_2_LABEL_TEST_T
    VIDEO2LABEL w3;
    w3.show();
#endif

#ifdef ARCFACE_TEST_T
    ARC_FACE w4;
//    w4.show();
#endif

#ifdef FACE_MATCH_TEST_T
    FACE_MATCH w5;
    w5.show();
#endif


#ifdef VIDEO_MATCH_TEST_T
    VIDEO_MATCH w6;
    w6.show();
#endif


#ifdef REGISTER_FACE_TEST_T
    REGISTER_FACE w7;
    w7.show();
#endif


    return a.exec();
}
