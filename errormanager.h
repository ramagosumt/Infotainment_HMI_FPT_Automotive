#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <QObject>
#include <QScxmlStateMachine>
#include <QTimer>

class ErrorManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int  periodicCurrentTime     READ getPeriodicCurrentTime     NOTIFY updated)
    Q_PROPERTY(int  reconnectingTime        READ getReconnectingTime        NOTIFY updated)
    Q_PROPERTY(bool connected               READ isConnected                NOTIFY updated)
    Q_PROPERTY(bool toggleCheck             READ isToggleCheck              NOTIFY updated)
    Q_PROPERTY(bool checking                READ isChecking                 NOTIFY updated)
    Q_PROPERTY(bool reconnecting            READ isReconnecting             NOTIFY updated)
    Q_PROPERTY(bool noDisplayError          READ isNoDisplayError           NOTIFY updated)

public:
    explicit ErrorManager(QObject *parent = nullptr);

    int getPeriodicCurrentTime()    const;
    int getReconnectingTime()       const;

    bool isConnected()              const;
    bool isToggleCheck()            const;
    bool isChecking()               const;
    bool isReconnecting()           const;
    bool isNoDisplayError()         const;

    Q_INVOKABLE void submitEvent(const QString &event);

private:
    QScxmlStateMachine *m_stateMachine;
    QTimer m_stateTimer;

    int m_periodicCurrentTime = 0;
    int m_reconnectingTime = 0;

signals:
    void updated();
};

#endif // ERRORMANAGER_H
