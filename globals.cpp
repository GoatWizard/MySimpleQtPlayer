#include "globals.h"

globals::globals()
{
    model = new QSqlTableModel;
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Path"));
    model->setHeaderData(2, Qt::Vertical, QObject::tr("Album"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Track"));
    qDebug() << "Globals Cinstructor";
}

void globals::initializeModel()
{
    //model = new QSqlTableModel;
    model->setTable(current_selected_pls);
    model->select();
}

globals * _globals;

