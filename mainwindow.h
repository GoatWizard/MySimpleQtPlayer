#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

#include <QtSql>

#include "playlist_form.h"
#include "info_pannel.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openFile();
    void playFile(QString fname);
private slots:

    void on_PlayButton_clicked();

    void on_Pause_clicked();

    void on_Stop_clicked();

    //My custom slots
    //void ShowContextMenu(const QPoint& pos);
    void AddItemsMenuFilesSlot();
    void AddItemsMenuFolderSlot();

    //Playback progres slider
    void seek(int seconds);
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);

    void  mediaStatusChanged(QMediaPlayer::MediaStatus status);

    //

    void on_VolumeSlider_valueChanged(int value);

    void on_MuteButton_clicked();

    void on_NextTrackButton_clicked();

    void on_PrevTrackButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer mediaPlayer;
    bool bIsPaused = true;
    void open_sqlite_db();
    void ListDirRecursive(QString directory);
    void PlayTrack();
    void seekTrack(qint16 offset);
    ///Forms
    playlist_form * plf;
    info_pannel * ipn;
};

#endif // MAINWINDOW_H
