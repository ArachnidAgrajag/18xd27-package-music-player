#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerDialog; }
QT_END_NAMESPACE

class PlayerDialog : public QDialog
{
    Q_OBJECT

public:
    PlayerDialog(QWidget *parent = nullptr);
    ~PlayerDialog();

private slots:
    void on_sliderProgress_sliderMoved(int position);

    void on_startButton_clicked();

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void on_stopButton_clicked();

private:
    Ui::PlayerDialog *ui;
    QMediaPlayer * player;
};

QString msToTime(qint64 msTime);
#endif // DIALOG_H
