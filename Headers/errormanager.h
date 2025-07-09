#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <QObject>
#include <QScxmlStateMachine>
#include <QTimer>

class ErrorManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int  periodicCurrentTime             READ getPeriodicCurrentTime         NOTIFY onUpdated)
    Q_PROPERTY(int  reconnectingTime                READ getReconnectingTime            NOTIFY onUpdated)
    Q_PROPERTY(bool connected                       READ isConnected                    NOTIFY onUpdated)
    Q_PROPERTY(bool toggleCheck                     READ isToggleCheck                  NOTIFY onUpdated)
    Q_PROPERTY(bool checking                        READ isChecking                     NOTIFY onUpdated)
    Q_PROPERTY(bool reconnecting                    READ isReconnecting                 NOTIFY onUpdated)
    Q_PROPERTY(bool noDisplayError                  READ isNoDisplayError               NOTIFY onUpdated)

public:
    explicit ErrorManager(QObject *parent = nullptr);

    int getPeriodicCurrentTime()                            const;
    int getReconnectingTime()                               const;

    bool isConnected()                                      const;
    bool isToggleCheck()                                    const;
    bool isChecking()                                       const;
    bool isReconnecting()                                   const;
    bool isNoDisplayError()                                 const;

    Q_INVOKABLE void submitEvent(const QString &event);

private:
    QScxmlStateMachine *m_stateMachine;
    QTimer m_stateTimer;

    int m_periodicCurrentTime = 0;
    int m_reconnectingTime = 0;

signals:
    void onUpdated();
};

#endif // ERRORMANAGER_H
