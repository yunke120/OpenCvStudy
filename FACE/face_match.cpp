#include "face_match.h"
#include "ui_face_match.h"

FACE_MATCH::FACE_MATCH(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FACE_MATCH)
{
    ui->setupUi(this);

    similarity = 0.90; /* 定义两张图片得相似度 */
    ui->btnMatch->setEnabled(false);


#ifdef IMAGE_PRETREATMENT

    copyfeature = {0};
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


//    getImagesFeature("../rimg", feature_list);
    files_path = getImageFilePath("../rimg");

//    if(writeFaceFeature(&feature_list)) qDebug() << "write face feature success";
//    else qDebug() << "file open failed";
#endif



}

FACE_MATCH::~FACE_MATCH()
{
    delete ui;
}

void FACE_MATCH::on_btnLoad_clicked()
{
    ui->btnMatch->setEnabled(true);
    origin_img_filepath = QFileDialog::getOpenFileName(this, "select origin image", "../", "IMAGE(*.png  *.jpg)");
    qDebug() << origin_img_filepath;
    if(origin_img_filepath.isEmpty()) return;
    QImage image;
    image.load(origin_img_filepath);
    ui->label_Origin->setPixmap(QPixmap::fromImage(image.scaled(ui->label_Origin->width(),
                                                                ui->label_Origin->height(),
                                                                Qt::KeepAspectRatio)));



#ifdef IMAGE_PRETREATMENT
    MRESULT res = MOK;
    /* 先对源图像进行处理 */
    IplImage* img1 = cvLoadImage(origin_img_filepath.toLatin1().data());

    if(img1) {
        ASF_MultiFaceInfo detectedFaces1 = { 0 }; /* 多人脸信息 */
        ASF_SingleFaceInfo SingleDetectedFaces1 = { 0 }; /* 单人脸信息 */
        ASF_FaceFeature feature1 = { 0 }; /* 人脸特征 */

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
                copyfeature.featureSize = feature1.featureSize;
                copyfeature.feature = (MByte*)malloc(feature1.featureSize);
                memset(copyfeature.feature, 0, feature1.featureSize);
                memcpy(copyfeature.feature, feature1.feature, feature1.featureSize);
            }
            else {
                qDebug() << "feature1 extract failed";
            }
        }
        else {
            qDebug() << "detect faces_1 failed";
        }

    }
#endif
}

void FACE_MATCH::on_btnMatch_clicked()
{

#undef IMAGE_DIRECTLY
#ifdef IMAGE_DIRECTLY
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



    ASF_FaceFeature feature1 = { 0 }; /* 人脸特征 */
    ASF_FaceFeature copyfeature1 = { 0 };
    /* 先对源图像进行处理 */
    IplImage* img1 = cvLoadImage(origin_img_filepath.toLatin1().data());

    if(img1) {
        ASF_MultiFaceInfo detectedFaces1 = { 0 }; /* 多人脸信息 */
        ASF_SingleFaceInfo SingleDetectedFaces1 = { 0 }; /* 单人脸信息 */



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
            }
            else {
                qDebug() << "feature1 extract failed";
            }
        }
        else {
            qDebug() << "detect faces_1 failed";
        }

    }

    QStringList files_path = getImageFilePath();

    /* 遍历要查找的图片，一一比对其相似度 */
    for (int i = 0; i < files_path.size(); i++) {
        IplImage *img2 = cvLoadImage(files_path.at(i).toLatin1().data());

        //第二张人脸提取特征
        ASF_MultiFaceInfo	detectedFaces2 = { 0 };
        ASF_SingleFaceInfo SingleDetectedFaces2 = { 0 };
        ASF_FaceFeature feature2 = { 0 };
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
            if (MOK != res)
                qDebug() << QString("ASFFaceFeatureExtract %1 fail: %2").arg(i).arg(res);
        }
        else
            qDebug() << QString("ASFDetectFaces %1 fail: %2").arg(i).arg(res);


        /* 单人脸特征对比 */
        MFloat confidenceLevel;
        res = ASFFaceFeatureCompare(handle, &copyfeature1, &feature2, &confidenceLevel);
        if(res != MOK)
            qDebug() << QString("ASFFaceFeatureCompare fail: %1").arg(res);
        else {
            qDebug() << QString("the similarity between [%1] and [%2] is %3").arg(files_path.at(i))
                                                                             .arg(origin_img_filepath)
                                                                             .arg(confidenceLevel,3);
            if(confidenceLevel >= similarity)
            {
                QImage image;
                image.load(files_path.at(i));
                ui->labelMatch->setPixmap(QPixmap::fromImage(image.scaled(ui->labelMatch->width(),
                                                                          ui->labelMatch->height(),
                                                                          Qt::KeepAspectRatio)));

                break;
            }

        }

    }

#endif


#ifdef IMAGE_PRETREATMENT

    /* 单人脸特征对比 */
    MFloat confidenceLevel;
    QList<ASF_FaceFeature> lt;
    if(readFaceFeature("", lt)) {
        qDebug() << "read success";
        qDebug() << lt.size();
        for (int i = 0; i < lt.size(); i++) {

            if(MOK == ASFFaceFeatureCompare(handle, &copyfeature, &lt[i], &confidenceLevel)) {
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
    else {
        qDebug() << "read failed";
    }






#endif





}





void FACE_MATCH::CutIplImage(IplImage *src, IplImage *dst, int x, int y)
{
    CvSize size = cvSize(dst->width, dst->height);//区域大小
    cvSetImageROI(src, cvRect(x, y, size.width, size.height));//设置源图像ROI
    cvCopy(src, dst); //复制图像
    cvResetImageROI(src);//源图像用完后，清空ROI
}

void FACE_MATCH::timestampToTime(char *timeStamp, char *dateTime, int dateTimeSize)
{
    if(timeStamp == 0) return;
    time_t tTimeStamp = atoll(timeStamp); /* 把字符串转换成长长整型数（64位） */

    struct tm* pTm = gmtime(&tTimeStamp);

    strftime(dateTime, dateTimeSize, "%Y-%m-%d %H:%M:%S", pTm);

}

QStringList FACE_MATCH::getImageFilePath(QString filepath)
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

void FACE_MATCH::getImagesFeature(QString dirpath, QList<ASF_FaceFeature> &list)
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

bool FACE_MATCH::writeFaceFeature(QList<ASF_FaceFeature> *list)
{
    QFile file("C:\\Users\\siemens\\Desktop\\Face\\exe\\initfile\\facefeature.ff");
//    QFile file("./initfile/facefeature.ff");
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file);
        for (auto item = list->begin(); item != list->end(); ++item) {
            stream.writeRawData(reinterpret_cast<char*>(&item->featureSize) , sizeof (item->featureSize));
            stream.writeRawData(reinterpret_cast<char*>(item->feature) , item->featureSize);
        }
        file.close();
        return true;
    }
    else return false;

}

bool FACE_MATCH::readFaceFeature(QString filepath, QList<ASF_FaceFeature> &list)
{
    QFile file("C:\\Users\\siemens\\Desktop\\Face\\exe\\initfile\\facefeature.ff");
    if(file.open(QIODevice::ReadOnly)) {
        QDataStream stream(&file);
        ASF_FaceFeature l;
        while (!file.atEnd()) {
            stream.readRawData(reinterpret_cast<char*>(&l.featureSize), sizeof (l.featureSize));
            l.feature = reinterpret_cast<MByte*>(malloc(l.featureSize));
            stream.readRawData(reinterpret_cast<char*>(l.feature), l.featureSize);
            list << l;
            l.featureSize = 0;
            free(l.feature);

        }
        return true;
    }
    else return false;
}










