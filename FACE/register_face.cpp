#include "register_face.h"
#include "ui_register_face.h"

REGISTER_FACE::REGISTER_FACE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::REGISTER_FACE)
{
    ui->setupUi(this);

    similarity = 0.90;
    init_system();

    video_timer = new QTimer(this);
    connect(video_timer, &QTimer::timeout, this, &REGISTER_FACE::displayVideo);

    QMenu *menu = new QMenu("注册",this);

    QAction *image_action = new QAction(QString::fromLocal8Bit("图片注册"));
    QAction *video_action = new QAction(QString::fromLocal8Bit("视频注册"));
    menu->addAction(video_action);
    menu->addAction(image_action);

    ui->btnRegister->setMenu(menu);
    ui->btnRegister->setPopupMode(QToolButton::MenuButtonPopup);

    connect(image_action, &QAction::triggered, this, &REGISTER_FACE::btnActionImage);
    connect(video_action, &QAction::triggered, this, &REGISTER_FACE::btnActionVideo);

    face_sql = new FACE_SQL;
    db = face_sql->create_db("tbdb", "user");

    if(!face_sql->isExistTable(db, "userData")) {
        if(face_sql->create_table(db, "create table userData        \
                           (                                        \
                             id int unsigned not null primary key,  \
                             username char(16) not null,            \
                             pl char(9) not null,                   \
                             reserve1 char(9),                      \
                             reserve2 char(9),                      \
                             featuresize int unsigned not null,     \
                             featuredata blob not null,             \
                             imgtype int not null,                  \
                             imgcols int unsigned not null,         \
                             imgrows int unsigned not null,         \
                             imgsize int unsigned not null,         \
                             imgdata blob not null                  \
                           );")) qDebug() << "create table success.";
                              else qDebug() << "create table failed.";
    }
    else qDebug() << "table userData is existed.";

    this->getImagesFeature("../rimg", feature_list);


}

REGISTER_FACE::~REGISTER_FACE()
{
    db.close();
    video_timer->stop();
    ASFUninitEngine(image_handle);
    camera.release();
    delete ui;
}

void REGISTER_FACE::init_system()
{

    MRESULT res = MOK;
    QString APP_KEY = "kf4Er8xXdzWCD97fS44ghb6Lg9MMDtzPbqftjacyuM2";
    QString SDK_KEY = "BHwSM2pzFzcHUE8ZT9EfuSJENVLcHgHXGq3q6bEEmnkb";
    memStorage = cvCreateMemStorage(0); /* 创建一个内存存储块，0默认大小64KB */
    cascadeClassifier = new CvHaarClassifierCascade;
    cascadeClassifier = (CvHaarClassifierCascade*)cvLoad("./haarcascade_frontalface_alt2.xml");

    res = ASFOnlineActivation(APP_KEY.toLatin1().data(), SDK_KEY.toLatin1().data());
    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
        qDebug() << "ASFActivation fail";
    else
        qDebug() << "ASFActivation sucess";

    //初始化接口

    MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION ; /* 只用人脸检测和人脸特征 */
    res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_ONLY, 30, 5, mask, &image_handle);
    if (res != MOK)
        qDebug() << "ASFInitEngine fail";
    else
        qDebug() << "ASFInitEngine success";


}

void REGISTER_FACE::CutIplImage(IplImage *src, IplImage *dst, int x, int y)
{
    CvSize size = cvSize(dst->width, dst->height);//区域大小
    cvSetImageROI(src, cvRect(x, y, size.width, size.height));//设置源图像ROI
    cvCopy(src, dst); //复制图像
    cvResetImageROI(src);//源图像用完后，清空ROI
}

bool REGISTER_FACE::getFeatureByImage(QString img_path, ASF_FaceFeature &copyfeature)
{
    MRESULT res = MOK;
    IplImage* img1 = cvLoadImage(img_path.toLatin1().data());

    if(!img1) return false;

    ASF_MultiFaceInfo detectedFaces = { 0 }; /* 多人脸信息 */
    ASF_SingleFaceInfo SingleDetectedFaces = { 0 }; /* 单人脸信息 */
    ASF_FaceFeature feature = { 0 }; /* 人脸特征 */
    /* 4字节对齐 */
    IplImage* cutImg1 = cvCreateImage(cvSize(img1->width - img1->width % 4, img1->height), IPL_DEPTH_8U, img1->nChannels);
    CutIplImage(img1, cutImg1, 0, 0);

    ASVLOFFSCREEN offscreen = {0};
    offscreen.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    offscreen.i32Width = cutImg1->width;
    offscreen.i32Height = cutImg1->height;
    offscreen.pi32Pitch[0] = cutImg1->widthStep;
    offscreen.ppu8Plane[0] = (MUInt8*)cutImg1->imageData;

    res = ASFDetectFacesEx(image_handle, &offscreen, &detectedFaces);
    if(res == MOK && detectedFaces.faceNum >=1) {
        SingleDetectedFaces.faceRect.left = detectedFaces.faceRect[0].left;
        SingleDetectedFaces.faceRect.top = detectedFaces.faceRect[0].top;
        SingleDetectedFaces.faceRect.right = detectedFaces.faceRect[0].right;
        SingleDetectedFaces.faceRect.bottom = detectedFaces.faceRect[0].bottom;
        SingleDetectedFaces.faceOrient = detectedFaces.faceOrient[0];

        res = ASFFaceFeatureExtractEx(image_handle, &offscreen, &SingleDetectedFaces, &feature);
        if(res == MOK) { /* 第一次提取特征需进行拷贝，因为使用同一个引擎，第二次拷贝会覆盖第一次提取的结果 */
            //拷贝feature
            copyfeature.featureSize = feature.featureSize;
            copyfeature.feature = (MByte*)malloc(feature.featureSize);
            memset(copyfeature.feature, 0, feature.featureSize);
            memcpy(copyfeature.feature, feature.feature, feature.featureSize);
        }
        else return false;
    }else return false;
    return true;


}

bool REGISTER_FACE::getFeatureByVideo(cv::Mat img, ASF_FaceFeature &copyfeature)
{
    MRESULT res = MOK;
    IplImage imgTmp = img;
    IplImage *img1 = cvCloneImage(&imgTmp); /* 深拷贝 */

    if(!img1) return false;

    ASF_MultiFaceInfo detectedFaces = { 0 }; /* 多人脸信息 */
    ASF_SingleFaceInfo SingleDetectedFaces = { 0 }; /* 单人脸信息 */
    ASF_FaceFeature feature = { 0 }; /* 人脸特征 */
    /* 4字节对齐 */
    IplImage* cutImg1 = cvCreateImage(cvSize(img1->width - img1->width % 4, img1->height), IPL_DEPTH_8U, img1->nChannels);
    CutIplImage(img1, cutImg1, 0, 0);

    ASVLOFFSCREEN offscreen = {0};
    offscreen.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    offscreen.i32Width = cutImg1->width;
    offscreen.i32Height = cutImg1->height;
    offscreen.pi32Pitch[0] = cutImg1->widthStep;
    offscreen.ppu8Plane[0] = (MUInt8*)cutImg1->imageData;

    res = ASFDetectFacesEx(image_handle, &offscreen, &detectedFaces);
    if(res == MOK && detectedFaces.faceNum >=1) {
        SingleDetectedFaces.faceRect.left = detectedFaces.faceRect[0].left;
        SingleDetectedFaces.faceRect.top = detectedFaces.faceRect[0].top;
        SingleDetectedFaces.faceRect.right = detectedFaces.faceRect[0].right;
        SingleDetectedFaces.faceRect.bottom = detectedFaces.faceRect[0].bottom;
        SingleDetectedFaces.faceOrient = detectedFaces.faceOrient[0];

        res = ASFFaceFeatureExtractEx(image_handle, &offscreen, &SingleDetectedFaces, &feature);
        if(res == MOK) { /* 第一次提取特征需进行拷贝，因为使用同一个引擎，第二次拷贝会覆盖第一次提取的结果 */
            //拷贝feature
            copyfeature.featureSize = feature.featureSize;
            copyfeature.feature = (MByte*)malloc(feature.featureSize);
            memset(copyfeature.feature, 0, feature.featureSize);
            memcpy(copyfeature.feature, feature.feature, feature.featureSize);
        }
        else return false;
    }else return false;
                                  return true;
    }

QStringList REGISTER_FACE::getImageFilePath(QString dirpath)
{
    QDir dir(dirpath);
    QStringList files_path;
    files_path.clear();
    if(!dir.exists()) return files_path;

    QStringList nameFilters;
    nameFilters << "*.png" << "*.jpg";
    QStringList files_name = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);

    for (int i = 0; i < files_name.size(); i++) {
        files_path << "../rimg/" + files_name.at(i);
    }

     return files_path;
}

void REGISTER_FACE::getImagesFeature(QString dirpath, QList<ASF_FaceFeature> &list)
{
    MRESULT res = MOK;
    QStringList files_path = getImageFilePath(dirpath);
    if(files_path.isEmpty()) return;
    img_file_list = files_path;
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

        res = ASFDetectFacesEx(image_handle, &offscreen2, &detectedFaces2);
        if (MOK == res && detectedFaces2.faceNum >= 1)
        {
            SingleDetectedFaces2.faceRect.left = detectedFaces2.faceRect[0].left;
            SingleDetectedFaces2.faceRect.top = detectedFaces2.faceRect[0].top;
            SingleDetectedFaces2.faceRect.right = detectedFaces2.faceRect[0].right;
            SingleDetectedFaces2.faceRect.bottom = detectedFaces2.faceRect[0].bottom;
            SingleDetectedFaces2.faceOrient = detectedFaces2.faceOrient[0];

            res = ASFFaceFeatureExtractEx(image_handle, &offscreen2, &SingleDetectedFaces2, &feature2);
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



void REGISTER_FACE::on_btnRegister_clicked()
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

void REGISTER_FACE::on_btnConfirmRegister_clicked()
{

    if(Action_Video_Clicked_Flag) {
        Action_Video_Clicked_Flag = false;
        REGISTER_FLAG = true;
    }
    else if(Action_Image_Clicked_Flag)
    {
        Action_Image_Clicked_Flag = false;
        SQL_DATA_TypeDef sdt;
        if(ui->lineEditFaceIdR->text().isEmpty() || ui->lineEditLicenseR->text().isEmpty()) {
            qDebug() << "please fill the faceid lineeidt and the username lineedit.";
            return;
        }
        else {
            cv::Mat img = cv::imread(img_path.toLatin1().data());
            cv::Mat ret_image;
            cv::cvtColor(img, ret_image, CV_BGR2RGB);
            sdt.t_id = ui->lineEditFaceIdR->text().toInt();
            sdt.t_username = ui->lineEditLicenseR->text();
            sdt.t_pl = "豫AF56H9";
            sdt.t_reserve1 = "_";
            sdt.t_reserve2 = "_";
            sdt.t_featuresize = img_feature.featureSize;
            QByteArray featureByte = QByteArray::fromRawData((const char*)img_feature.feature, img_feature.featureSize);

            sdt.t_featuredata = featureByte;
            sdt.t_imgtype = ret_image.type();
            sdt.t_imgcols = ret_image.cols;
            sdt.t_imgrows = ret_image.rows;
            sdt.t_imgsize = ret_image.elemSize();

            const size_t data_size = ret_image.cols * ret_image.rows * ret_image.elemSize();

            QByteArray imgByte = QByteArray::fromRawData( (const char*)ret_image.ptr(), data_size );

            sdt.t_imgdata = imgByte;

            if(face_sql->insert_data_into_table(db, "userData", &sdt))
            qDebug() << "insert data into table success.";
            else qDebug() << "insert data into table failed.";
        }


    }
    else qDebug() << "please re-select the face image to be registered.";


}

void REGISTER_FACE::on_btnMatch_clicked()
{

    int id = ui->lineEditFaceIdM->text().toInt();
    SQL_DATA_TypeDef sdt;
    if(face_sql->get_userInfo(db, "userData", id, sdt)) {
        qDebug() << "get userInfo success";
    }
    else qDebug() << "get userInfo failed";

    ui->lineEditFaceIdM->setText(QString::number(sdt.t_id));
    ui->lineEditLicenseM->setText(sdt.t_username);
    qDebug() << sdt.t_pl.toLocal8Bit();

    cv::Mat img = cv::Mat(sdt.t_imgrows,sdt.t_imgcols, sdt.t_imgtype, (void*)sdt.t_imgdata.data()).clone();

//    cv::Mat img1;
//    cv::cvtColor(img, img1, CV_BGR2RGB);

    QImage image((const uchar*)img.data, img.cols, img.rows, QImage::Format_RGB888);
    ui->labelMatch->setPixmap(QPixmap::fromImage(image));
    img.release();

}

void REGISTER_FACE::on_btnConfirmMatch_clicked()
{
    int id = ui->lineEditFaceIdM->text().toInt();
    SQL_DATA_TypeDef sdt;
    if(face_sql->get_userInfo(db, "userData", id, sdt)) {
        qDebug() << "get userInfo success";
    }
    else qDebug() << "get userInfo failed";


        /* 单人脸特征对比 */
        MFloat confidenceLevel;
        ASF_FaceFeature feature1 = {0};
        feature1.featureSize = sdt.t_featuresize;
        feature1.feature = (MByte*)sdt.t_featuredata.data();
        for (int i = 0; i < feature_list.size(); i++) {

            if(MOK == ASFFaceFeatureCompare(image_handle, &feature1, &feature_list[i], &confidenceLevel)) {
                qDebug() << confidenceLevel;
                if(confidenceLevel >= similarity) {
                    QImage image;
                    image.load(img_file_list.at(i));
                    ui->labelMatch_2->setPixmap(QPixmap::fromImage(image.scaled(ui->labelMatch->width(),
                                                                              ui->labelMatch->height(),
                                                                              Qt::KeepAspectRatio)));

                    break;
                }
            }

        }



}


void REGISTER_FACE::displayVideo()
{
  if(!camera.isOpened()) {
      qDebug() << "camera opened failed.";
      return ;
  }
  cv::Mat image;
  cv::Mat ret_image;
  cv::Mat grayimage;
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

      cvClearMemStorage(memStorage);

      CvSeq *seqFace = cvHaarDetectObjects(&img, cascadeClassifier, memStorage);

      for (int i = 0; i < seqFace->total; i++) {

          CvRect* r = (CvRect*)cvGetSeqElem(seqFace, i); /* 利用强制类型转换，转换为序列中实际存储的数据类型 */
          CvPoint center;
          int radius;
          center.x = cvRound((r->x + r->width * 0.5));
          center.y = cvRound((r->y + r->height * 0.5));
          radius = cvRound((r->width + r->height) * 0.25);

          cvCircle(&dspimg, center, radius, FaceCirclecolors[i % 8],1);

      }

      if(REGISTER_FLAG)
      {
          REGISTER_FLAG = false;
          ASF_FaceFeature m_feature = {0};
          if(getFeatureByVideo(image,m_feature)) {
              qDebug() << "get feature success";
               SQL_DATA_TypeDef sdt;
              if(ui->lineEditFaceIdR->text().isEmpty() || ui->lineEditLicenseR->text().isEmpty()) {
                  qDebug() << "please fill the faceid lineeidt and the username lineedit.";
              }
              else {
                sdt.t_id = ui->lineEditFaceIdR->text().toInt();
                sdt.t_username = ui->lineEditLicenseR->text();
                sdt.t_pl = "豫AF56H9";
                sdt.t_reserve1 = "_";
                sdt.t_reserve2 = "_";
                sdt.t_featuresize = m_feature.featureSize;
                QByteArray featureByte = QByteArray::fromRawData((const char*)m_feature.feature, m_feature.featureSize);
                sdt.t_featuredata = featureByte;
                sdt.t_imgtype = ret_image.type();
                sdt.t_imgcols = ret_image.cols;
                sdt.t_imgrows = ret_image.rows;
                sdt.t_imgsize = ret_image.elemSize();

                const size_t data_size = ret_image.cols * ret_image.rows * ret_image.elemSize();

                QByteArray imgByte = QByteArray::fromRawData( (const char*)ret_image.ptr(), data_size );

                sdt.t_imgdata = imgByte;
//                sdt.t_datetime = QDateTime::currentDateTime();
//                qDebug() << QDateTime::currentDateTime().toString("yyyy-M-d hh:mm:ss");

                if(face_sql->insert_data_into_table(db, "userData", &sdt))
                    qDebug() << "insert data into table success.";
                else qDebug() << "insert data into table failed.";


              }

          }
          else qDebug() << "get feature failed";
      }


      QImage q_image((const uchar*)ret_image.data,ret_image.cols,ret_image.rows, QImage::Format_RGB888); /* 截图彩色 */
      ui->labelDisplay->setPixmap(QPixmap::fromImage(q_image));


  }

}



void REGISTER_FACE::btnActionImage()
{
    if(video_timer->isActive()) video_timer->stop();

    ui->labelDisplay->clear();

    img_path = "";
    QString imagefilepath = QFileDialog::getOpenFileName(this, "select register image", "../", "IMAGE(*.png *.jpg)");
    if(imagefilepath.isEmpty()) return;
    img_path = imagefilepath;
    QImage image;
    image.load(imagefilepath);
    ui->labelDisplay->setPixmap(QPixmap::fromImage(image.scaled(ui->labelDisplay->width(),
                                                                ui->labelDisplay->height(),
                                                                Qt::KeepAspectRatio)));



//    ASF_FaceFeature m_feature = {0};
    img_feature = {0};
    if(getFeatureByImage(imagefilepath,img_feature)) {
        qDebug() << "get feature success";
        Action_Image_Clicked_Flag = true;
        Action_Video_Clicked_Flag = false;
        SQL_DATA_TypeDef sdt;

    }
    else qDebug() << "get feature failed";

}

void REGISTER_FACE::btnActionVideo()
{
    camera.open(0);
    camera.set(CV_CAP_PROP_FRAME_WIDTH,ui->labelDisplay->width());
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,ui->labelDisplay->height());
    if(!camera.isOpened()) {
        qDebug() << "camera0 open failed.";
        return;
    }
    Action_Video_Clicked_Flag = true;
    Action_Image_Clicked_Flag = false;
    video_timer->start(150);
}

//void REGISTER_FACE::on_pushButton_clicked()
//{
//    SAVE_IMAGE_DATA_FLAG = true;
//}

//void REGISTER_FACE::on_pushButton_2_clicked()
//{
//    QFile file("./initfile/imagedata.ff");
//    if(file.open(QIODevice::ReadOnly)) {
//        QDataStream stream(&file);

//        try {

//            int type,rows,cols;
//            stream >> type >> rows >> cols;
//            qDebug() << type << "_" << rows << "_" << cols;
//            QByteArray data;
//            stream >> data;
//            file.close();

//            cv::Mat immg = cv::Mat(rows, cols, type, (void*)data.data());
//            QImage q_image((const uchar*)immg.data,immg.cols, immg.rows, QImage::Format_RGB888); /* 截图彩色 */
//            ui->labelMatch->setPixmap(QPixmap::fromImage(q_image));
//        } catch (...) {
//            qDebug() << "error";
//        }




//    }
//}



                              //void REGISTER_FACE::displayVideo()
                              //{
                              //    if(!camera.isOpened()) {
                              //        qDebug() << "camera opened failed.";
                              //        return ;
                              //    }
                              //    cv::Mat image;
                              //    cv::Mat ret_image;
                              //    cv::Mat grayimage;
                              //    if(!camera.read(image)) {
                              //        qDebug() << "The read image is empty";
                              //        return ;
                              //    }
                              //    cv::cvtColor(image, grayimage, CV_BGR2GRAY);
                              //    cv::cvtColor(image, ret_image, CV_BGR2RGB);
                              //    IplImage img(grayimage);
                              //    IplImage dspimg(ret_image);
                              //    if(cascadeClassifier != NULL) {
                              //        CvScalar FaceCirclecolors[] = {
                              //            {{0,0,255}},
                              //            {{0,128,255}},
                              //            {{0,255,255}},
                              //            {{0,255,0}},
                              //            {{255,128,0}},
                              //            {{255,255,0}},
                              //            {{255,0,0}},
                              //            {{255,0,255}},
                              //        };

                              //        cvClearMemStorage(memStorage);

                              //        CvSeq *seqFace = cvHaarDetectObjects(&img, cascadeClassifier, memStorage);

                              //        for (int i = 0; i < seqFace->total; i++) {

                              //            CvRect* r = (CvRect*)cvGetSeqElem(seqFace, i); /* 利用强制类型转换，转换为序列中实际存储的数据类型 */
                              //            CvPoint center;
                              //            int radius;
                              //            center.x = cvRound((r->x + r->width * 0.5));
                              //            center.y = cvRound((r->y + r->height * 0.5));
                              //            radius = cvRound((r->width + r->height) * 0.25);

                              //            cvCircle(&dspimg, center, radius, FaceCirclecolors[i % 8],1);

                              //        }

                              //        if(REGISTER_FLAG)
                              //        {
                              //            REGISTER_FLAG = false;
                              //            ASF_FaceFeature m_feature = {0};
                              //            if(getFeatureByVideo(image,m_feature)) {
                              //                qDebug() << "get feature success";
                              //                FACE_DATA_TypeDef face_data;
                              //                if(ui->lineEditFaceIdR->text().isEmpty() || ui->lineEditLicenseR->text().isEmpty()) {
                              //                    qDebug() << "please fill the faceid lineeidt and the username lineedit.";
                              //                }
                              //                else {
                              //                    face_data.t_id = ui->lineEditFaceIdR->text().toInt();;
                              //                    face_data.t_username = ui->lineEditLicenseR->text();
                              //                    face_data.t_feature = m_feature;
                              //                    face_data.t_image = ret_image;
                              //                    qDebug() <<"video:" << ret_image.type();
                              //                    if(face_bin->append(face_bin->get_file_name(), face_data))
                              //                        qDebug() << "register feature success";
                              //                    else qDebug() << "register feature failed";
                              //                }

                              //            }
                              //            else qDebug() << "get feature failed";
                              //        }
                              //        QImage q_image((const uchar*)ret_image.data,ret_image.cols,ret_image.rows, QImage::Format_RGB888); /* 截图彩色 */
                              //        ui->labelDisplay->setPixmap(QPixmap::fromImage(q_image));


                              //    }

                              //}


                              //bool REGISTER_FACE::registerFaceFeature(QString filepath, ASF_FaceFeature feature)
                              //{
                              //    QFile file(filepath);

                              //    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) return false;

                              //    QDataStream stream(&file);
                              //    stream.writeRawData(reinterpret_cast<char*>(&feature.featureSize) , sizeof (feature.featureSize));
                              //    stream.writeRawData(reinterpret_cast<char*>(feature.feature) , feature.featureSize);
                              //    file.close();
                              //    return true;
                              //}


                              //bool REGISTER_FACE::readFaceFeature(QString filepath, QList<ASF_FaceFeature> &list)
                              //{
                              //    QFile file(filepath);
                              //    if(file.open(QIODevice::ReadOnly)) {
                              //        QDataStream stream(&file);
                              //        ASF_FaceFeature l;
                              //        while (!file.atEnd()) {
                              //            stream.readRawData(reinterpret_cast<char*>(&l.featureSize), sizeof (l.featureSize));
                              //            l.feature = reinterpret_cast<MByte*>(malloc(l.featureSize));
                              //            stream.readRawData(reinterpret_cast<char*>(l.feature), l.featureSize);
                              //            list << l;
                              //            l.featureSize = 0;
                              //            free(l.feature);

                              //        }
                              //        file.close();
                              //        return true;
                              //    }
                              //    else return false;
                              //}

                              //bool REGISTER_FACE::readFaceFeature(QString filepath, QList<face_data_def>& face_data)
                              //{
                              //    QFile file(filepath);
                              //    if(file.open(QIODevice::ReadOnly)) {
                              //        QDataStream stream(&file);
                              //        face_data_def s_face_data = {0};
                              //        while (!file.atEnd()) {

                              //            stream >> s_face_data.faceid;
                              //            stream >> s_face_data.username;
                              //            stream.readRawData(reinterpret_cast<char*>(&s_face_data.feature.featureSize), sizeof (s_face_data.feature.featureSize));
                              //            s_face_data.feature.feature = reinterpret_cast<MByte*>(malloc(s_face_data.feature.featureSize));
                              //            stream.readRawData(reinterpret_cast<char*>(s_face_data.feature.feature), s_face_data.feature.featureSize);
                              //            face_data << s_face_data;
                              //            s_face_data = {0};
                              //            free(s_face_data.feature.feature);

                              //        }
                              //        file.close();
                              //        return true;
                              //    }
                              //    else return false;
                              //}

                              //bool REGISTER_FACE::registerFaceFeature(QString filepath, face_data_def face_data)
                              //{
                              //    QFile file(filepath);

                              //    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) return false;

                              //    QDataStream stream(&file);

                              //    stream << face_data.faceid;
                              //    stream << face_data.username;
                              //    stream.writeRawData(reinterpret_cast<char*>(&face_data.feature.featureSize) , sizeof (face_data.feature.featureSize));
                              //    stream.writeRawData(reinterpret_cast<char*>(face_data.feature.feature) , face_data.feature.featureSize);
                              //    file.close();
                              //    return true;

                              //}
//                              FACE_DATA_TypeDef face_data;
//                              if(face_bin->read(face_bin->get_file_name(), face_data, 4)) {
//                                  qDebug() << face_data.t_id;
//                                  qDebug() << face_data.t_image.type();
//                                  ui->lineEditFaceIdM->setText(QString::number(face_data.t_id));
//                                  ui->lineEditLicenseM->setText(face_data.t_username);
//                                  QImage q_image((const uchar*)face_data.t_image.data,face_data.t_image.cols, face_data.t_image.rows, QImage::Format_RGB888); /* 截图彩色 */
//                                  ui->labelMatch->clear();
//                                  ui->labelMatch->setPixmap(QPixmap::fromImage(q_image));
//                              }
//                              else qDebug() << "match error";


//                              QList<FACE_DATA_TypeDef> face_data_list;
//                              int count = face_bin->readAll(face_bin->get_file_name(), face_data_list);
//                              qDebug() << count;

//                              qDebug() << face_data_list[0].t_id;
//                              ui->lineEditFaceIdM->setText(QString::number(face_data_list[0].t_id));
//                              qDebug() << face_data_list[0].t_id;
//                              ui->lineEditLicenseM->setText(face_data_list[0].t_username);
//                              QImage q_image((const uchar*)face_data_list[0].t_image.data,face_data_list[0].t_image.cols, face_data_list[0].t_image.rows, QImage::Format_RGB888); /* 截图彩色 */

//                              ui->labelMatch->clear();
//                              ui->labelMatch->setPixmap(QPixmap::fromImage(q_image));
