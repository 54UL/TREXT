
#include "screenshothelper.hpp"
#include "qdebug.h"

#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QPixmap>
#include <QQuickWindow>
#include <QUrl>
#include <QBuffer>

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
