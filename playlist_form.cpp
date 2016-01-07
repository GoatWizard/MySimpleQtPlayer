#include "playlist_form.h"
#include "ui_playlist_form.h"

#include <QInputDialog>
#include <QtSql>

#include "globals.h"
//#include "myplayertreewidgetitem.h"


playlist_form::playlist_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playlist_form)
{
    ui->setupUi(this);
    read_db();
}

playlist_form::~playlist_form()
{
    delete ui;
}

void playlist_form::on_PlaylistWidget_clicked(const QModelIndex &index)
{
    
}

void playlist_form::read_db()
{
    QSqlQuery query;
    query.exec("SELECT Name FROM Playlists");

    while (query.next()) {
             QString plname = query.value(0).toString();
             ui->PlaylistWidget->addItem(plname);
    }
}


void playlist_form::on_newPlaylist_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Playlist name:"), QLineEdit::Normal,"default", &ok);

    if (ok && !text.isEmpty()){
        //Sql ops
        QSqlQuery query;
        query.exec("create table if not exists Playlists (Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, Name varchar(20))");
        query.exec("insert into Playlists (Name) values('" + text + "')");
        query.exec("create table " + QString("TBL") + text.toLocal8Bit().toHex() +" (Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL , Path varchar(20), Album varchar(20), Track varchar(20))");
        //
        ui->PlaylistWidget->addItem(text);
        _globals->current_selected_pls = text;
    }

}

void playlist_form::on_PlaylistWidget_itemClicked(QListWidgetItem *item)
{
     _globals->current_selected_pls = item->text();
     _globals->fillPlaylist();
}
/*
void fillPlaylist()
{
    _globals->playlistTree->clear(); //CHECK THIS MAY CAUSE MEMORY LEAK

    QSqlQuery albquery;
    QString querys = "SELECT DISTINCT Album FROM " + QString("TBL") + _globals->current_selected_pls.toLocal8Bit().toHex() ;
    albquery.prepare(querys);
    //albquery.bindValue(":valCsp", _globals->current_selected_pls);
    albquery.exec();
    qDebug() << albquery.lastError() << _globals->current_selected_pls.toLocal8Bit().toHex();
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
        }
    }
}
*/
