
#ifndef COLOUR_H
#define COLOUR_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include <QColor>
#include <QString>
#include <QColorDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class colour; }
QT_END_NAMESPACE

class colour : public QMainWindow

{
    Q_OBJECT

        QLabel* current;

//ALL FOR RGB
    QString r;
    QString g;
    QString b;
    int maxy;
    int miny;
    int d;
    int sum;
 //ALL FOR XYZ
    QString x;
    QString y;
    QString z;


    QString h;
    QString l;
    QString s;

    double rFloat;

public:
    colour(QWidget *parent = nullptr);
    QColorDialog* colorDialog;
    QColor currentColor;
    void SetColor();
    ~colour();

private:
    Ui::colour *ui;

public slots:
    void RGBChanger();
    void RGB_Box();
    void XYZChange();
    void HLSChange();

    void XYZ_Box();
    void XYZChanger();
    void RGBChange2();


    //QColor rgbColor;
    QColor hlsToRgb(int h, int l, int s);

    void HLS_Box();
        void HLS_Box2();
    void on_pushButton_clicked();

};

#endif // COLOUR_H
