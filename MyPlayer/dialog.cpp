#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);

    connect(player, &QMediaPlayer::positionChanged, this, &Dialog::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &Dialog::on_durationChanged);
    player->setMedia(QUrl::fromLocalFile("/home/saikrishna/Downloads/random stuff/Chumma Kizhi-Masstamilan.in.mp3"));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(position);
}

void Dialog::on_sliderVolume_sliderMoved(int position)
{
    player->setVolume(position);
}

void Dialog::on_startButton_clicked()
{
    //Load the file
    //player->setMedia(QUrl::fromLocalFile("/home/saikrishna/Downloads/random stuff/Chumma Kizhi-Masstamilan.in.mp3"));

    if (ui->startButton->isChecked()){
        ui->startButton->setText("Play");
        player->pause();

    }
    else{
        ui->startButton->setText("Pause");
        player->play();
    }

    qDebug() << player->errorString();
}


void Dialog::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}

void Dialog::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
}



void Dialog::on_stopButton_clicked()
{
     player->stop();
}
