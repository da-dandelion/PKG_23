
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <QPainter>
#include <QPainterPath>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentAlgorithm(0)
{
    QWidget::setFixedSize(800, 500);

    QPushButton *algorithmButton = new QPushButton("Next Algorithm", this);
    connect(algorithmButton, &QPushButton::clicked, this, &MainWindow::drawNextAlgorithm);

    nanoSeconds = 0;

    QPushButton *rect_1 = new QPushButton(" ", this);
    rect_1->setGeometry(250, 450, 300, 25);
    rect_1->show();

    QPushButton *rect_2 = new QPushButton(" ", this);
    rect_2->setGeometry(0, 0, 210, 50);
    rect_2->setStyleSheet("text-align: center;");
    rect_2->show();

    QString values = "Time: ";
    timeLabel = new QLabel(values, this);
    timeLabel->setGeometry(10, 20, 200, 35);
    QFont font("Bookman Old Style", 10);
    timeLabel->setFont(font);
    timeLabel->show();

    setGeometry(100, 100, 800, 500);
    algorithmButton->setGeometry(10, 470, 150, 25);
    algorithmButton->show();

    QPushButton *prevAlgorithmButton = new QPushButton("Previous Algorithm", this);
    connect(prevAlgorithmButton, &QPushButton::clicked, this, &MainWindow::drawPrevAlgorithm); // Подключаем кнопку к новому слоту
    prevAlgorithmButton->setGeometry(10, 440, 150, 25);
    prevAlgorithmButton->show();

    /*QRect rectangle(250, 450, 300, 25);
    painter.drawRect(rectangle);
    painter.fillRect(rectangle, Qt::lightGray);
    QRect textRect = rectangle;
    textRect.adjust(0, 0, -1, -1);

    painter.drawRect(0, 0, 200, 50);
    painter.fillRect(0, 0, 200, 50, Qt::lightGray);*/

    // Подписи к осям
    x_Label = new QLabel("X: ", this);
    y_Label = new QLabel("Y: ", this);
    x_Label->setGeometry(405, 5, 20, 20);
    y_Label->setGeometry(780, 250, 20, 20);
    QFont font_2("Arial", 12); // Пример: шрифт Arial, размер 12

    // Установка созданного шрифта для QLabel
    x_Label->setFont(font_2);
    y_Label->setFont(font_2);
    x_Label->show();
    y_Label->show();

    basic_info = new QLabel(" ", this);
    sec = new QLabel(" ", this);
    names = new QLabel(" ", this);


}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isMousePressed = true;
        lastPos = event->pos();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    // Обработка перемещения сетки и графика уже осуществляется в paintEvent
   /* if (isMousePressed) {
        // Вычисляем смещение по осям X и Y
        offsetX = event->pos().x() - lastPos.x();
        offsetY = event->pos().y() - lastPos.y();

        //painter.translate(offsetX, offsetY);
        // Обновляем lastPos для следующего события мыши
        lastPos = event->pos();

        // Перерисовываем виджет
        update();
        event->accept();*/
    if (event->buttons() & Qt::LeftButton) {
        // Вычисляем смещение мыши
        QPoint offset = event->pos() - lastPos;

        // Обновляем смещение
        offsetX += offset.x();
        offsetY += offset.y();

        // Запоминаем текущие координаты мыши
        lastPos = event->pos();

        // Перерисовываем окно
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isMousePressed = false;
    }
}

MainWindow::~MainWindow() {}

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

/*void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);

    int width = 800;
    int height = 500;

    int centerX = originalWidth / 2;
    int centerY = originalHeight / 2;

    painter.setPen(Qt::black);

    // Оси координат
    painter.setPen(QPen(Qt::white, 6)); // Более толстая линия для осей
    painter.drawLine(0, centerY, width, centerY); // Горизонтальная ось X
    painter.drawLine(centerX, 0, centerX, height); // Вертикальная ось Y

    // Линии сетки
    int gridSize = 25; // Размер сетки
    painter.setPen(QPen(Qt::darkGray, 1, Qt::SolidLine)); // Стиль линии сетки

    for (int i = centerX % gridSize; i <= width; i += gridSize) {
        painter.drawLine(i, 0, i, height); // Вертикальные линии сетки
    }

    for (int i = centerY % gridSize; i <= height; i += gridSize) {
        painter.drawLine(0, i, width, i); // Горизонтальные линии сетки
    }

    // Подписи к осям
    painter.drawText(centerX + 5, 20, "X");
    painter.drawText(width - 20, centerY - 5, "Y");

    //подписи названиям выолняемого прямо сейчас алгоритма
    QRect rectangle(250, 450, 300, 25);
    painter.drawRect(rectangle);
    painter.fillRect(rectangle, Qt::lightGray);
    QRect textRect = rectangle;
    textRect.adjust(0, 0, -1, -1);

        painter.drawRect(0, 0, 200, 50);
        painter.fillRect(0, 0, 200, 50, Qt::lightGray);

        QFont font;

    // Выбор и вызов метода для отрисовки на основе значения currentAlgorithm
    switch (currentAlgorithm) {
    case 0:
        drawStepByStepLine(painter);
        // Установка выравнивания текста по центру
        font.setPointSize(12);
        painter.setFont(font);
        painter.drawText(textRect, Qt::AlignCenter, "Пошаговый алгоритм");
        break;
    case 1:
        drawDDALine(painter);
        font.setPointSize(12);
        painter.setFont(font);
        // Установка выравнивания текста по центру
        painter.drawText(textRect, Qt::AlignCenter, "Алгоритм ЦДА");
        break;
    case 2:
        drawBresenhamLine(painter);
        font.setPointSize(12);
        painter.setFont(font);
        painter.drawText(textRect, Qt::AlignCenter, "Алгоритм Брезенхема (линия)");
        break;
    case 3:
        drawBresenhamCircle(painter);
        font.setPointSize(12);
        painter.setFont(font);
        painter.drawText(textRect, Qt::AlignCenter, "Алгоритм Брезенхема (окружность)");
        break;
  /*  case 4:
        drawBresenhamCircle2(painter);
        font.setPointSize(12);
        painter.setFont(font);
        painter.drawText(textRect, Qt::AlignCenter, "Алгоритм Брезенхема 2 (сглаживание)");
        break;
    default:
        break;
    }

    // Вывод времени выполнения алгоритма на экран
    QString timeStr = "Time: " + QString::number(nanoSeconds) + " nanoseconds";
    timeLabel->setText(timeStr);
}
*/

void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    /*QRect rectangle(250, 450, 300, 25);
    painter.drawRect(rectangle);
    painter.fillRect(rectangle, Qt::lightGray);
    QRect textRect = rectangle;
    textRect.adjust(0, 0, -1, -1);

    painter.drawRect(0, 0, 200, 50);
    painter.fillRect(0, 0, 200, 50, Qt::lightGray);*/

    int width = 800;
    int height = 500;

    int centerX = width / 2;
    int centerY = height / 2;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

            painter.translate(offsetX, offsetY);
    // Масштабирование координат и размеров элементов
    painter.scale(scaleFactor, scaleFactor);
    painter.translate((1 / scaleFactor - 1) * width / 2, (1 / scaleFactor - 1) * height / 2);

    // Оси координат
    painter.setPen(QPen(Qt::white, 6)); // Более толстая линия для осей
    painter.drawLine(0, centerY, width, centerY); // Горизонтальная ось X
    painter.drawLine(centerX, 0, centerX, height); // Вертикальная ось Y

    // Линии сетки
    int gridSize = 25; // Размер сетки
    painter.setPen(QPen(Qt::darkGray, 1, Qt::SolidLine)); // Стиль линии сетки

    for (int i = centerX % gridSize; i <= width; i += gridSize) {
        painter.drawLine(i, 0, i, height); // Вертикальные линии сетки
    }

    for (int i = centerY % gridSize; i <= height; i += gridSize) {
        painter.drawLine(0, i, width, i); // Горизонтальные линии сетки
    }

   /* // Подписи к осям
    painter.drawText(centerX + 5, 20, "X");
    painter.drawText(width - 20, centerY - 5, "Y");

   /* // Масштабирование подписей
    painter.scale(1 / scaleFactor, 1 / scaleFactor);*/

    QFont font;

    // Выбор и вызов метода для отрисовки на основе значения currentAlgorithm
    switch (currentAlgorithm) {
    case 0:
        drawStepByStepLine(painter);
        // Установка выравнивания текста по центру
        font.setPointSize(12);
        painter.setFont(font);
        break;
    case 1:
        drawDDALine(painter);
        font.setPointSize(12);
        painter.setFont(font);
        // Установка выравнивания текста по центру
        //painter.drawText(textRect, Qt::AlignCenter, "Алгоритм ЦДА");
        break;
    case 2:
        drawBresenhamLine(painter);
        font.setPointSize(12);
        painter.setFont(font);
        //painter.drawText(textRect, Qt::AlignCenter, "Алгоритм Брезенхема (линия)");
        break;
    case 3:
        drawBresenhamCircle(painter);
        font.setPointSize(12);
        painter.setFont(font);
        //painter.drawText(textRect, Qt::AlignCenter, "Алгоритм Брезенхема (окружность)");
        break;
    case 4:
        drawBresenhamCircle2(painter);
        font.setPointSize(12);
        painter.setFont(font);
        //painter.drawText(textRect, Qt::AlignCenter, "Алгоритм Брезенхема (окружность)");
        break;
    case 5:
        drawCastle(painter);
        font.setPointSize(12);
        painter.setFont(font);
        //painter.drawText(textRect, Qt::AlignCenter, "Алгоритм Брезенхема (окружность)");
        break;
    default:
        break;
    }
}


void MainWindow::drawNextAlgorithm() {
    currentAlgorithm = (currentAlgorithm + 1) % 6;

    const int numIterations = 10; // Количество итераций для усреднения времени выполнения
    qint64 totalNanoSeconds = 0;

    for (int i = 0; i < numIterations; ++i) {
        QElapsedTimer timer;
        timer.start();

        update();

        qint64 elapsed = timer.nsecsElapsed();
        totalNanoSeconds += elapsed;
    }

    nanoSeconds = totalNanoSeconds / numIterations;

    QString s = QString::number(nanoSeconds);
    // Подписи значений
    sec->setText(s);
    sec->setGeometry(50, 20, 200, 35);
    QFont font("Bookman Old Style", 8);
    sec->setFont(font);
    sec->show();
    //update();
}

void MainWindow::drawPrevAlgorithm() {
    currentAlgorithm = (currentAlgorithm - 1 + 6) % 6; // Обратный переход на предыдущий алгоритм

    const int numIterations = 10; // Количество итераций для усреднения времени выполнения
    qint64 totalNanoSeconds = 0;

    for (int i = 0; i < numIterations; ++i) {
        QElapsedTimer timer;
        timer.start();

        update();

        qint64 elapsed = timer.nsecsElapsed();
        totalNanoSeconds += elapsed;
    }

    nanoSeconds = totalNanoSeconds / numIterations;

    QString s = QString::number(nanoSeconds);
    // Подписи значений
    sec->setText(s);
    sec->setGeometry(50, 20, 200, 35);
    QFont font("Bookman Old Style", 8);
    sec->setFont(font);
    sec->show();

    //update();
}

void MainWindow::drawStepByStepLine(QPainter &painter) {
    int windowWidth = 800;
    int windowHeight = 500;

    // Центр окна
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;

    int x1 = centerX + 10; // Начальная точка смещена на 150 пикселей влево от центра по x
    int y1 = centerY - 10; // Начальная точка смещена на 100 пикселей вверх от центра по y
    int x2 = centerX + 250; // Конечная точка смещена на 150 пикселей вправо от центра по x
    int y2 = centerY - 150; // Конечная точка смещена на 50 пикселей вниз от центра по y
    /////////////////////////////////////

    // разница между начальными и конечными точками
    int dx = x2 - x1;
    int dy = y2 - y1;

    //количество шагов на построение всей линии - большее из dx и dy
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // на сколько будет увеличиваться переменные с каждым шагом
    float xIncrement = float(dx) / steps;
    float yIncrement = float(dy) / steps;

    float x = x1;
    float y = y1;

    painter.setPen(Qt::magenta);
    //
    int pointRadius = 1; // Задайте радиус точки здесь
    // Установка стиля пера для рисования точки
    QPen pen = painter.pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(pointRadius); // Устанавливаем ширину пера равную двойному радиусу точки
    painter.setPen(pen);
    //

    for (int i = 0; i <= steps; ++i) {
        painter.drawPoint(round(x), round(y));

        x += xIncrement;
        y += yIncrement;
    }

    QString values = "X1: " + QString::number(x1) +
                     ", Y1: " + QString::number(y1) +
                     ", X2: " + QString::number(x2) +
                     ", Y2: " + QString::number(y2);
    //painter.drawText(10, 20, values); // Расположение текста с координатами

    // Подписи значений
    basic_info->setText(values);
    basic_info->setGeometry(10, 0, 200, 35);
    QFont font("Bookman Old Style", 8);
    basic_info->setFont(font);
    basic_info->show();

    names->setText("Step-by-step algorithm");
    names->setAlignment(Qt::AlignCenter);
    names->setGeometry(250, 450, 300, 25);
    names->setFont(font);
    names->show();

    painter.setPen(QPen(Qt::black, 0.2));
    painter.drawLine(x1, y1, x2, y2);
}

void MainWindow::drawDDALine(QPainter &painter) {
    basic_info->show();
    int width = 800;
    int height = 500;

    int centerX = width / 2;
    int centerY = height / 2;

    int x1 = centerX + 10; // Начальная точка смещена на 150 пикселей влево от центра по x
    int y1 = centerY - 10; // Начальная точка смещена на 100 пикселей вверх от центра по y
    int x2 = centerX + 250; // Конечная точка смещена на 150 пикселей вправо от центра по x
    int y2 = centerY - 150; // Конечная точка смещена на 50 пикселей вниз от центра по y
    /////////////////////////////////////
    int dx = x2 - x1;
    int dy = y2 - y1;

    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = float(dx) / steps;
    float yIncrement = float(dy) / steps;

    float x = x1;
    float y = y1;

    painter.setPen(Qt::darkBlue); // Установка цвета линии

    int pointRadius = 1; // Задайте радиус точки здесь
    // Установка стиля пера для рисования точки
    QPen pen = painter.pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(pointRadius); // Устанавливаем ширину пера равную двойному радиусу точки
    painter.setPen(pen);

    for (int i = 0; i <= steps; ++i) {
        painter.drawPoint(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }

    QString values = "X1: " + QString::number(x1) +
                     ", Y1: " + QString::number(y1) +
                     ", X2: " + QString::number(x2) +
                     ", Y2: " + QString::number(y2);

    // Подписи значений
    basic_info->setText(values);
    basic_info->setGeometry(10, 0, 200, 35);
    QFont font("Bookman Old Style", 8);
    basic_info->setFont(font);
    basic_info->show();

    names->setText("DDA algorithm");
    names->setAlignment(Qt::AlignCenter);
    names->setGeometry(250, 450, 300, 25);
    names->setFont(font);
    names->show();

    painter.setPen(QPen(Qt::black, 0.1));
    painter.drawLine(x1, y1, x2, y2);
}



void MainWindow::drawCastle(QPainter &painter) {
    basic_info->show();
    int width = 800;
    int height = 500;

    int centerX = width / 2;
    int centerY = height / 2;

    int x1 = centerX + 10; // Начальная точка смещена на 150 пикселей влево от центра по x
    int y1 = centerY - 10; // Начальная точка смещена на 100 пикселей вверх от центра по y
    int x2 = centerX + 250; // Конечная точка смещена на 150 пикселей вправо от центра по x
    int y2 = centerY - 150; // Конечная точка смещена на 50 пикселей вниз от центра по y
    /////////////////////////////////////


    // Вычисляем разности координат
    int dx = x2 - x1;
    int dy = y2 - y1;

    int m1 = 1, m2 = 2;

    int k = centerY - 150;
    int y = centerY - k;
    int x = 250 - (centerY - k);

    int check_m1 = 10;
    int check_m2 = 10;
    // Сравниваем x и y
    while (x != y) {
        if (x > y) {
        // Уточняем верхнее приближение m2 и переменную x
        m2 += (m1 * check_m2);
        check_m2 *= check_m1;
        x = x - y;
        } else {
        // Уточняем нижнее приближение m1 и переменную y
        m1 += (m2 * check_m1);
        check_m1 *= check_m2;
        y = y - x;
        }
    }

    int m11 = 0;
    int check = check_m1 / 10;
    while (m1 % 10 != 0)
    {
        m11 += (m1 % 10) * check;
        check /= 10;
        m1 /= 10;
    }

    // Окончательный результат
    int m = (m2 * check_m1) + m11;

    int kk = m;
    m *= check_m1;
    m*= check_m2;
    m+= kk;

    // Рисуем отрезок
    int currentX = x2;
    int currentY = y2;

    painter.setPen(Qt::darkBlue); // Установка цвета линии

    int pointRadius = 3; // Задайте радиус точки здесь
    // Установка стиля пера для рисования точки
    QPen pen = painter.pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(pointRadius); // Устанавливаем ширину пера равную двойному радиусу точки
    painter.setPen(pen);

    painter.drawPoint(x1, y1);

    int curX = 0;
    int curY = 0;

    while (currentX >= x1 && currentY <= y1) {
        //drawPixel(painter, currentX, currentY);
        int pointRadius = 4; // Задайте радиус точки здесь
        // Установка стиля пера для рисования точки
        painter.setPen(Qt::darkBlue);
        QPen pen = painter.pen();
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidth(pointRadius); // Устанавливаем ширину пера равную двойному радиусу точки
        painter.setPen(pen);
        painter.drawPoint(round(currentX), round(currentY));
        curX = currentX;
        curY = currentY;
        if (m % 10 == 1)
        {
        currentX -= 25;
        m /= 10;
        }
        else
        {
        currentX -= 25;
        currentY += 25;
        m /= 10;
        }

        if (currentX >= x1)
        {
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(curX, curY, currentX, currentY);
        }
        if (currentX < x1)
        {
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(curX, curY, x1, y1);
        }
    }

    std::cout<< "M1:::" <<currentX << ":M2:" << currentX << "....." ;
    ///////////////////////////////////

    QString values = "X1: " + QString::number(x1) +
                     ", Y1: " + QString::number(y1) +
                     ", X2: " + QString::number(x2) +
                     ", Y2: " + QString::number(y2);

    // Подписи значений
    basic_info->setText(values);
    basic_info->setGeometry(10, 0, 200, 35);
    QFont font("Bookman Old Style", 8);
    basic_info->setFont(font);
    basic_info->show();

    names->setText("Castle-Pitway");
    names->setAlignment(Qt::AlignCenter);
    names->setGeometry(250, 450, 300, 25);
    names->setFont(font);
    names->show();

    painter.setPen(QPen(Qt::black, 0.1));
    painter.drawLine(x1, y1, x2, y2);
}


void MainWindow::drawBresenhamLine(QPainter &painter) {
    int width = 800;
    int height = 500;

    int centerX = width / 2;
    int centerY = height / 2;

    int x1 = centerX + 10; // Начальная точка смещена на 150 пикселей влево от центра по x
    int y1 = centerY - 10; // Начальная точка смещена на 100 пикселей вверх от центра по y
    int x2 = centerX + 250; // Конечная точка смещена на 150 пикселей вправо от центра по x
    int y2 = centerY - 150; // Конечная точка смещена на 50 пикселей вниз от центра по y
    /////////////////////////////////////


    painter.setPen(QPen(Qt::black, 0.1));
    painter.drawLine(x1, y1, x2, y2);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

// по всем направлениям так как sy и sx устанавливает направление
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    painter.setPen(Qt::blue); // Установка цвета линии

    int pointRadius = 1; // Задайте радиус точки здесь
    // Установка стиля пера для рисования точки
    QPen pen = painter.pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(pointRadius); // Устанавливаем ширину пера равную двойному радиусу точки
    painter.setPen(pen);

    while (x1 != x2 || y1 != y2) {
        painter.drawPoint(x1, y1);
        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    QString values = "X1: " + QString::number(x1) +
                     ", Y1: " + QString::number(y1) +
                     ", X2: " + QString::number(x2) +
                     ", Y2: " + QString::number(y2);

    // Подписи значений
    basic_info->setText(values);
    basic_info->setGeometry(10, 0, 200, 35);
    QFont font("Bookman Old Style", 8);
    basic_info->setFont(font);
    basic_info->show();

    names->setText("Bresenham algorithm -> LINE");
    names->setAlignment(Qt::AlignCenter);
    names->setGeometry(250, 450, 300, 25);
    names->setFont(font);
    names->show();

}

void MainWindow::drawBresenhamCircle(QPainter &painter) {
    int width = 800;
    int height = 500;

    int centerX = width / 2;
    int centerY = height / 2;

    int radius = 100; // Радиус окружности

    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    painter.setPen(Qt::darkGreen); // Установка цвета окружности

    int pointRadius = 1; // Задайте радиус точки здесь
    // Установка стиля пера для рисования точки
    QPen pen = painter.pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(pointRadius * 1.25); // Устанавливаем ширину пера равную двойному радиусу точки
    painter.setPen(pen);

    while (x <= y) {
        painter.drawPoint(centerX + x, centerY + y);
        painter.drawPoint(centerX + x, centerY - y);
        painter.drawPoint(centerX - x, centerY + y);
        painter.drawPoint(centerX - x, centerY - y);
        painter.drawPoint(centerX + y, centerY + x);
        painter.drawPoint(centerX + y, centerY - x);
        painter.drawPoint(centerX - y, centerY + x);
        painter.drawPoint(centerX - y, centerY - x);

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    QString values = "Radius: " + QString::number(radius) +
                     ", X: " + QString::number(x) +
                     ", Y: " + QString::number(y) +
                     ", D: " + QString::number(d);

    // Подписи значений
    basic_info->setText(values);
    basic_info->setGeometry(10, 0, 200, 35);
    QFont font("Bookman Old Style", 8);
    basic_info->setFont(font);
    basic_info->show();

    names->setText("Bresenham algorithm -> CIRCLE");
    names->setAlignment(Qt::AlignCenter);
    names->setGeometry(250, 450, 300, 25);
    names->setFont(font);
    names->show();
}


void MainWindow::drawBresenhamCircle2(QPainter &painter) {
    int width = 800;
    int height = 500;

    int centerX = width / 2;
    int centerY = height / 2;

    int radius = 100; // Радиус окружности

    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

       painter.setPen(QPen(Qt::gray, 5));
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

        painter.setPen(QPen(Qt::yellow, 1));
    while (x <= y) {
        drawSmoothedPoints(painter, centerX, centerY, x, y); // Рисуем сглаженные точки окружности

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    QString values = "Radius: " + QString::number(radius) +
                     ", X: " + QString::number(x) +
                     ", Y: " + QString::number(y) +
                     ", D: " + QString::number(d);

    // Подписи значений
    basic_info->setText(values);
    basic_info->setGeometry(10, 0, 200, 35);
    QFont font("Bookman Old Style", 8);
    basic_info->setFont(font);
    basic_info->show();

    names->setText("Bresenham algorithm -> CIRCLE (smoothed)");
    names->setAlignment(Qt::AlignCenter);
    names->setGeometry(250, 450, 300, 25);
    names->setFont(font);
    names->show();
}

void MainWindow::drawSmoothedPoints(QPainter &painter, int centerX, int centerY, int x, int y) {
    painter.drawPoint(centerX + x, centerY + y);
    painter.drawPoint(centerX + x, centerY - y);
    painter.drawPoint(centerX - x, centerY + y);
    painter.drawPoint(centerX - x, centerY - y);
    painter.drawPoint(centerX + y, centerY + x);
    painter.drawPoint(centerX + y, centerY - x);
    painter.drawPoint(centerX - y, centerY + x);
    painter.drawPoint(centerX - y, centerY - x);

    painter.drawPoint(centerX + x, centerY + y - 1);
    painter.drawPoint(centerX + x, centerY - y + 1);
    painter.drawPoint(centerX - x, centerY + y - 1);
    painter.drawPoint(centerX - x, centerY - y + 1);
    painter.drawPoint(centerX + y, centerY + x - 1);
    painter.drawPoint(centerX + y, centerY - x + 1);
    painter.drawPoint(centerX - y, centerY + x - 1);
    painter.drawPoint(centerX - y, centerY - x + 1);
}
