
#ifndef SCREENSHOTHELPER_H
#define SCREENSHOTHELPER_H

#include <QImage>
#include <QObject>
#include <QUrl>

class ScreenshotHelper : public QObject
{
    Q_OBJECT
public:
    explicit ScreenshotHelper(QObject *parent = nullptr);

    //QML METHODS
    Q_INVOKABLE QUrl captureWindow(QWindow *window);

signals:

};

#endif // SCREENSHOTHELPER_H
