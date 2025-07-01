#include "ErrorManager.h"

ErrorManager::ErrorManager(QObject *parent)
    : QObject(parent)
{
    m_stateMachine = QScxmlStateMachine::fromFile(":/WeatherApp_MVVM/ErrorManager.scxml");

    if (!m_stateMachine) return;

    const QList<QScxmlError> errors = m_stateMachine->parseErrors();
    if (!errors.isEmpty()) return;

    connect(m_stateMachine, &QScxmlStateMachine::runningChanged, this, [this]() {
        if (m_stateMachine->isRunning())
            emit onUpdated();
    });

    connect(m_stateMachine, &QScxmlStateMachine::reachedStableState, this, &ErrorManager::onUpdated);

    m_stateMachine->start();

    m_stateTimer.setInterval(1000);
    m_stateTimer.setSingleShot(false);
    m_stateTimer.start();

    connect(&m_stateTimer, &QTimer::timeout, this, [this]() {
        if (isConnected() || isToggleCheck() || isChecking()) {
            ++m_periodicCurrentTime;
            m_reconnectingTime = 0;
        } else if (isReconnecting() || isNoDisplayError()) {
            m_periodicCurrentTime = 0;
            ++m_reconnectingTime;
        }
        emit onUpdated();
    });
}

int ErrorManager::getPeriodicCurrentTime() const {
    return m_periodicCurrentTime;
}

int ErrorManager::getReconnectingTime() const {
    return m_reconnectingTime;
}

bool ErrorManager::isConnected() const {
    return m_stateMachine->activeStateNames().contains("Connected");
}

bool ErrorManager::isToggleCheck() const {
    return m_stateMachine->activeStateNames().contains("ToggleCheck");
}

bool ErrorManager::isChecking() const {
    return m_stateMachine->activeStateNames().contains("Checking");
}

bool ErrorManager::isReconnecting() const {
    return m_stateMachine->activeStateNames().contains("Reconnecting");
}

bool ErrorManager::isNoDisplayError() const
{
    return m_stateMachine->activeStateNames().contains("NoDisplayError");
}

void ErrorManager::submitEvent(const QString &event)
{
    m_stateMachine->submitEvent(event);
}
