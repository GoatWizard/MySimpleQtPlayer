#ifndef TWORKER_H
#define TWORKER_H

#include <QDebug>
#include <QThread>
#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QEventLoop>

#include <QLabel>
#include <QPixmap>

class TWorker : public QObject
{
    Q_OBJECT
public:
    explicit TWorker(QObject *parent = 0);
    ~TWorker();

    void requestWork();
    void abort();

    QLabel * imageLabel;
    QList<QPixmap *> CoverArtList;
    QString dirpath;
private:
    bool _working;
    bool _abort;
    QMutex mutex;

    quint16 imagecounter = 0;
signals:
    void workRequested();
    void valueChanged(const QString &value);
    void finished();

public slots:
     void doWork();
};

#endif // TWORKER_H
