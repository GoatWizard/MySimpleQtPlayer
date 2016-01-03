#ifndef INFO_PANNEL_H
#define INFO_PANNEL_H

#include <QWidget>

namespace Ui {
class info_pannel;
}

class info_pannel : public QWidget
{
    Q_OBJECT

public:
    explicit info_pannel(QWidget *parent = 0);
    ~info_pannel();

private:
    Ui::info_pannel *ui;
};

#endif // INFO_PANNEL_H
