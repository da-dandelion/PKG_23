#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <iostream>
#include <QPainter>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //l->addWidget(p,0,0,12,1);
    QGridLayout* l = new QGridLayout;
    QPushButton* pbSutherland = new QPushButton;
    pbSutherland->setText("Sutherland-Cohen Algorythm");
    QPushButton* pbCirus = new QPushButton;
    pbCirus->setText("Cirus-Beck Algorythm");

    l->addWidget(pbSutherland, 0, 0);
    l->addWidget(pbCirus, 1, 0);

    // Установить выравнивание содержимого ячеек по центру
    l->setAlignment(Qt::AlignCenter);

    ui->Sutherlandwidget->setLayout(l);
    pbSutherland->setFixedSize(200, 40);
    pbCirus->setFixedSize(200, 40);
    l->addWidget(pbSutherland,0,1,1,1);
    l->addWidget(pbCirus,1,1,1,1);
    ui->Sutherlandwidget->setLayout(l);
    connect(pbSutherland, SIGNAL(clicked()), this, SLOT(showSutherland()));
    connect(pbCirus, SIGNAL(clicked()), this, SLOT(showCirus()));

}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15;

    // Изменение масштабного коэффициента
    scaleFactor *= std::pow(1.2, numSteps);

    // Ограничение масштабного коэффициента
    scaleFactor = std::max(1.0, std::min(scaleFactor, 20.0));

    // Перерисовка окна с новым масштабом
    update();

    event->accept(); // Принять обработку события колесика мыши
}

MainWindow::~MainWindow()
{
    delete ui;
}

