#ifndef MYPLAYERTREEWIDGETITEM_H
#define MYPLAYERTREEWIDGETITEM_H

#include <QTreeWidgetItem>

class MyPlayerTreeWidgetItem : public QObject, public  QTreeWidgetItem
{
    //Q_OBJECT
public:
    MyPlayerTreeWidgetItem(QTreeWidget *view, int type = Type);
    MyPlayerTreeWidgetItem(QTreeWidgetItem * parent, int type = Type);
    //MyPlayerTreeWidgetItem(QTreeWidget* parent);
     //MyPlayerTreeWidgetItem(QTreeWidget *view, int type = Type);
     //MyPlayerTreeWidgetItem (QTreeWidget * parent);
    quint16 IdNum;
};

#endif // MYPLAYERTREEWIDGETITEM_H
