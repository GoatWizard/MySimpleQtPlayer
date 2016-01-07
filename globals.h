#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtSql>
#include <QTreeWidget>

class globals
{
public:
    globals();
    QString current_selected_pls;
    QTreeWidget * playlistTree;
};

extern globals * _globals;

#endif // GLOBALS_H
