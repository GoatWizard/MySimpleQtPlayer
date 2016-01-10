#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtSql>
#include <QTreeWidget>

#include "myplayertreewidgetitem.h"

class globals
{
public:
    globals();
    void fillPlaylist();

    QString current_selected_pls;
    QString current_active_pls;
    quint16 current_played_track;

    QTreeWidget * playlistTree;
    QList <MyPlayerTreeWidgetItem *> TreeItems;

};

extern globals * _globals;

#endif // GLOBALS_H
