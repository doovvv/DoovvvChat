#include "timerbtn.h"
#include <QMouseEvent>


TimerBtn::TimerBtn(QWidget *parent):QPushButton(parent),_count(10)
{
    _timer = new QTimer(this);
    connect(_timer,&QTimer::timeout,[this](){
        _count--;
        if(_count <= 0){
            _timer->stop();
            _count = 10;
            this->setText("获取");
            return;
        }
        this->setText(QString::number(_count));
    });
}

TimerBtn::~TimerBtn()
{
    _timer->stop();
}

void TimerBtn::mouseReleaseEvent(QMouseEvent *e)

{   if(e->button() == Qt::LeftButton){
        this->setEnabled(false);
        this->setText(QString::number(_count));
        _timer->start(1000);
    }
    QPushButton::mouseMoveEvent(e);
    return;
}
