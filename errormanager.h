#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <QObject>
//#include <QStateMachine>
//include <QState>
//#include <QFinalState>
#include <QTimer>

class MediaViewModel;

class ErrorManager : public QObject
{
    Q_OBJECT

public:
    explicit ErrorManager(MediaViewModel *mediaViewModel, QObject *parent = nullptr);

private:
    //QStateMachine m_stateMachine;
    //QState m_noErrorState;
    //QState m_errorState;
    QTimer m_checkTimer;

    MediaViewModel *m_mediaViewModel;

    void checkMediaStatus();

signals:
    void onErrorDetected();
    void onErrorResolved();
};

#endif // ERRORMANAGER_H
