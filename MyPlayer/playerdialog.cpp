#include "playerdialog.h"
#include "ui_dialog.h"
#include "songTags.h"
const char file [] ="/home/saikrishna/Downloads/random stuff/Chumma Kizhi-Masstamilan.in.mp3";

PlayerDialog::PlayerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerDialog)
{
 ui->setupUi(this);

    player = new QMediaPlayer(this);

    connect(player, &QMediaPlayer::positionChanged, this, &PlayerDialog::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &PlayerDialog::on_durationChanged);
    player->setMedia(QUrl::fromLocalFile(file));
    readTags(file);

}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}


void PlayerDialog::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(position);
}

void PlayerDialog::on_startButton_clicked()
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


void PlayerDialog::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
    std::cout<<"position"<<position<<std::endl;
    ui->elapsedTime->setText(msToTime(position));

}

void PlayerDialog::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
    ui->totalTime->setText(msToTime(position));
}



void PlayerDialog::on_stopButton_clicked()
{
    player->stop();
    ui->startButton->setChecked(true);
    ui->startButton->setText("Play");

}

QString msToTime(qint64 msTime){
    qint64 minTime = msTime / 60000;
    msTime = msTime - (60000*minTime);
    qint64 secTime = msTime/1000;
    QString Time = ((minTime<10)?"0":"")+QString::number(minTime) +((secTime<10)?":0":":")+QString::number(secTime);
    return Time;

}

