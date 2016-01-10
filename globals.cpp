#include "globals.h"

#include "myplayertreewidgetitem.h"

globals::globals()
{

}

globals * _globals;

void globals::fillPlaylist()
{
    playlistTree->clear(); //CHECK THIS MAY CAUSE MEMORY LEAK
    TreeItems.clear();

    QSqlQuery albquery;
    QString querys = "SELECT DISTINCT Album FROM " + QString("TBL") + _globals->current_selected_pls.toLocal8Bit().toHex() ;
    albquery.prepare(querys);
    //albquery.bindValue(":valCsp", _globals->current_selected_pls);
    albquery.exec();
    //qDebug() << albquery.lastError() << _globals->current_selected_pls.toLocal8Bit().toHex();
    while (albquery.next()) { ///Sort by album
        MyPlayerTreeWidgetItem * albumitem =new MyPlayerTreeWidgetItem(_globals->playlistTree);;
        albumitem->setText(0,albquery.value(0).toString());
        albumitem->setExpanded(true);

        QSqlQuery query;
        //query.exec("SELECT Id,Track FROM " + _globals->current_selected_pls + " WHERE Album ='" + albquery.value(0).toString()+ "'");

        QString querystring = "SELECT Id,Track FROM " + QString("TBL") + _globals->current_selected_pls.toLocal8Bit().toHex() + " WHERE Album = :valAlbum";
        query.prepare(querystring);
        query.bindValue(":valAlbum",albquery.value(0).toString());
        query.exec();

        while (query.next()) {
        //qDebug() << query.value(1).toString();
        MyPlayerTreeWidgetItem * songitem = new MyPlayerTreeWidgetItem(albumitem);
        songitem->setText(0,query.value(1).toString());
        songitem->IdNum = query.value(0).toUInt();
        TreeItems.push_back(songitem);
        }
    }
}
