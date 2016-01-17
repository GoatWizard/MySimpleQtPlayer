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

     if(_globals->current_active_pls == _globals->current_selected_pls){ //This is needed to select played song if playlist is changed but any song from it wasn't played.
     _globals->TreeItems[_globals->current_played_track_id-1]->setSelected(true);
     }
}

