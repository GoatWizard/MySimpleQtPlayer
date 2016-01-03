#ifndef GLOBALS_H
#define GLOBALS_H

//#include <QString>
#include <QtSql>

class globals
{
public:
    globals();
    QString current_selected_pls;

     QSqlTableModel * model;

    void initializeModel();
};

extern globals * _globals;

#endif // GLOBALS_H
