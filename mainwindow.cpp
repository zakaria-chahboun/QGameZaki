#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QColorDialog>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include <QBrush>
#include <QTimer>
#include <QSound>
#include <QPen>

#define MyApp "TIME OUT"
#define MyOrg "ZAKI PRO"

int i = 0;

/* Zakaria Chahoun 27/05/2018 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Init Setting
    QSettings settings(MyApp, MyOrg);
    this->color.setNamedColor(settings.value("COLOR","#f93592").toString());

    // Init factor :)
    factor = 5760/ui->spinBox->value();

    // Tools :p
    elp = new QGraphicsEllipseItem(nullptr);
    timer = new QTimer(this);

    // Decorations
    //QPen pen(Qt::green, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    //pen.setColor(QColor("#f8298b"));

    // Properties
    elp->setRect(0,0,500,500);
    elp->setPen(Qt::NoPen);
    elp->setBrush(QBrush(this->color));

    // Graphics view
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addItem(elp);
    ui->graphicsView->setScene(scene);

    // Timer :)
    connect(timer,&QTimer::timeout,[&](){
        if(counter<=5760/factor){
           elp->setSpanAngle(counter*factor);
           ui->timelabel->setText("<span style='font-size:30pt;'>"+QString::number(counter)+"</span>");
           // you have just 5 secs, go go! :p
           if(ui->spinBox->value() < counter+10 && ui->spinBox->value()>=10){
               QSound::play(":/Res/SECONDS.wav");
               elp->setBrush(QBrush(QColor("red")));
           }
           qDebug() << counter*factor << counter;
           counter++;

        }else{
            timer->stop();
            counter = 1; // reset
            ui->spinBox->setEnabled(true);
            ui->start->setText("إبدأ");
            ui->start->setChecked(false);
            QSound::play(":/Res/SECONDS END.wav");
            elp->setBrush(QBrush(this->color));
        }
    });

    // just ...
    QString text =
     "<b style='color:red;'>Astrolabe Group</b> | "
     "<b style='color:red;'>مجموعة أسطرلاب التعليمية الشبابية</b> | "
     "<b>AstrolabeGroup@Gmail.com</b>";

    QLabel *lab = new QLabel(text,this);
    ui->statusBar->addWidget(lab);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete elp;
    delete timer;
}

// Change factor value by : spinbox changed event
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    //elp->setStartAngle(arg1*10);// 5760 = closed circle
    factor = 5760/arg1;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    auto h =  ui->graphicsView->height();
    elp->setRect(0,0,h-20,h-20);
}

// On click : start/stop
void MainWindow::on_start_clicked(bool checked)
{
    if(checked){
        ui->start->setText("قف");
        ui->spinBox->setEnabled(false);
        timer->start(1000);

    }else{
        counter = 1; // reset
        ui->start->setText("إبدأ");
        ui->spinBox->setEnabled(true);
        timer->stop();
        elp->setSpanAngle(6000*factor);
        ui->timelabel->setText("<span style='font-size:30pt;'>0</span>");
    }
}

// About
void MainWindow::on_actionCreator_triggered()
{
    QMessageBox::about(this,"About Creator",
                       "This application is created by <b>Zakaria Chahboun</b>"
                       "<br>27/05/2017<br>"
                       "<br><b>Contact:</b><br>"
                       "Gmail: Zakaria.Chahboun.1996@Gmail.Com<br>"
                       "Twitter: @Zaki_Chahboun<br>"
                       "Facebook: Zakaria.Chahboun.2018<br>"
                       "Tel: +212 678807280 / +212 680982106<br>"
                       "<br><b>All rights reserved</b><br>"
                       "<img src=':/Res/ZAKI PRO - PNG.PNG'/>");
}

// Change Color : Circle :)
void MainWindow::on_actionColor_triggered()
{
    auto tcolor = QColorDialog::getColor(this->color,this,"إختر اللون المفضل",QColorDialog::DontUseNativeDialog);

    if(tcolor == QColor::Invalid)
        return;

    // set color
    elp->setBrush(QBrush(tcolor));

    // and save it
    QSettings settings(MyApp, MyOrg);
    settings.setValue("COLOR",tcolor.name());
    this->color = tcolor;
}
