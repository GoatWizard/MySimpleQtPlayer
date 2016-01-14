#ifndef INFO_PANNEL_H
#define INFO_PANNEL_H

#include <QWidget>
#include <QPixmap>
#include <QVideoWidget>

//Cover Art changing thread
#include "tworker.h"
#include <QThread>

namespace Ui {
class info_pannel;
}

class info_pannel : public QWidget
{
    Q_OBJECT

public:
    explicit info_pannel(QWidget *parent = 0);
    ~info_pannel();

    void DisplayCoverArt(QString path);
    void DisplayMediaInfo(QString path);

    QVideoWidget * videoWidget;
    void setIsVideo(bool bIsVideo);
private:
    Ui::info_pannel *ui;

    TWorker * worker;
    QThread * thread;

    QString PreviousCoverArt; //This need to prevent cover art changing when next track folder is same
};

#endif // INFO_PANNEL_H
