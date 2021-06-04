#include "video_match.h"
#include "ui_video_match.h"

VIDEO_MATCH::VIDEO_MATCH(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VIDEO_MATCH)
{
    ui->setupUi(this);

    video_timer = new QTimer(this);


    similarity = 0.95;

    connect(video_timer, &QTimer::timeout, this, &VIDEO_MATCH::displayVideo);

    cascadeClassifier = new CvHaarClassifierCascade;
    cascadeClassifier = (CvHaarClassifierCascade*)cvLoad("B:\\QT_Project\\Face\\exe\\haarcascade_frontalface_alt2.xml");



    feature1 = {0};
    feature_list.clear();
    MRESULT res = MOK;
    QString APP_KEY = "kf4Er8xXdzWCD97fS44ghb6Lg9MMDtzPbqftjacyuM2";
    QString SDK_KEY = "BHwSM2pzFzcHUE8ZT9EfuSJENVLcHgHXGq3q6bEEmnkb";
    res = ASFOnlineActivation(APP_KEY.toLatin1().data(), SDK_KEY.toLatin1().data());
    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
        qDebug() << "ASFActivation fail";
    else
        qDebug() << "ASFActivation sucess";

    //初始化接口

    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION ; /* 只用人脸检测和人脸特征 */
    res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_ONLY, 30, 5, mask, &handle);
    if (res != MOK)
        qDebug() << "ASFInitEngine fail";
    else
        qDebug() << "ASFInitEngine success";

/* https://github.com/YunKe-191022/Opencv_Study.git  */
    getImagesFeature("../rimg", feature_list);

}

VIDEO_MATCH::~VIDEO_MATCH()
{
    delete ui;
}

void VIDEO_MATCH::CutIplImage(IplImage *src, IplImage *dst, int x, int y)
{
    CvSize size = cvSize(dst->width, dst->height);//区域大小
    cvSetImageROI(src, cvRect(x, y, size.width, size.height));//设置源图像ROI
    cvCopy(src, dst); //复制图像
    cvResetImageROI(src);//源图像用完后，清空ROI
}

QStringList VIDEO_MATCH::getImageFilePath(QString dirpath)
{
    QDir dir("../rimg");
    QStringList files_path;
    files_path.clear();
    if(!dir.exists()) return files_path;

    QStringList nameFilters;
    nameFilters << "*.png" << "*.jpg";
    QStringList files_name = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);

    for (int i = 0; i < files_name.size(); i++) {
//        qDebug() << files_name.at(i);
        files_path << "../rimg/" + files_name.at(i);
    }

    return files_path;
}

void VIDEO_MATCH::getImagesFeature(QString dirpath, QList<ASF_FaceFeature> &list)
{
    MRESULT res = MOK;
    files_path = getImageFilePath(dirpath);

    /* 遍历要查找的图片，一一比对其相似度 */
    for (int i = 0; i < files_path.size(); i++) {
//        qDebug() << files_path.at(i);
        IplImage *img2 = cvLoadImage(files_path.at(i).toLatin1().data());

        //第二张人脸提取特征
        ASF_MultiFaceInfo	detectedFaces2 = { 0 };
        ASF_SingleFaceInfo SingleDetectedFaces2 = { 0 };
        ASF_FaceFeature feature2 = { 0 };
        ASF_FaceFeature copyfeature2 = { 0 };
        IplImage* cutImg2 = cvCreateImage(cvSize(img2->width - img2->width % 4, img2->height), IPL_DEPTH_8U, img2->nChannels);
        CutIplImage(img2, cutImg2, 0, 0);

        ASVLOFFSCREEN offscreen2 = { 0 };
        offscreen2.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
        offscreen2.i32Width = cutImg2->width;
        offscreen2.i32Height = cutImg2->height;
        offscreen2.pi32Pitch[0] = cutImg2->widthStep;
        offscreen2.ppu8Plane[0] = (MUInt8*)cutImg2->imageData;

        res = ASFDetectFacesEx(handle, &offscreen2, &detectedFaces2);
        if (MOK == res && detectedFaces2.faceNum >= 1)
        {
            SingleDetectedFaces2.faceRect.left = detectedFaces2.faceRect[0].left;
            SingleDetectedFaces2.faceRect.top = detectedFaces2.faceRect[0].top;
            SingleDetectedFaces2.faceRect.right = detectedFaces2.faceRect[0].right;
            SingleDetectedFaces2.faceRect.bottom = detectedFaces2.faceRect[0].bottom;
            SingleDetectedFaces2.faceOrient = detectedFaces2.faceOrient[0];

            res = ASFFaceFeatureExtractEx(handle, &offscreen2, &SingleDetectedFaces2, &feature2);
            copyfeature2 = {0};
            if (res == MOK)
            {
                //拷贝feature
                copyfeature2.featureSize = feature2.featureSize;
                copyfeature2.feature = (MByte *)malloc(feature2.featureSize);
                memset(copyfeature2.feature, 0, feature2.featureSize);
                memcpy(copyfeature2.feature, feature2.feature, feature2.featureSize);
                list << copyfeature2;
            }
            else {
                qDebug() << QString("extract image_%1 feature failed").arg(i);
            }
        }
        else {
            qDebug() << QString("ASFDetectFaces %1 fail: %2").arg(i).arg(res);

        }

    }
    qDebug() << "Traverse complete";
}

void VIDEO_MATCH::getMatchImageFeature(cv::Mat img, ASF_FaceFeature& copyfeature1)
{
    MRESULT res = MOK;
    IplImage imgTmp = img;
    IplImage *img1 = cvCloneImage(&imgTmp); /* 深拷贝 */
//    IplImage *img1 = cvCreateImage(cvSize(img.cols, img.rows), 8, 3);

    if(img1) {
        ASF_MultiFaceInfo detectedFaces1 = { 0 }; /* 多人脸信息 */
        ASF_SingleFaceInfo SingleDetectedFaces1 = { 0 }; /* 单人脸信息 */
        ASF_FaceFeature feature1 = { 0 }; /* 人脸特征 */
        copyfeature1 = {0};
//        ASF_FaceFeature copyfeature1 = {0};

        /* 4字节对齐 */
        IplImage* cutImg1 = cvCreateImage(cvSize(img1->width - img1->width % 4, img1->height), IPL_DEPTH_8U, img1->nChannels);
        CutIplImage(img1, cutImg1, 0, 0);
        ASVLOFFSCREEN offscreen1 = {0};
        offscreen1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
        offscreen1.i32Width = cutImg1->width;
        offscreen1.i32Height = cutImg1->height;
        offscreen1.pi32Pitch[0] = cutImg1->widthStep;
        offscreen1.ppu8Plane[0] = (MUInt8*)cutImg1->imageData;

        res = ASFDetectFacesEx(handle, &offscreen1, &detectedFaces1);
        if(res == MOK && detectedFaces1.faceNum >=1) {
            SingleDetectedFaces1.faceRect.left = detectedFaces1.faceRect[0].left;
            SingleDetectedFaces1.faceRect.top = detectedFaces1.faceRect[0].top;
            SingleDetectedFaces1.faceRect.right = detectedFaces1.faceRect[0].right;
            SingleDetectedFaces1.faceRect.bottom = detectedFaces1.faceRect[0].bottom;
            SingleDetectedFaces1.faceOrient = detectedFaces1.faceOrient[0];

            res = ASFFaceFeatureExtractEx(handle, &offscreen1, &SingleDetectedFaces1, &feature1);
            if(res == MOK) { /* 第一次提取特征需进行拷贝，因为使用同一个引擎，第二次拷贝会覆盖第一次提取的结果 */
                //拷贝feature
                copyfeature1.featureSize = feature1.featureSize;
                copyfeature1.feature = (MByte*)malloc(feature1.featureSize);
                memset(copyfeature1.feature, 0, feature1.featureSize);
                memcpy(copyfeature1.feature, feature1.feature, feature1.featureSize);

                qDebug() << "get feature 1 success";

            }
            else {
                qDebug() << "feature1 extract failed";
            }
        }
        else {
            qDebug() << "detect faces_1 failed";
        }
    }
}

void VIDEO_MATCH::displayVideo()
{
    if(!camera.isOpened()) {
        qDebug() << "camera opened failed.";
        return ;
    }
    if(!camera.read(image)) {
        qDebug() << "The read image is empty";
        return ;
    }

    cv::cvtColor(image, grayimage, CV_BGR2GRAY);
    cv::cvtColor(image, ret_image, CV_BGR2RGB);
    IplImage img(grayimage);
    IplImage dspimg(ret_image);
    if(cascadeClassifier != NULL) {
        CvScalar FaceCirclecolors[] = {
            {{0,0,255}},
            {{0,128,255}},
            {{0,255,255}},
            {{0,255,0}},
            {{255,128,0}},
            {{255,255,0}},
            {{255,0,0}},
            {{255,0,255}},
        };


        CvMemStorage *memStorage = cvCreateMemStorage(0); /* 创建一个内存存储块，0默认大小64KB */
        cvClearMemStorage(memStorage); /* 将释放的内存返还给内存存储器，不返还给系统 */

//        DWORD start_time, end_time;
//        start_time = GetTickCount();
        CvSeq *seqFace = cvHaarDetectObjects(&img, cascadeClassifier, memStorage);
//        end_time = GetTickCount();

//        qDebug() << QString("face number: %1 , identify all time: %2").arg(seqFace->total).arg(end_time - start_time);

        for (int i = 0; i < seqFace->total; i++) {

            CvRect* r = (CvRect*)cvGetSeqElem(seqFace, i); /* 利用强制类型转换，转换为序列中实际存储的数据类型 */
            CvPoint center;
            int radius;
            center.x = cvRound((r->x + r->width * 0.5));
            center.y = cvRound((r->y + r->height * 0.5));
            radius = cvRound((r->width + r->height) * 0.25);

            cvCircle(&dspimg, center, radius, FaceCirclecolors[i % 8],1);

        }
    }



    if(SAVE_IMAGE_FLAGE)
    { /* 点击匹配，获取当前祯图像feature */
        SAVE_IMAGE_FLAGE = false;
//        qDebug() << QString("face number: %1 , identify all time: %2").arg(seqFace->total).arg(end_time - start_time);
        getMatchImageFeature(image, feature1);

        /* 单人脸特征对比 */
        MFloat confidenceLevel;

        for (int i = 0; i < feature_list.size(); i++) {

            if(MOK == ASFFaceFeatureCompare(handle, &feature1, &feature_list[i], &confidenceLevel)) {
                qDebug() << confidenceLevel;
                if(confidenceLevel >= similarity) {
                    QImage image;
                    image.load(files_path.at(i));
                    ui->labelMatch->setPixmap(QPixmap::fromImage(image.scaled(ui->labelMatch->width(),
                                                                              ui->labelMatch->height(),
                                                                              Qt::KeepAspectRatio)));

                    break;
                }
            }

        }


    }

    QImage q_image((const uchar*)ret_image.data,ret_image.cols,ret_image.rows, QImage::Format_RGB888); /* 截图彩色 */
//    QImage q_image((const uchar*)grayimage.data,grayimage.cols,grayimage.rows, QImage::Format_Grayscale8); /* 灰度显示 */
    ui->labelDisplay->setPixmap(QPixmap::fromImage(q_image));
}

void VIDEO_MATCH::on_btnPlay_clicked()
{
    camera.open(0);
    camera.set(CV_CAP_PROP_FRAME_WIDTH,ui->labelDisplay->width());
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,ui->labelDisplay->height());
    if(!camera.isOpened()) {
        qDebug() << "camera0 open failed.";
        return;
    }

    video_timer->start(150);
}

void VIDEO_MATCH::on_btnMatch_clicked()
{
    SAVE_IMAGE_FLAGE = true;
}

void VIDEO_MATCH::on_btnStop_clicked()
{
    video_timer->stop();
    ASFUninitEngine(handle);
    camera.release();
    image.release();

}
