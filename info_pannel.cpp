#include "info_pannel.h"
#include "ui_info_pannel.h"

info_pannel::info_pannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info_pannel)
{
    ui->setupUi(this);
}

info_pannel::~info_pannel()
{
    delete ui;
}
