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
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &PlayerDialog::on_mediaStatusChanged);
    connect(ui->curSongsList,&QListWidget::itemDoubleClicked,this, &PlayerDialog::on_curSongItemDoubleClicked);
    connect(ui->playedSongList,&QListWidget::itemDoubleClicked,this, &PlayerDialog::on_prevSongItemDoubleClicked);

}


PlayerDialog::~PlayerDialog()
{
    delete ui;
}

void PlayerDialog::load_playingQueue(musicQueueSpecial *mQueue)
{
    curQueue=mQueue;
    curQueue->playNext(&previous,&playingNow);
    displayCurQueue();
    previous.display();
    load_music(playingNow,true);
}


void PlayerDialog::load_music(musicFile mFile, bool firstPlay){
    player->setMedia(QUrl::fromLocalFile(mFile.get_fileLoc()));
    ui->Album->setText("Album : "+mFile.get_album());
    ui->Album->adjustSize();
    ui->Title->setText("Track : "+mFile.get_title());
    ui->Title->adjustSize();
    ui->Artist->setText("Artist : "+mFile.get_artist());
    ui->Artist->adjustSize();
    ui->coverImg->setPixmap(QPixmap::fromImage( mFile.get_coverArt()));
    ui->coverImg->adjustSize();
    if(!firstPlay){
        ui->startButton->setText("Pause");
        ui->startButton->setChecked(false);
        player->play();
    }
    if(previous.count()==1){
        ui->previousButton->setDisabled(true);
    }
    else {
        ui->previousButton->setDisabled(false);
    }

    if(curQueue->count()==0){
        ui->nextButton->setDisabled(true);
    }
    else {
        ui->nextButton->setDisabled(false);
    }

    displayCurQueue();

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


void PlayerDialog::on_previousButton_clicked()
{
    curQueue->playPrev(&previous,&playingNow);
    load_music(playingNow,false);

}

void PlayerDialog::on_nextButton_clicked()
{
    curQueue->playNext(&previous, &playingNow);
    load_music(playingNow,false);
}

void PlayerDialog::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status==7){
        curQueue->playNext(&previous, &playingNow);
        load_music(playingNow,false);
    }
}

void PlayerDialog::on_clearQueueButton_clicked()
{
    int n = curQueue->count();
    for(int i=0;i<n;i++){
        curQueue->dequeue();
    }
    n=previous.count();
    for(int i=0;i<n;i++){
        previous.dequeue();
    }
    displayCurQueue();
    ui->nextButton->setDisabled(true);
    ui->previousButton->setDisabled(true);
}

void PlayerDialog::on_curSongItemDoubleClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();
    curQueue->jumpTill(index,&previous,&playingNow);
    load_music(playingNow,false);
}

void PlayerDialog::on_prevSongItemDoubleClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();
    curQueue->jumpBack(index,&previous,&playingNow);
    load_music(playingNow,false);
}

void PlayerDialog::displayCurQueue()
{

    ui->curSongsList->clear();
    ui->playedSongList->clear();
    int n = curQueue->count();
    for(int i=0;i<n;i++){
        QListWidgetItem * newItem=  new QListWidgetItem;
        newItem->setText(curQueue->get_mFile(i).get_title());
        newItem->setData(Qt::UserRole, i);
        ui->curSongsList->addItem(newItem);
    }
    n= previous.count();
    for(int i=0;i<n;i++){
        QListWidgetItem * newItem=  new QListWidgetItem;
        newItem->setText(previous.get_mFile(i).get_title());
        newItem->setData(Qt::UserRole, i);
        ui->playedSongList->addItem(newItem);
    }
}
