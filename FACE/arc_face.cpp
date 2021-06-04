#include "arc_face.h"
#include "ui_arc_face.h"

ARC_FACE::ARC_FACE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ARC_FACE)
{
    ui->setupUi(this);


    MRESULT res = MOK;
    ASF_ActiveFileInfo activeFileInfo = {0};
    res = ASFGetActiveFileInfo(&activeFileInfo);
    if(res != MOK) {
        qDebug() << QString("ASFGetActiveFileInfo fail: %1").arg(res);
    }
    else {
        char startDateTime[32];
        timestampToTime(activeFileInfo.startTime,startDateTime,32);
        qDebug() << QString("startTime: %1").arg(startDateTime);

        char endDateTime[32];
        timestampToTime(activeFileInfo.endTime, endDateTime, 32);
        qDebug() << QString("endTime: %1").arg(endDateTime);
    }

    const ASF_VERSION version = ASFGetVersion();
    qDebug() << QString("\n Version: %1\n BuildDate: %2\n CpoyRight: %3").arg(version.Version).arg(version.BuildDate).arg(version.CopyRight);

    QString APP_KEY = "kf4Er8xXdzWCD97fS44ghb6Lg9MMDtzPbqftjacyuM2";
    QString SDK_KEY = "BHwSM2pzFzcHUE8ZT9EfuSJENVLcHgHXGq3q6bEEmnkb";
    res = ASFOnlineActivation(APP_KEY.toLatin1().data(), SDK_KEY.toLatin1().data());
    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
        qDebug() << "ASFActivation fail";
    else
        qDebug() << "ASFActivation sucess";

    //初始化接口
    MHandle handle = NULL;
    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE |
        ASF_LIVENESS | ASF_IR_LIVENESS;
    res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_ONLY, 30, 5, mask, &handle);
    if (res != MOK)
        qDebug() << "ASFInitEngine fail";
    else
        qDebug() << "ASFInitEngine success";


    // 人脸检测
    IplImage* img1 = cvLoadImage("B:\\QT_Project\\Face\\rimg\\17328.png");
    IplImage* img2 = cvLoadImage("B:\\QT_Project\\Face\\rimg\\27360.png");

    if(img1 && img2) {
        ASF_MultiFaceInfo detectedFaces1 = { 0 }; /* 多人脸信息 */
        ASF_SingleFaceInfo SingleDetectedFaces1 = { 0 }; /* 单人脸信息 */
        ASF_FaceFeature feature1 = { 0 }; /* 人脸特征 */
        ASF_FaceFeature copyfeature1 = { 0 };

        /* 4字节对齐 */
        IplImage* cutImg1 = cvCreateImage(cvSize(img1->width - img1->width % 4, img1->height), IPL_DEPTH_8U, img1->nChannels);
        CutIplImage(img1, cutImg1, 0, 0);


        ASVLOFFSCREEN offscreen1 = { 0 }; /* 图像数据信息，该结构体在 asvloffscreen. 基础的头文件中 */
        offscreen1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
        offscreen1.i32Width = cutImg1->width;
        offscreen1.i32Height = cutImg1->height;
        offscreen1.pi32Pitch[0] = cutImg1->widthStep;
        offscreen1.ppu8Plane[0] = (MUInt8*)cutImg1->imageData;

        /*
         * hEngine in 引擎句柄
         * imgData in 图像数据
         * detectedFaces out 检测到的人脸信息
        */
        res = ASFDetectFacesEx(handle, &offscreen1, &detectedFaces1); /* 检测人脸信息 */

        if (MOK == res && detectedFaces1.faceNum >= 1)
        {
            SingleDetectedFaces1.faceRect.left = detectedFaces1.faceRect[0].left;
            SingleDetectedFaces1.faceRect.top = detectedFaces1.faceRect[0].top;
            SingleDetectedFaces1.faceRect.right = detectedFaces1.faceRect[0].right;
            SingleDetectedFaces1.faceRect.bottom = detectedFaces1.faceRect[0].bottom;
            SingleDetectedFaces1.faceOrient = detectedFaces1.faceOrient[0];

            res = ASFFaceFeatureExtractEx(handle, &offscreen1, &SingleDetectedFaces1, &feature1);
            if (res == MOK)
            {
                //拷贝feature
                copyfeature1.featureSize = feature1.featureSize;
                copyfeature1.feature = (MByte *)malloc(feature1.featureSize);
                memset(copyfeature1.feature, 0, feature1.featureSize);
                memcpy(copyfeature1.feature, feature1.feature, feature1.featureSize);
            }
            else
                qDebug() << QString("ASFFaceFeatureExtract 1 fail: %1").arg(res);
        }
        else
            qDebug() << QString("ASFDetectFaces 1 fail: %1").arg(res);


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
                qDebug() << QString("ASFFaceFeatureExtract 2 fail: %1").arg(res);
        }
        else
            qDebug() << QString("ASFDetectFaces 2 fail: %1").arg(res);


        /* 单人脸特征对比 */
        MFloat confidenceLevel;
        res = ASFFaceFeatureCompare(handle, &copyfeature1, &feature2, &confidenceLevel);
        if(res != MOK)
            qDebug() << QString("ASFFaceFeatureCompare fail: %1").arg(res);
        else
            qDebug() << QString("ASFFaceFeatureCompare success: %1").arg(confidenceLevel);


        // RGB图像检测
        MInt32 processMask = ASF_AGE | ASF_GENDER;
        res = ASFProcessEx(handle, &offscreen2, &detectedFaces2, processMask);
        if(res != MOK)
            qDebug() << QString("ASFSProcessEx fail: %1").arg(res);
        else
            qDebug() << QString("ASFSProcessEx success: %1").arg(res);

        // 获取年龄
        ASF_AgeInfo ageInfo = { 0 };
        res = ASFGetAge(handle, &ageInfo);
        if(res != MOK)
            qDebug() << QString("ASFGetAge fail: %1").arg(res);
        else
            qDebug() << QString("ASFGetAge success! age: %1").arg(ageInfo.ageArray[0]);


        // 获取性别
        ASF_GenderInfo genderInfo = { 0 };
        res = ASFGetGender(handle, &genderInfo);
        if(res != MOK)
            qDebug() << QString("ASFGetGender fail: %1").arg(res);
        else
            qDebug() << QString("ASFGetGender success! gender: %1").arg(genderInfo.genderArray[0]);


        SafeFree(copyfeature1.feature);		//释放内存
        cvReleaseImage(&cutImg1);
        cvReleaseImage(&cutImg2);

    }
    else {
        qDebug() << "load failed";
    }


    cvReleaseImage(&img1);
    cvReleaseImage(&img2);

    //反初始化
    res = ASFUninitEngine(handle);
    if(res != MOK)
        qDebug() << QString("ALUninitEngine fail: %1").arg(res);
    else
        qDebug() << QString("ALUninitEngine success!: %1").arg(res);

//    getchar();

}

ARC_FACE::~ARC_FACE()
{
    delete ui;
}

void ARC_FACE::CutIplImage(IplImage *src, IplImage *dst, int x, int y)
{
    CvSize size = cvSize(dst->width, dst->height);//区域大小
    cvSetImageROI(src, cvRect(x, y, size.width, size.height));//设置源图像ROI
    cvCopy(src, dst); //复制图像
    cvResetImageROI(src);//源图像用完后，清空ROI
}

void ARC_FACE::timestampToTime(char *timeStamp, char *dateTime, int dateTimeSize)
{
    if(timeStamp == 0) return;
    time_t tTimeStamp = atoll(timeStamp); /* 把字符串转换成长长整型数（64位） */

    struct tm* pTm = gmtime(&tTimeStamp);

    strftime(dateTime, dateTimeSize, "%Y-%m-%d %H:%M:%S", pTm);

}
