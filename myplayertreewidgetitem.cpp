#include "myplayertreewidgetitem.h"

//MyPlayerTreeWidgetItem::MyPlayerTreeWidgetItem(QTreeWidget *parent)
//{

//}

MyPlayerTreeWidgetItem::MyPlayerTreeWidgetItem(QTreeWidget *view, int type)  : QTreeWidgetItem(view,type)
{

}

MyPlayerTreeWidgetItem::MyPlayerTreeWidgetItem(QTreeWidgetItem * parent, int type) :QTreeWidgetItem(parent,type)
{

}
