
#include "screenshothelper.hpp"
#include "qdebug.h"

#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QPixmap>
#include <QQuickWindow>
#include <QUrl>
#include <QBuffer>
#include <QImage>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <QQuickImageProvider>
//#include <opencv2/core/base64.hpp>
#include <QByteArray>
#include <QRegularExpression>

cv::Mat qImageToCvMat(const QImage& qImage)
{
    QImage convertedImage = qImage.convertToFormat(QImage::Format_RGB888);
    cv::Mat cvMat(convertedImage.height(), convertedImage.width(), CV_8UC3, convertedImage.bits(), convertedImage.bytesPerLine());
    cv::cvtColor(cvMat, cvMat, cv::COLOR_BGR2RGB); // Optional: Convert BGR to RGB format

    return cvMat.clone(); // Return a copy of the cv::Mat
}

//returns the text content from the provided file path
//file: file path
extern const char * ReadImage(const char * file)
{
    // Load the image
    cv::Mat image = cv::imread(file);

    // Create a Tesseract OCR object
    tesseract::TessBaseAPI ocr;
    ocr.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    ocr.SetPageSegMode(tesseract::PSM_AUTO);

    // Convert the image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);



    // Set the image data for OCR
    ocr.SetImage(gray.data, gray.cols, gray.rows, 1, gray.cols);
    ocr.SetSourceResolution(172);

    // Run OCR on the image
    char* text = ocr.GetUTF8Text();

    // Release the memory used by the OCR object and the text
    ocr.End();
    return text;
}

ScreenshotHelper::ScreenshotHelper(QObject *parent)
    : QObject{parent}
{

}

QUrl ScreenshotHelper::captureWindow(QWindow *window)
{
    QScreen* screen = QGuiApplication::primaryScreen();

    if (screen)
    {
        QPixmap pixmap = screen->grabWindow(0);
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");
        QString base64Data = QString::fromLatin1(bytes.toBase64().data());
        QString dataUrl = QStringLiteral("data:image/png;base64,%1").arg(base64Data);
        return QUrl(dataUrl);
    }
    else
    {
        qDebug()<<"No window availible";
        return QUrl();
    }
}

cv::Mat base64ToMat(QString& base64Image, QRect region)
{
    // Remove the data URI scheme if present
    QString cleanedBase64 = base64Image;
    cleanedBase64.remove(QRegularExpression("data:[^;]+;base64,"));

    // Convert QString to QByteArray
    QByteArray imageData = QByteArray::fromBase64(cleanedBase64.toLatin1());

    // Load the image from the decoded data
    QImage image;
    image.loadFromData(imageData);

    return qImageToCvMat(image.copy(region));
}

QString ScreenshotHelper::recognizeText(QString b64Image, QRect region)
{
//    cv::Mat image = qImageToCvMat(*input);
    qDebug()<<"Recognizing text... in region"<< region;
    cv::Mat image = base64ToMat(b64Image, region);
    qDebug()<<"Is empty:"<<image.empty();
    if (image.empty()) return QString("EMPTY IMAGE...");
    // Create a Tesseract OCR object
    tesseract::TessBaseAPI ocr;
    ocr.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    ocr.SetPageSegMode(tesseract::PSM_AUTO);
    // Convert the image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    // Create a window to display the image
    cv::namedWindow("Image", cv::WINDOW_NORMAL);

    // Show the image in the window
    cv::imshow("Image", gray);
    // Set the image data for OCR
    ocr.SetImage(gray.data, gray.cols, gray.rows, 1, gray.cols);
    ocr.SetSourceResolution(300);

    // Run OCR on the image
    char* text = ocr.GetUTF8Text();
    qDebug()<<"Recognized text "<<text;
    // Release the memory used by the OCR object and the text
    ocr.End();
    return QString(text); // free the memory pls
}

