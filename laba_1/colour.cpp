
#include "colour.h"
#include "ui_colour.h"
#include <QColor>
#include <QtMath>
#include <QGridLayout>
#include <QDebug>
#include <algorithm>
#include <string>

#include <QGridLayout>
#include <QString>
#include <QDoubleValidator>
#include <QMessageBox>
#include <iostream>
#include <cmath>

colour::colour(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::colour)
{
    ui->setupUi(this);
    setWindowTitle("'Changer in RGB -> XYZ -> HLS' (LAB1)");
    setWindowIcon(QIcon(":/icon.png"));
    ui->statusbar->setStyleSheet(
        "QStatusBar {"
        "background-color: #aed3dd;"
        "color: #E6E6FA;"
        "}");

    current = new QLabel;
    current->setText("You may change any color with sliders or spinboxes OR just press auto change!");
    current->setStyleSheet("color: black;"
                           "font-size:16px;"
                           "font-family: Titillium Web;");
    ui->statusbar->addWidget(current,1);
    current->setAlignment(Qt::AlignCenter);

    currentColor.setRgb(0,0,0);
    colorDialog = new QColorDialog;
    SetColor();
    ui->col->setStyleSheet("QGraphicsView{background-color:white;border: 2px solid black;""}");

//все про слайдеры для RGB
    ui->sliderR->setRange(0,255);
    ui->sliderG->setRange(0,255);
    ui->sliderB->setRange(0,255);
    ui->sliderR->setValue(1);
    ui->sliderG ->setValue(0);
    ui->sliderB->setValue(0);
    connect(ui->sliderR, SIGNAL(sliderMoved(int)), this, SLOT(RGB_Box()));
    connect(ui->sliderG, SIGNAL(sliderMoved(int)), this, SLOT(RGB_Box()));
    connect(ui->sliderB, SIGNAL(sliderMoved(int)), this, SLOT(RGB_Box()));


//spin box для RGB

connect(ui->spinBox_R, SIGNAL(editingFinished()), this, SLOT(RGBChanger()));
connect(ui->spinBox_G, SIGNAL(editingFinished()), this, SLOT(RGBChanger()));
connect(ui->spinBox_B, SIGNAL(editingFinished()), this, SLOT(RGBChanger()));
    ui->spinBox_R->setRange(0,255);
    ui->spinBox_G->setRange(0,255);
    ui->spinBox_B->setRange(0,255);
ui->spinBox_R->setValue(0);
ui->spinBox_G ->setValue(0);
ui->spinBox_B->setValue(0);


//rgb to xyz
    ui->sliderX->setRange(0,255);
    ui->sliderY->setRange(0,255);
    ui->sliderZ->setRange(0,255);
    ui->spinBox_X->setRange(0,255);
    ui->spinBox_Y->setRange(0,255);
    ui->spinBox_Z->setRange(0,255);
    ui->sliderX->setValue(0);
    ui->sliderY ->setValue(0);
    ui->sliderZ->setValue(0);
    ui->spinBox_X->setValue(0);
    ui->spinBox_Y ->setValue(0);
    ui->spinBox_Z->setValue(0);

    connect(ui->sliderR, SIGNAL(sliderMoved(int)), this, SLOT(XYZChange()));
    connect(ui->sliderG, SIGNAL(sliderMoved(int)), this, SLOT(XYZChange()));
    connect(ui->sliderB, SIGNAL(sliderMoved(int)), this, SLOT(XYZChange()));

    connect(ui->spinBox_R, SIGNAL(editingFinished()), this, SLOT(XYZChange()));
    connect(ui->spinBox_G, SIGNAL(editingFinished()), this, SLOT(XYZChange()));
    connect(ui->spinBox_B, SIGNAL(editingFinished()), this, SLOT(XYZChange()));

//rgb to hls
    ui->sliderH->setRange(0,360);
    ui->sliderL->setRange(0,100);
    ui->sliderS->setRange(0,100);
    ui->spinBox_H->setRange(0,360);
    ui->spinBox_L->setRange(0,100);
    ui->spinBox_S->setRange(0,100);
    ui->sliderH->setValue(0);
    ui->sliderL ->setValue(0);
    ui->sliderS->setValue(0);
    ui->spinBox_H->setValue(0);
    ui->spinBox_L ->setValue(0);
    ui->spinBox_S->setValue(0);

    connect(ui->sliderR, SIGNAL(sliderMoved(int)), this, SLOT(HLSChange()));
    connect(ui->sliderG, SIGNAL(sliderMoved(int)), this, SLOT(HLSChange()));
    connect(ui->sliderB, SIGNAL(sliderMoved(int)), this, SLOT(HLSChange()));

    connect(ui->spinBox_R, SIGNAL(editingFinished()), this, SLOT(HLSChange()));
    connect(ui->spinBox_G, SIGNAL(editingFinished()), this, SLOT(HLSChange()));
    connect(ui->spinBox_B, SIGNAL(editingFinished()), this, SLOT(HLSChange()));

//slider для XYZ

    connect(ui->sliderX, SIGNAL(sliderMoved(int)), this, SLOT(XYZ_Box()));
    connect(ui->sliderY, SIGNAL(sliderMoved(int)), this, SLOT(XYZ_Box()));
    connect(ui->sliderZ, SIGNAL(sliderMoved(int)), this, SLOT(XYZ_Box()));

//spin box для XYZ

    connect(ui->spinBox_X, SIGNAL(editingFinished()), this, SLOT(XYZChanger()));
    connect(ui->spinBox_Y, SIGNAL(editingFinished()), this, SLOT(XYZChanger()));
    connect(ui->spinBox_Z, SIGNAL(editingFinished()), this, SLOT(XYZChanger()));

//все для HLS
    connect(ui->sliderH, SIGNAL(sliderMoved(int)), this, SLOT(HLS_Box()));
    connect(ui->sliderL, SIGNAL(sliderMoved(int)), this, SLOT(HLS_Box()));
    connect(ui->sliderS, SIGNAL(sliderMoved(int)), this, SLOT(HLS_Box()));

    connect(ui->spinBox_H, SIGNAL(editingFinished()), this, SLOT(HLS_Box2()));
    connect(ui->spinBox_L, SIGNAL(editingFinished()), this, SLOT(HLS_Box2()));
    connect(ui->spinBox_S, SIGNAL(editingFinished()), this, SLOT(HLS_Box2()));
}


//All for RGB
//база слайдеры и спинбоксы
void colour :: RGBChanger()
{
    qDebug() << ui->spinBox_R->value();
    r = QString::number(ui->spinBox_R -> value());

    qDebug() << ui->spinBox_G->value();
    g = QString::number(ui->spinBox_G -> value());

    qDebug() << ui->spinBox_B->value();
    b = QString::number(ui->spinBox_B -> value());

    ui->sliderR->setValue(ui->spinBox_R -> value());
    ui->sliderG->setValue(ui->spinBox_G -> value());
    ui->sliderB->setValue(ui->spinBox_B -> value());

    ui->col->setStyleSheet("QGraphicsView{background-color:rgb("+r+","+g+","+b+");border: 2px solid black;""}");
}

void colour :: RGB_Box()
{
    qDebug() << ui->sliderR->value();
    r = QString::number(ui->sliderR -> value());

    qDebug() << ui->sliderG->value();
    g = QString::number(ui->sliderG -> value());

    qDebug() << ui->sliderB->value();
    b = QString::number(ui->sliderB -> value());

    ui->spinBox_R->setValue(ui->sliderR -> value());
    ui->spinBox_G->setValue(ui->sliderG-> value());
    ui->spinBox_B->setValue(ui->sliderB -> value());
    ui->col->setStyleSheet("QGraphicsView{background-color:rgb("+r+","+g+","+b+"); border: 2px solid black;""}");
}


//перевод в XYZ из RGB
void colour :: XYZChange()
{
        double r = ui->sliderR->value() / 255.0;
        double g = ui->sliderG->value() / 255.0;
        double b = ui->sliderB->value() / 255.0;

        // Применяем обратное компандирование (companding) для r, g, b
        if (r > 0.04045)
        {
            r = pow((r + 0.055) / 1.055, 2.4);
        }
        else
        {
            r = r / 12.92;
        }

        if (g > 0.04045)
        {
            g = pow((g + 0.055) / 1.055, 2.4);
        }
        else
        {
            g = g / 12.92;
        }

        if (b > 0.04045)
        {
            b = pow((b + 0.055) / 1.055, 2.4);
        }
        else
        {
            b = b / 12.92;
        }

        // Применяем линейное преобразование для получения значений XYZ
        double x = r * 0.4124564 + g * 0.3575761 + b * 0.1804375;
        double y = r * 0.2126729 + g * 0.7151522 + b * 0.0721750;
        double z = r * 0.0193339 + g * 0.1191920 + b * 0.9503041;

        // Нормализуем значения XYZ в диапазоне от 0 до 100
        x *= 100.0;
        y *= 100.0;
        z *= 100.0;

        // Устанавливаем значения XYZ в спинбоксы
        ui->spinBox_X->setValue(int(x));
        ui->spinBox_Y->setValue(int(y));
        ui->spinBox_Z->setValue(int(z));

        ui->sliderX->setValue(int(x));
        ui->sliderY->setValue(int(y));
        ui->sliderZ->setValue(int(z));
    /*qDebug() << ui->sliderR->value();
    r = QString::number(ui->sliderR -> value());

    qDebug() << ui->sliderG->value();
    g = QString::number(ui->sliderG -> value());

    qDebug() << ui->sliderB->value();
    b = QString::number(ui->sliderB -> value());

    ui->sliderX->setValue(((ui->sliderR -> value()) * 0.412453) + ((ui->sliderG -> value()) * 0.357580) + ((ui->sliderB -> value()) * 0.180423));
    ui->sliderY->setValue(((ui->sliderR -> value()) * 0.212671) + ((ui->sliderG -> value()) * 0.715160) + ((ui->sliderB -> value()) * 0.072169));
    ui->sliderZ->setValue(((ui->sliderR -> value()) * 0.019334) + ((ui->sliderG -> value()) * 0.119193) + ((ui->sliderB -> value()) * 0.950227));
    ui->spinBox_X->setValue(((ui->sliderR -> value()) * 0.412453) + ((ui->sliderG -> value()) * 0.357580) + ((ui->sliderB -> value()) * 0.180423));
    ui->spinBox_Y->setValue(((ui->sliderR -> value()) * 0.212671) + ((ui->sliderG -> value()) * 0.715160) + ((ui->sliderB -> value()) * 0.072169));
    ui->spinBox_Z->setValue(((ui->sliderR -> value()) * 0.019334) + ((ui->sliderG -> value()) * 0.119193) + ((ui->sliderB -> value()) * 0.950227));

    ui->sliderX->setValue(((ui->spinBox_R -> value()) * 0.412453) + ((ui->spinBox_G -> value()) * 0.357580) + ((ui->spinBox_B -> value()) * 0.180423));
    ui->sliderY->setValue(((ui->spinBox_R -> value()) * 0.212671) + ((ui->spinBox_G -> value()) * 0.715160) + ((ui->spinBox_B -> value()) * 0.072169));
    ui->sliderZ->setValue(((ui->spinBox_R -> value()) * 0.019334) + ((ui->spinBox_G -> value()) * 0.119193) + ((ui->spinBox_B -> value()) * 0.950227));
    ui->spinBox_X->setValue(((ui->spinBox_R -> value()) * 0.412453) + ((ui->spinBox_G -> value()) * 0.357580) + ((ui->spinBox_B -> value()) * 0.180423));
    ui->spinBox_Y->setValue(((ui->spinBox_R -> value()) * 0.212671) + ((ui->spinBox_G -> value()) * 0.715160) + ((ui->spinBox_B -> value()) * 0.072169));
    ui->spinBox_Z->setValue(((ui->spinBox_R -> value()) * 0.019334) + ((ui->spinBox_G -> value()) * 0.119193) + ((ui->spinBox_B -> value()) * 0.950227));
*/
    //ui->col->setStyleSheet("QGraphicsView{background-color:rgb("+r+","+g+","+b+");border: 2px solid black;""}");
}

//перевод в HLS из RGB
void colour :: HLSChange()
{
    int rr = ui->sliderR->value();
    int gg = ui->sliderG->value();
    int bb = ui->sliderB->value();

    r = QString::number(ui->sliderR->value());
    g = QString::number(ui->sliderG->value());
    b = QString::number(ui->sliderB->value());

    // Создаем объект QColor с заданными значениями RGB
    QColor color(rr, gg, bb);

    // Получаем значения HLS
    int h, l, s;
    color.getHsl(&h, &l, &s);

    // Устанавливаем значения HLS в ползунки и спинбоксы
    ui->sliderH->setValue(h);
    ui->spinBox_H->setValue(h);
    ui->sliderL->setValue(l);
    ui->spinBox_L->setValue(l);
    ui->sliderS->setValue(s);
    ui->spinBox_S->setValue(s);

    ui->col->setStyleSheet("QGraphicsView{background-color:rgb("+r+","+g+","+b+");border: 2px solid black;}");

    /*qDebug() << ui->sliderR->value();
    r = QString::number(ui->sliderR -> value());

    qDebug() << ui->sliderG->value();
    g = QString::number(ui->sliderG -> value());

    qDebug() << ui->sliderB->value();
    b = QString::number(ui->sliderB -> value());

    maxy = qMax(qMax(ui->sliderR -> value(), ui->sliderB -> value()), ui->sliderG -> value());
    miny = qMin(qMin(ui->sliderR -> value(), ui->sliderB -> value()), ui->sliderG -> value());
    d = maxy - miny;
    sum = (maxy + miny) / 2;

    if(d == 0)
    {
        ui->sliderH->setValue(0);
        ui->spinBox_H->setValue(0);

        ui->sliderS->setValue(0);
        ui->spinBox_S->setValue(0);
    }
   /* else
    {
        if ( sum < 0.5 )  ui->sliderS->setValue(d / ( maxy + miny ));
                else ui->sliderS->setValue(d / ( 2 - (maxy + miny)));

                  del_R = ( ( ( var_Max - var_R ) / 6 ) + ( del_Max / 2 ) ) / d
                      del_G = ( ( ( var_Max - var_G ) / 6 ) + ( del_Max / 2 ) ) / d
                      del_B = ( ( ( var_Max - var_B ) / 6 ) + ( del_Max / 2 ) ) / d

                  if      ( var_R == var_Max ) H = del_B - del_G
                  else if ( var_G == var_Max ) H = ( 1 / 3 ) + del_R - del_B
                  else if ( var_B == var_Max ) H = ( 2 / 3 ) + del_G - del_R

                  if ( H < 0 ) H += 1
                if ( H > 1 ) H -= 1
    }*/
  /*  d = maxy - miny;
    sum = maxy + miny;

    if(d == 0)
    {
        ui->sliderH->setValue(0);
        ui->spinBox_H->setValue(0);
    }
    else{
    if(maxy == ui->spinBox_G -> value() || maxy == ui->sliderG -> value())
        ui->sliderH->setValue((60 * ((((ui->spinBox_B -> value())) - ((ui->spinBox_R -> value()))) / d))/ 255 + 120);
    if(maxy == ui->spinBox_G -> value() || maxy == ui->sliderG -> value())
        ui->spinBox_H->setValue((60 * ((((ui->spinBox_B -> value())) - ((ui->spinBox_R -> value()))) / d)) / 255 + 120);

    if(maxy == ((ui->spinBox_R -> value())))
        ui->sliderH->setValue(60 * (((((ui->spinBox_G -> value())) - ((ui->spinBox_B -> value()))) / d) % 6));
    if(maxy == ((ui->spinBox_R -> value())))
        ui->spinBox_H->setValue(60 * (((((ui->spinBox_G -> value())) - ((ui->spinBox_B -> value()))) / d) % 6));


    if(maxy == (ui->spinBox_B -> value()))
        ui->sliderH->setValue(((60 * ui->spinBox_R -> value() - 60 * ui->spinBox_G -> value()) / d)  + 240);
    if(maxy == ((ui->spinBox_B -> value())))
        ui->spinBox_H->setValue(((60 * ui->spinBox_R -> value() - 60 * ui->spinBox_G -> value()) / d)  + 240);

    }

    ui->sliderL->setValue(sum / 5.1);
    ui->spinBox_L->setValue(sum / 5.1);

    ui->spinBox_S->setValue((d / sum) * 100);
    ui->sliderS->setValue((d / sum) * 100);

    ui->col->setStyleSheet("QGraphicsView{background-color:rgb("+r+","+g+","+b+");border: 2px solid black;}");*/
}


//два бокса для базы XYZ
void colour :: XYZ_Box()
{
    ui->spinBox_X->setValue(ui->sliderX -> value());
    ui->spinBox_Y->setValue(ui->sliderY-> value());
    ui->spinBox_Z->setValue(ui->sliderZ -> value());

    RGBChange2();
}

void colour :: XYZChanger()
{
    ui->sliderX->setValue(ui->spinBox_X -> value());
    ui->sliderY->setValue(ui->spinBox_Y -> value());
    ui->sliderZ->setValue(ui->spinBox_Z -> value());

    RGBChange2();
}


//HLS спинбоксы
void colour::HLS_Box()
{
    ui->spinBox_H->setValue(ui->sliderH->value());
    ui->spinBox_L->setValue(ui->sliderL->value());
    ui->spinBox_S->setValue(ui->sliderS->value());

    int C = ui->sliderS->value() * 2 * ui->sliderL->value();
    int m = ui->sliderL->value() - C / 2;
    int X = C * (1 - abs((ui->sliderH->value() / 60) % 2 - 1));

    if (0 <= ui->sliderH->value() && ui->sliderH->value() < 60)
    {
        ui->sliderR->setValue((C + m) * 0.025);
        ui->sliderG->setValue((X + m) * 0.025);
        ui->sliderB->setValue(m * 0.025);
        ui->spinBox_R->setValue((C + m) * 0.025);
        ui->spinBox_G->setValue((X + m) * 0.025);
        ui->spinBox_B->setValue(m * 0.025);
    }
    else if (60 <= ui->sliderH->value() && ui->sliderH->value() < 120)
    {
        ui->sliderR->setValue((X + m) * 0.025);
        ui->sliderG->setValue((C + m) * 0.025);
        ui->sliderB->setValue(m * 0.025);
        ui->spinBox_R->setValue((X + m) * 0.025);
        ui->spinBox_G->setValue((C + m) * 0.025);
        ui->spinBox_B->setValue(m * 0.025);
    }
    else if (120 <= ui->sliderH->value() && ui->sliderH->value() < 180)
    {
        ui->sliderR->setValue(m * 0.025);
        ui->sliderG->setValue((C + m) * 0.025);
        ui->sliderB->setValue((X + m) * 0.025);
        ui->spinBox_R->setValue(m * 0.025);
        ui->spinBox_G->setValue((C + m) * 0.025);
        ui->spinBox_B->setValue((X + m) * 0.025);
    }
    else if (180 <= ui->sliderH->value() && ui->sliderH->value() < 240)
    {
        ui->sliderR->setValue(m * 0.025);
        ui->sliderG->setValue((X + m) * 0.025);
        ui->sliderB->setValue((C + m) * 0.025);
        ui->spinBox_R->setValue(m * 0.025);
        ui->spinBox_G->setValue((X + m) * 0.025);
        ui->spinBox_B->setValue((C + m) * 0.025);
    }
    else if (240 <= ui->sliderH->value() && ui->sliderH->value() < 300)
    {
        ui->sliderR->setValue((X + m) * 0.025);
        ui->sliderG->setValue(m * 0.025);
        ui->sliderB->setValue((C + m) * 0.025);
        ui->spinBox_R->setValue((X + m) * 0.025);
        ui->spinBox_G->setValue(m * 0.025);
        ui->spinBox_B->setValue((C + m) * 0.025);
    }
    else if (300 <= ui->sliderH->value() && ui->sliderH->value() < 360)
    {
        ui->sliderR->setValue((C + m) * 0.025);
        ui->sliderG->setValue(m * 0.025);
        ui->sliderB->setValue((X + m) * 0.025);
        ui->spinBox_R->setValue((C + m) * 0.025);
        ui->spinBox_G->setValue(m * 0.025);
        ui->spinBox_B->setValue((X + m) * 0.025);
    }

    XYZChange();
}

QColor colour::hlsToRgb(int h, int l, int s)
{
    double h_ = h / 360.0;
    double l_ = l / 255.0;
    double s_ = s / 255.0;

    double c = (1 - std::abs(2 * l_ - 1)) * s_;
    double x = c * (1 - std::abs(std::fmod(h_ * 6, 2) - 1));
    double m = l_ - c / 2;

    double r_, g_, b_;

    if (h_ >= 0 && h_ < 1 / 6.0) {
        r_ = c;
        g_ = x;
        b_ = 0;
    } else if (h_ >= 1 / 6.0 && h_ < 2 / 6.0) {
        r_ = x;
        g_ = c;
        b_ = 0;
    } else if (h_ >= 2 / 6.0 && h_ < 3 / 6.0) {
        r_ = 0;
        g_ = c;
        b_ = x;
    } else if (h_ >= 3 / 6.0 && h_ < 4 / 6.0) {
        r_ = 0;
        g_ = x;
        b_ = c;
    } else if (h_ >= 4 / 6.0 && h_ < 5 / 6.0) {
        r_ = x;
        g_ = 0;
        b_ = c;
    } else {
        r_ = c;
        g_ = 0;
        b_ = x;
    }

    int r = static_cast<int>((r_ + m) * 255.0);
    int g = static_cast<int>((g_ + m) * 255.0);
    int b = static_cast<int>((b_ + m) * 255.0);

    return QColor(r, g, b);
}

//HLS слайдеры
void colour :: HLS_Box2()
{
    qDebug() << ui->sliderH->value();
    h = QString::number(ui->sliderH -> value());

    qDebug() << ui->sliderL->value();
    l = QString::number(ui->sliderL -> value());

    qDebug() << ui->sliderS->value();
    s = QString::number(ui->sliderS -> value());

    ui->sliderH->setValue(ui->spinBox_H -> value());
    ui->sliderL->setValue(ui->spinBox_L-> value());
    ui->sliderS->setValue(ui->spinBox_S -> value());

    int h = ui->sliderH->value(); // Оттенок (0-360)
    int l = ui->sliderL->value(); // Светлота (0-255)
    int s = ui->sliderS->value(); // Насыщенность (0-255)

    QColor rgbColor = hlsToRgb(h, l, s);

    ui->sliderR->setValue(rgbColor.red());
    ui->sliderG->setValue(rgbColor.green());
    ui->sliderB->setValue(rgbColor.blue());

    ui->spinBox_R->setValue(rgbColor.red());
    ui->spinBox_G->setValue(rgbColor.green());
    ui->spinBox_B->setValue(rgbColor.blue());

    r = QString::number(ui->sliderR->value());
    g = QString::number(ui->sliderG->value());
    b = QString::number(ui->sliderB->value());

    RGB_Box();
    //RGBChanger();
    /*int C = ((ui->spinBox_S -> value()) * 2 * (ui->spinBox_L -> value()));
    int m = (ui->spinBox_L -> value()) + (C / 2);
    int X = C * (((ui->spinBox_H -> value())) % 2);

    if(0 <= ui->sliderH -> value() && (ui->sliderH -> value()) < 60)
    {
    ui->sliderR->setValue((C + m) * 0.025);
    ui->sliderG->setValue((X * 42.5) + (m * 0.025));
    ui->sliderB->setValue(m * 0.025);
    ui->spinBox_R->setValue((C + m) * 0.025);
    ui->spinBox_G->setValue((X * 42.5) + (m * 0.025));
    ui->spinBox_B->setValue(m * 0.025);
    }
    else if(60 <= ui->sliderH -> value() && (ui->sliderH -> value()) < 120)
    {
    ui->sliderR->setValue((X * 42.5) + (m * 0.025));
    ui->sliderG->setValue((C + m) * 0.025);
    ui->sliderB->setValue(m * 0.025);
    ui->spinBox_R->setValue((X * 42.5) + (m * 0.025));
    ui->spinBox_G->setValue((C + m) * 0.025);
    ui->spinBox_B->setValue(m * 0.025);
    }
    else if(120 <= ui->sliderH -> value() && (ui->sliderH -> value()) < 180)
    {
    ui->sliderR->setValue(m * 0.025);
    ui->sliderG->setValue((C + m) * 0.025);
    ui->sliderB->setValue((X * 42.5) + (m * 0.025));
    ui->spinBox_R->setValue(m * 0.025);
    ui->spinBox_G->setValue((C + m) * 0.025);
    ui->spinBox_B->setValue((X * 42.5) + (m * 0.025));
    }
    else if(180 <= ui->sliderH -> value() && (ui->sliderH -> value()) < 240)
    {
    ui->sliderR->setValue(m * 0.025);
    ui->sliderG->setValue((X * 42.5) + (m * 0.025));
    ui->sliderB->setValue((C + m) * 0.025);
    ui->spinBox_R->setValue(m * 0.025);
    ui->spinBox_G->setValue((X * 42.5) + (m * 0.025));
    ui->spinBox_B->setValue((C + m) * 0.025);
    }
    else if(240 <= ui->sliderH -> value() && (ui->sliderH -> value()) < 300)
    {
    ui->sliderR->setValue((X * 42.5) + (m * 0.025));
    ui->sliderG->setValue(m * 0.025);
    ui->sliderB->setValue((C + m) * 0.025);
    ui->spinBox_R->setValue((X * 42.5) + (m * 0.025));
    ui->spinBox_G->setValue(m * 0.025);
    ui->spinBox_B->setValue((C + m) * 0.025);
    }
    else if(300 <= ui->sliderH -> value() && (ui->sliderH -> value()) < 360)
    {
    ui->sliderR->setValue((C + m) * 0.025);
    ui->sliderG->setValue((m) * 0.025);
    ui->sliderB->setValue((X * 42.5) + (m * 0.025));
    ui->spinBox_R->setValue((C + m) * 0.025);
    ui->spinBox_G->setValue(m * 0.025);
    ui->spinBox_B->setValue((X * 42.5) + (m * 0.025));
    }

    XYZChange();*/
}

//кнопка автоматичсекого выбора
void colour::on_pushButton_clicked()
{
    currentColor = colorDialog->getColor();
    ui->sliderR->setValue(currentColor.red());
    ui->sliderG->setValue(currentColor.green());
    ui->sliderB->setValue(currentColor.blue());
    ui->sliderX->setValue(currentColor.red() * 0.412453 + currentColor.green() * 0.357880 + currentColor.blue() * 0.180423);
    ui->sliderY->setValue(currentColor.red() * 0.212671 + currentColor.green() * 0.715160 + currentColor.blue() * 0.072169);
    ui->sliderZ->setValue(currentColor.red() * 0.019334 + currentColor.green() * 0.119193 + currentColor.blue() * 0.950227);
    ui->sliderH->setValue(currentColor.hue());
    ui->sliderS->setValue(currentColor.hslSaturation() * 0.4);
    ui->sliderL->setValue(currentColor.lightness() * 0.4);


    ui->spinBox_R->setValue(currentColor.red());
    ui->spinBox_G->setValue(currentColor.green());
    ui->spinBox_B->setValue(currentColor.blue());
    ui->spinBox_X->setValue(currentColor.red() * 0.412453 + currentColor.green() * 0.357880 + currentColor.blue() * 0.180423);
    ui->spinBox_Y->setValue(currentColor.red() * 0.212671 + currentColor.green() * 0.715160 + currentColor.blue() * 0.072169);
    ui->spinBox_Z->setValue(currentColor.red() * 0.019334 + currentColor.green() * 0.119193 + currentColor.blue() * 0.950227);
    ui->spinBox_H->setValue(currentColor.hue());
    ui->spinBox_S->setValue(currentColor.hslSaturation() * 0.4);
    ui->spinBox_L->setValue(currentColor.lightness() * 0.4);

    SetColor();
}

//цвет
void colour:: SetColor()
{
    QString rv = QString::number(ui->sliderR->value());
    QString gv = QString::number(ui->sliderG->value());
    QString bv = QString::number(ui->sliderB->value());
    ui->col->setStyleSheet("QWidget{""background-color:rgb("+rv+","+gv+","+bv+"); border: 2px solid black;""}");
}

colour::~colour()
{
    delete ui;
}


//перевод в rgb из xyz
void colour :: RGBChange2(){
    double rFloat = (ui->spinBox_X -> value()) * 3.2406 + (ui->spinBox_Y -> value()) * -1.5372 + (ui->spinBox_Y -> value()) * -0.4986;
    double gFloat = (ui->spinBox_X -> value()) * -0.9689 + (ui->spinBox_Y -> value()) * 1.8758 + (ui->spinBox_Y -> value()) * 0.0415;
    double bFloat = (ui->spinBox_X -> value()) * 0.0557 + (ui->spinBox_Y -> value()) * -0.2040 + (ui->spinBox_Y -> value()) * 1.0570;

    bFloat /= 100;
    gFloat /= 100;
    rFloat /= 100;

    if(rFloat>=0.0031308){
    rFloat = qPow(rFloat, 1/2.4)*1.055 - 0.055;
    }else{
    rFloat *=12.92;
    }
    if(gFloat>=0.0031308){
    gFloat = pow(gFloat, 1/2.4)*1.055 - 0.055;
    }else{
    gFloat *=12.92;
    }
    if(bFloat>=0.0031308){
    bFloat = pow(bFloat, 1/2.4)*1.055 - 0.055;
    }else{
    bFloat *=12.92;
    }

    bFloat *= 255;
    gFloat *= 255;
    rFloat *= 255;

    if(gFloat < 0) gFloat = 0;
    if(gFloat > 255) gFloat = 255;
    if(bFloat < 0) bFloat = 0;
    if(bFloat > 255) bFloat = 255;
    if(rFloat < 0) rFloat = 0;
    if(rFloat > 255) rFloat = 255;
    int rr = (int)rFloat;
    int gg = (int)gFloat;
    int bb = (int)bFloat;

    ui->sliderR->setValue(rr);
    ui->sliderG->setValue(gg);
    ui->sliderB->setValue(bb);
    ui->spinBox_R->setValue(rr);
    ui->spinBox_G->setValue(gg);
    ui->spinBox_B->setValue(bb);

    qDebug() << ui->sliderR->value();
    x = QString::number(ui->sliderR -> value());

    qDebug() << ui->sliderG->value();
    y = QString::number(ui->sliderG -> value());

    qDebug() << ui->sliderB->value();
    z = QString::number(ui->sliderB -> value());

    HLSChange();
}

