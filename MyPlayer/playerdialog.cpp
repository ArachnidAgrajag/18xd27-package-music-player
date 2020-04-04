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
    repeat=false;
    //curQueue = new musicQueueSpecial;
}


PlayerDialog::~PlayerDialog()
{
    delete ui;
    delete player;
    //delete curQueue;
}

void PlayerDialog::load_playingQueue(musicQueueSpecial mQueue)
{
    curQueue=mQueue;
    curQueue.playNext(&previous,&playingNow);
    displayCurQueue();
    previous.display();
    load_music(playingNow,true);
}

void PlayerDialog::load_allSongs(musicQueueSpecial mQueue)
{
    allSongs=mQueue;
    displayAllSongs();
    load_playingQueue(allSongs);
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
        if(!repeat)
            ui->previousButton->setDisabled(true);
    }
    else {
        ui->previousButton->setDisabled(false);
    }

    if(curQueue.count()==0){
        if(!repeat)
            ui->nextButton->setDisabled(true);
    }
    else {
        ui->nextButton->setDisabled(false);
    }

    if(!(curQueue.count()==0&&previous.count()==0)){
        ui->resetButton->setDisabled(false);
        ui->shuffleButton->setDisabled(false);
        ui->repeatCheckBox->setDisabled(false);
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
    if(previous.count()==1 && repeat){
        int n = curQueue.count();
        for(int i= 0;i<n;i++){
            curQueue.playNext(&previous,&playingNow);
        }

        load_music(playingNow,false);
    }
    else{
        curQueue.playPrev(&previous,&playingNow);
        load_music(playingNow,false);
    }
}

void PlayerDialog::on_nextButton_clicked()
{
    if(curQueue.count()==0 && repeat){
        curQueue.reset(&previous,&playingNow);
        load_music(playingNow,false);
    }
    else{
    curQueue.playNext(&previous, &playingNow);
    load_music(playingNow,false);
    }

}

void PlayerDialog::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status==7){
        if(curQueue.count()!=0){
            curQueue.playNext(&previous, &playingNow);
            load_music(playingNow,false);
        }
        else{
            if(repeat){
                curQueue.reset(&previous,&playingNow);
                load_music(playingNow,false);
            }
            if(!repeat){
                player->stop();
                ui->startButton->setChecked(true);
                ui->startButton->setText("Play");
            }
        }
    }
}

void PlayerDialog::on_clearQueueButton_clicked()
{
    int n = curQueue.count();
    for(int i=0;i<n;i++){
        curQueue.dequeue();
    }
    n=previous.count();
    for(int i=0;i<n;i++){
        previous.dequeue();
    }
    displayCurQueue();
    ui->nextButton->setDisabled(true);
    ui->previousButton->setDisabled(true);
    ui->resetButton->setDisabled(true);
    ui->shuffleButton->setDisabled(true);
    ui->repeatCheckBox->setDisabled(true);
}

void PlayerDialog::on_curSongItemDoubleClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();
    curQueue.jumpTill(index,&previous,&playingNow);
    load_music(playingNow,false);
}

void PlayerDialog::on_prevSongItemDoubleClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();
    curQueue.jumpBack(index,&previous,&playingNow);
    load_music(playingNow,false);
}

void PlayerDialog::displayCurQueue()
{

    ui->curSongsList->clear();
    ui->playedSongList->clear();
    int n = curQueue.count();
    for(int i=0;i<n;i++){
        QListWidgetItem * newItem=  new QListWidgetItem;
        newItem->setText(curQueue.get_mFile(i).get_title());
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

void PlayerDialog::displayAllSongs()
{
    int n = allSongs.count();
    for(int i=0;i<n;i++){
        QListWidgetItem * newItem=  new QListWidgetItem;
        newItem->setText(allSongs.get_mFile(i).get_title());
        newItem->setData(Qt::UserRole, i);
        ui->allSongsList->addItem(newItem);
    }
}


void PlayerDialog::on_repeatCheckBox_stateChanged(int arg1)
{
   if (arg1==0){
       repeat=false;
       if(curQueue.count()==0)
           ui->nextButton->setDisabled(true);
       if(previous.count()==1)
           ui->previousButton->setDisabled(true);
   }
   else if (arg1==2){//checked state
       repeat=true;
       ui->nextButton->setEnabled(true);
       ui->previousButton->setEnabled(true);
   }
}

void PlayerDialog::on_resetButton_clicked()
{
    curQueue.reset(&previous,&playingNow);
    load_music(playingNow,false);
}

void PlayerDialog::on_shuffleButton_clicked()
{
    curQueue.shuffle(&previous,&playingNow);
    load_music(playingNow,false);
}

void PlayerDialog::on_clearSelButton_clicked()
{
    ui->allSongsList->clearSelection();
}

void PlayerDialog::on_addToQueueButton_clicked()
{
    foreach (QListWidgetItem* item, ui->allSongsList->selectedItems()){
        curQueue.enqueue(allSongs.get_mFile((item->data(Qt::UserRole).toInt())).get_fileLoc());
    }
    displayCurQueue();
}

void PlayerDialog::on_newQueueButton_clicked()
{
    int n = curQueue.count();
    for(int i=0;i<n;i++){
        curQueue.dequeue();
    }
    foreach (QListWidgetItem* item, ui->allSongsList->selectedItems()){
        curQueue.enqueue(allSongs.get_mFile((item->data(Qt::UserRole).toInt())).get_fileLoc());
    }
    displayCurQueue();
}
