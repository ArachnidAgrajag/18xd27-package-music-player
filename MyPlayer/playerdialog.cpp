#include "playerdialog.h"
#include "ui_dialog.h"



PlayerDialog::PlayerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerDialog)
{
 ui->setupUi(this);

    player = new QMediaPlayer(this);
    connect(player, &QMediaPlayer::positionChanged, this, &PlayerDialog::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &PlayerDialog::on_durationChanged);
}


PlayerDialog::~PlayerDialog()
{
    delete ui;
}


void PlayerDialog::load_music(musicFile *mFile){
    player->setMedia(QUrl::fromLocalFile(mFile->get_fileLoc()));
    ui->Album->setText("Album : "+mFile->get_album());
    ui->Album->adjustSize();
    ui->Title->setText("Track : "+mFile->get_title());
    ui->Title->adjustSize();
    ui->Artist->setText("Artist : "+mFile->get_artist());
    ui->Artist->adjustSize();
    ui->coverImg->setPixmap(QPixmap::fromImage( mFile->get_coverArt()));
    ui->coverImg->adjustSize();
}

void PlayerDialog::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(position);
}

void PlayerDialog::on_startButton_clicked()
{
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

