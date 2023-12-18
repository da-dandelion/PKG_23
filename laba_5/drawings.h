#ifndef DRAWINGS_H
#define DRAWINGS_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <iostream>

enum type{
    Cirus,
    Sutherland
};

class drawings : public QWidget
{
public:
    drawings(type, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*)
    {
        QPainter painter1(this);
        double h = this->height();
        double w = this->width();
        h/=2;
        w/=2;
        double hScale = 20;
        double wScale = 20;
/*        painter1.translate(offsetX, offsetY);
        // Масштабирование координат и размеров элементов
        painter1.scale(scaleFactor, scaleFactor);
        painter1.translate((1 / scaleFactor - 1) * this->width()/ 2, (1 / scaleFactor - 1) * this->height() / 2);
*/
        painter1.translate(w,h);
        QPainterPath text;
        QFont f ("Times", 8);
        f.setStyleStrategy(QFont::ForceOutline);
        painter1.setPen(QPen(Qt::black, 1));
        painter1.drawLine(-this->width()/2, 0, this->width()/2, 0);
        painter1.drawLine(0, -this->height()/2, 0, this->height()/2);
        painter1.setPen(QPen(Qt::black, 3));
        text.addText(0, 0, f, QString::number(0));
        for(int i = 1; i < this->width()/(wScale*2); i++){
            painter1.setPen(QPen(Qt::black, 3));
            painter1.drawPoint(i*wScale, 0);
            text.addText(i*wScale, 12, f, QString::number(i));
            painter1.drawPoint(-i*wScale, 0);
            text.addText(-i*wScale, 12, f, QString::number(-i));
            painter1.setPen(QPen(Qt::black, 1));
            painter1.drawLine(-i*wScale, -this->height()/2, -i*wScale, this->height()/2);
            painter1.drawLine(i*wScale, -this->height()/2, i*wScale, this->height()/2);
        }
        for(int i = 1; i < this->height()/(hScale*2); i++){
            painter1.setPen(QPen(Qt::black, 3));
            painter1.drawPoint(0, i*hScale);
            text.addText(0, -i*hScale, f, QString::number(i));
            painter1.drawPoint(0, -i*hScale);
            text.addText(0, i*hScale, f, QString::number(-i));
            painter1.setPen(QPen(Qt::black, 1));
            painter1.drawLine(-this->width()/2, -i*hScale, this->width()/2, -i*hScale);
            painter1.drawLine(-this->width()/2, i*hScale, this->width()/2, i*hScale);
        }
        painter1.setPen(QPen(Qt::yellow, 3));
        for(int i = 0; i<sss.size(); i++){
            //std::cout<< "segs" << sss.size() << "end";
            // std::cout<<segments[i].first.x() <<  segments[i].first.y() << segments[i].second.x() << segments[i].second.y()<<std::endl;
            painter1.drawLine(sss[i].first.x()*20, -sss[i].first.y()*20, sss[i].second.x()*20, -sss[i].second.y()*20);
        }
        /*
        painter1.setBrush(Qt::NoBrush);
        for(int i = 0; i<segments.size(); i++){
            std::cout<< "segs" << segments.size() << "end";
           // std::cout<<segments[i].first.x() <<  segments[i].first.y() << segments[i].second.x() << segments[i].second.y()<<std::endl;
            painter1.drawLine(segments[i].first.x()*20, -segments[i].first.y()*20, segments[i].second.x()*20, -segments[i].second.y()*20);
        }*/
        painter1.setPen(QPen(Qt::blue, 4));
        if(t == type::Sutherland){
            painter1.drawLine(Xmax*20, -Ymax*20, Xmax*20, -Ymin*20);
            painter1.drawLine(Xmax*20, -Ymax*20, Xmin*20, -Ymax*20);
            painter1.drawLine(Xmin*20, -Ymin*20, Xmax*20, -Ymin*20);
            painter1.drawLine(Xmin*20, -Ymin*20, Xmin*20, -Ymax*20);
        }else{
            for(int i = 0; i<polygon.size();i++){
                painter1.drawLine(polygon[i].first.x()*20,-polygon[i].first.y()*20,polygon[i].second.x()*20,-polygon[i].second.y()*20);
            }
        }
        painter1.setPen(QPen(Qt::darkGreen, 4));
        for(int i = 0; i<clippedSegments.size(); i++){
            painter1.drawLine(clippedSegments[i].first.x()*20, -clippedSegments[i].first.y()*20, clippedSegments[i].second.x()*20, -clippedSegments[i].second.y()*20);
        }
        painter1.setPen(QPen(Qt::black, 1));
        painter1.setBrush(QBrush(Qt::black));
        painter1.drawPath(text);

        painter1.setPen(QPen(Qt::darkGreen, 4));

        // Проходим по списку центров и рисуем отрезки на сцене
        for(int i = 0; i< centers.size(); i++){
            painter1.drawLine(centers[i].first.x() * 20, -centers[i].first.y() * 20, centers[i].second.x() * 20, -centers[i].second.y() * 20);
        }
    }
private:
    void clipSegments();
    void Cirus();
    void ClipByCirus(QPair<QPointF,QPointF>);
    float getT(QPair<QPointF,QPointF>,QPair<QPointF,QPointF>, bool*);
    int getCode(QPointF);
    QPointF intersectionPoint(QPointF,QPointF);
    QVector<QPair<QPointF,QPointF>> segments;
    QVector<QPair<QPointF,QPointF>> sss;
    QVector<QPair<QPointF,QPointF>> polygon;
    QVector<QPair<QPointF,QPointF>> centers;
    QVector<QPair<QPointF,QPointF>> clippedSegments;
    QVector<QPointF> CirusSegment;

    void clipByCohenSutherland(QPointF &P1, QPointF &P2, int P1_code, int P2_code, QPointF &intersectionPoint1, QPointF &intersectionPoint2);
    int Xmin, Xmax, Ymin, Ymax;
    type t;
    float t_1, t_2;

    int offsetX = 0;
    int offsetY = 0;
            qreal scaleFactor;
};

#endif // DRAWINGS_H
