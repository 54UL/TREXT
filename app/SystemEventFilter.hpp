
#ifndef SYSTEMEVENTFILTER_H
#define SYSTEMEVENTFILTER_H
#include <QObject>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

class SystemEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit SystemEventFilter(QObject *parent = nullptr){}

    bool eventFilter(QObject* object, QEvent* event) override
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_R)
            {

                qDebug()<<"CTRL+R PRESSED!!";
                return true;

            }
        }
//        else if(event->type() == QEvent::MouseButtonPress){
//            qDebug()<<"MouseButtonPress triggered!!";
//        }
//        else if(event->type() == QEvent::MouseButtonRelease){
//            qDebug()<<"MouseButtonRelease triggered!!";
//        }

        return false;
    }
};

#endif // SYSTEMEVENTFILTER_H
