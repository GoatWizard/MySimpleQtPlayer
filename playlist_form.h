#ifndef PLAYLIST_FORM_H
#define PLAYLIST_FORM_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class playlist_form;
}

class playlist_form : public QWidget
{
    Q_OBJECT

public:
    explicit playlist_form(QWidget *parent = 0);
    ~playlist_form();

    void read_db();

private slots:

    void on_newPlaylist_clicked();

    void on_PlaylistWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::playlist_form *ui;
};

#endif // PLAYLIST_FORM_H
