#ifndef MYPLAYERTREEWIDGETITEM_H
#define MYPLAYERTREEWIDGETITEM_H

#include <QTreeWidgetItem>
//#include <qDebug>

class MyPlayerTreeWidgetItem : public QObject, public  QTreeWidgetItem
{
public:
    MyPlayerTreeWidgetItem(QTreeWidget *view, int type = Type);
    MyPlayerTreeWidgetItem(QTreeWidgetItem * parent, int type = Type);
    //~MyPlayerTreeWidgetItem(){qDebug() << "MyPlayerTreeWidgetItem destructor";}
    quint16 IdNum;
};

#endif // MYPLAYERTREEWIDGETITEM_H
