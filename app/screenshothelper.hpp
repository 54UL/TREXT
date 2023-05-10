
#ifndef SCREENSHOTHELPER_H
#define SCREENSHOTHELPER_H

#include <QImage>
#include <QObject>
#include <QUrl>
#include <QImage>
#include <QQuickImageProvider>

class ScreenshotHelper : public QObject
{
    Q_OBJECT
public:
    explicit ScreenshotHelper(QObject *parent = nullptr);

    //QML METHODS
    Q_INVOKABLE QUrl captureWindow(QWindow *window);
    Q_INVOKABLE QString recognizeText(QString b64Image, QRect region);
signals:

};

#endif // SCREENSHOTHELPER_H
