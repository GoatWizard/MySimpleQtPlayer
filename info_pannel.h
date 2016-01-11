#ifndef INFO_PANNEL_H
#define INFO_PANNEL_H

#include <QWidget>
#include <QPixmap>

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

private:
    Ui::info_pannel *ui;

    TWorker * worker;
    QThread * thread;
};

#endif // INFO_PANNEL_H
