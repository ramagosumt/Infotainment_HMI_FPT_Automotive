#ifndef STREAMINGVIEWMODEL_H
#define STREAMINGVIEWMODEL_H

#include <QObject>

class StreamingViewModel : public QObject
{
    Q_OBJECT

public:
    explicit StreamingViewModel(QObject *parent = nullptr);

signals:
};

#endif // STREAMINGVIEWMODEL_H
