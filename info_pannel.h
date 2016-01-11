#ifndef INFO_PANNEL_H
#define INFO_PANNEL_H

#include <QWidget>
//#include <QLabel>

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
    //QLabel * imageLabel;
};

#endif // INFO_PANNEL_H
