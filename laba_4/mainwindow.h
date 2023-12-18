#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void drawNextAlgorithm();
    void drawPrevAlgorithm();

private:
    int currentAlgorithm;
    qreal scaleFactor;
    qint64 nanoSeconds;
    int gridSize = 25;
    int originalWidth = 800;
    int originalHeight = 500;
    int centerX;
    int centerY;
    int width;

   // QPainter painter;

    bool isMousePressed; // Флаг, указывающий, нажата ли кнопка мыши
    QPoint lastPos; // Последние координаты мыши
    int offsetX = 0;
    int offsetY = 0;

    QLabel *timeLabel;
    QLabel *x_Label;
    QLabel *y_Label;
    QLabel *basic_info;
    QLabel *sec;
    QLabel *names;

    void drawStepByStepLine(QPainter &painter);
    void drawDDALine(QPainter &painter);
    void drawBresenhamLine(QPainter &painter);
    void drawBresenhamCircle(QPainter &painter);
        void drawBresenhamCircle2(QPainter &painter);
    void drawSmoothedPoints(QPainter &painter, int centerX, int centerY, int x, int y);

    bool isFullScreen;
};

#endif // MAINWINDOW_H
