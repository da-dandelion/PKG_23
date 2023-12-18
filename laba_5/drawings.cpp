#include <QVector>
#include <QPair>
#include "drawings.h"
#include <fstream>
#include<iostream>
#include <cmath>

drawings::drawings(type t, QWidget *parent ): QWidget(parent)
{
    std::ifstream fin("D:/QT SEM2/5lab/input.txt");
    int n;
    fin>>n;
    int x1,y1,x2,y2;
    QPointF p1, p2;
    for(int i = 0; i < n; i++){
        fin>>x1>>y1>>x2>>y2;
        p1.setX(x1);
        p1.setY(y1);
        p2.setX(x2);
        p2.setY(y2);
        segments.push_back(qMakePair(p1,p2));
        sss.push_back(qMakePair(p1,p2));
    }
    fin>>Xmin>>Ymin>>Xmax>>Ymax;
    fin>>n;
    for(int i = 0; i<n;i++){
        fin>>x1>>y1>>x2>>y2;
        p1.setX(x1);
        p1.setY(y1);
        p2.setX(x2);
        p2.setY(y2);
        polygon.push_back(qMakePair(p1,p2));
    }
    this->t = t;
    if(t == type::Sutherland){
        clipSegments();
    }else{
        Cirus();
    }
}

void drawings::clipSegments()
{
    QVector<QPair<QPointF, QPointF>> clippedSegments;
    for (int i = 0; i < segments.size(); i++)
    {
        QPointF P1 = segments[i].first;
        QPointF P2 = segments[i].second;
        QPointF P3 = P2;
        //QPointF P4 = P1;
        //std::cout << P1.x() << P1.y() << P2.x() << P2.y();
        int P1_code = getCode(P1), P2_code = getCode(P2);
        //std::cout << P1_code << "second"<< P2_code <<std::endl;
        int kkk = 0;
        if (P1_code == 0)
        {
            if (P2_code == 0){
            clippedSegments.push_back(segments[i]);
            centers.push_back(segments[i]);
            //std::cout << "result" <<  P1.x() <<  P1.y() <<  P2.x() <<  P2.y() << std::endl;
            //std::cout << "ddddd" << centers.size();
            kkk = 1;
            }
            else
            {
            P2 =  P1;
            P1 = P3;
            //std::cout << "NNNNNEEEEEEWWWWWWW" <<  P1.x() <<  P1.y() <<  P2.x() <<  P2.y() << std::endl;
            int code = P1_code;
            P1_code = P2_code;
            P2_code = code;
            //std::cout << "NNNNNEEEEEEWWWWWWW" <<  P1_code <<  P2_code << std::endl;
            }
        }
            if ((P1_code % 10 == 1) && (P2_code % 10 == 1) && P2_code != 0) {
            //k = 1;
            }
            else if ((P1_code % 100 == 10) && (P2_code % 100 == 10) && P2_code != 0) {
            //k = 1;
            }
            else if ((P1_code >= 1000) && (P2_code >= 1000) && P2_code != 0) {
            //k = 1;
            }
            else if ((P1_code >= 100) && (P2_code >= 100) && (P1_code < 1000) && (P2_code < 1000) && P2_code != 0) {
            //k = 1;
            }
        else if (kkk == 0)
        {
            QPointF intersectionPoint1, intersectionPoint2;
            intersectionPoint2 = segments[i].second;
            int k = 0;

                // Проверка, является ли отрезок полностью невидимым внутри прямоугольника

                // Вычисление точек пересечения отрезка с границами прямоугольника
                double x1 = P1.x();
                double y1 = P1.y();
                double x2 = P2.x();
                double y2 = P2.y();
                //std::cout << "NNNNNEEEEEEWWWWWWW" <<  x1 <<  y1 <<  x2 <<  y2 << std::endl;

                // Проверка и обновление координат точек пересечения для каждой границы прямоугольника
                if (P1_code % 10 == 1) { // Код P1 указывает на левую границу прямоугольника
                    double x = Xmin;
                    double y = y1 + (y2 - y1) * (Xmin - x1) / (x2 - x1);
                    //double x = (x2 -x1) * (Ymax - Ymin);
                    //double y =  ((x1 * y2 - y1 * x2) * (Ymax - Ymin) - (Xmax * (Ymax - Ymin)) * (y2 - y1)) / ((x2 -x1) * (Ymax - Ymin));
                    intersectionPoint1.setX(x);
                    intersectionPoint1.setY(y);
                    segments.push_back(qMakePair(intersectionPoint1, P2));
                    //centers.push_back(qMakePair(intersectionPoint1, intersectionPoint2));
                } else if (P1_code % 100 == 10) { // Код P1 указывает на правую границу прямоугольника
                    double x = Xmax;
                    double y = y1 + (y2 - y1) * (Xmax - x1) / (x2 - x1);
                    intersectionPoint1.setX(x);
                    intersectionPoint1.setY(y);
                    segments.push_back(qMakePair(intersectionPoint1, P2));
                    //std::cout << "///////////////" <<  intersectionPoint1.x() <<  intersectionPoint1.y() <<  intersectionPoint2.x() <<  intersectionPoint2.y() << std::endl;
                } else if ((P1_code >= 100) && (P1_code < 1000)) { // Код P1 указывает на нижнюю границу прямоугольника
                    double y = Ymin;
                    double x = x1 + (x2 - x1) * (Ymin - y1) / (y2 - y1);
                    P1.setX(x);
                    P1.setY(y);
                    intersectionPoint1.setX(x);
                    intersectionPoint1.setY(y);
                    //std::cout << "__________" << P1.x() << P1.y() << "PPPPPPPPPPPPPPPPPPPP";
                    segments.push_back(qMakePair(intersectionPoint1, P2));
                } else if (P1_code >= 1000) { // Код P1 указывает на верхнюю границу прямоугольника
                    double y = Ymax;
                    double x = x1 + (x2 - x1) * (Ymax - y1) / (y2 - y1);
                    intersectionPoint1.setX(x);
                    intersectionPoint1.setY(y);
                    segments.push_back(qMakePair(intersectionPoint1, P3));
                    //std::cout << "************" <<  intersectionPoint1.x() <<  intersectionPoint1.y() <<  intersectionPoint2.x() <<  intersectionPoint2.y() << std::endl;
                }

                // Обновление кода P1
                P1_code = getCode(intersectionPoint1);
                P1 = intersectionPoint1;
            }
            //clipByCohenSutherland(P1, P2, P1_code, P2_code, intersectionPoint1, intersectionPoint2);
            //centers.push_back(qMakePair(intersectionPoint1, intersectionPoint2));
       //}
    }
    segments = clippedSegments;
}

int drawings::getCode(QPointF point)
{
    int code = 0;
    double x = point.x();
    double y = point.y();

    if (x < Xmin)
        code += 1; // Левая граница прямоугольника
    else if (x > Xmax)
        code += 10; // Правая граница прямоугольника

    if (y < Ymin)
        code += 100; // Нижняя граница прямоугольника
    else if (y > Ymax)
        code += 1000; // Верхняя граница прямоугольника

    return code;
}

//////////////////////////////////////////////
void drawings::Cirus(){
    for(int i = 0; i < segments.size(); i++){
        ClipByCirus(segments[i]);
        if (t_1 < 0 || t_1 > 1 || t_2 < 0 || t_2 > 1){
            continue;
        }else{
            QPointF begin = segments[i].first;
            QPointF end = segments[i].second;
            QPointF p1;
            p1.setX(begin.x() + t_1 * (end.x() - begin.x()));
            p1.setY(begin.y() + t_1 * (end.y() - begin.y()));
            QPointF p2;
            p2.setX(begin.x() + t_2 * (end.x() - begin.x()));
            p2.setY(begin.y() + t_2 * (end.y() - begin.y()));
            clippedSegments.push_back(qMakePair(p1,p2));
        }
    }
}
//////////////////////////////////////////////////
float drawings::getT(QPair<QPointF,QPointF> edge, QPair<QPointF,QPointF> segment, bool* onLine){
    bool a;
    float ks = (segment.second.y()-segment.first.y())/(segment.second.x()-segment.first.x());
    float ke = (edge.second.y()-edge.first.y())/(edge.second.x()-edge.first.x());
    float bs = segment.first.y() - ks*segment.first.x();
    float be = edge.first.y() - ke*edge.first.x();
    float x = (be-bs)/(ks-ke);
    if ((x - edge.first.x()) / (edge.second.x() - edge.first.x()) <= 0 || (x - edge.first.x()) / (edge.second.x() - edge.first.x()) >= 1){
        return -1;
    }
    if ((segment.second.x() - segment.first.x()) == 0 && ke == ks && be == bs){
        a = true;
        onLine = &a;
        return-1;
    }else{
        float te = (x - segment.first.x()) / (segment.second.x() - segment.first.x());
        return te;
    }
}

float ScalarMultiply(QPair<QPointF,QPointF> v1, QPair<QPointF,QPointF> v2){
    float v1x1 = v1.first.y();
    float v1x2 = v1.second.y();
    float v1y1 = v1.first.x();
    float v1y2 = v1.second.x();
    float v2x1 = v2.first.x();
    float v2x2 = v2.second.x();
    float v2y1 = v2.first.y();
    float v2y2 = v2.second.y();
    return(-(v1x2-v1x1)*(v2x2-v2x1) + (v1y2-v1y1)*(v2y2-v2y1));
}

float getParameterOfPoint(QPointF p, QPair<QPointF, QPointF> segment)
{
    return (p.x() - segment.first.x()) / (segment.second.x() - segment.first.x());
}

void drawings::ClipByCirus(QPair<QPointF, QPointF> segment){
    QVector<float> T_enter;
    QVector<float> T_outer;
    float t, S;
    bool onLine = false;
    for(int i = 0; i<polygon.size();i++){
        t = getT(polygon[i], segment, &onLine);
        if(onLine){
            T_enter.push_back(getParameterOfPoint(polygon[i].first, segment));
            T_outer.push_back(getParameterOfPoint(polygon[i].second, segment));
            T_outer.push_back(getParameterOfPoint(polygon[i].first, segment));
            T_enter.push_back(getParameterOfPoint(polygon[i].second, segment));
            onLine = false;
            continue;
        }
        S=-ScalarMultiply(polygon[i], segment);
        if(t>=0 && t<=1){
            if(S>0){
                T_enter.push_back(t);
            }else if(S<0){
                T_outer.push_back(t);
            }else{
                T_enter.push_back(t);
                T_outer.push_back(t);
            }
        }
    }
    if(T_outer.size() == 0 && T_enter.size() == 0){
        t_1 = -1;
        t_2 = -1;
        return;
    }

    float t_enter = 0;
    float t_outer = 1;
    for (int i = 0; i < T_enter.size(); i++){
        if (t_enter < T_enter[i])
        {
            t_enter = T_enter[i];
        }
    }
    for (int i = 0; i < T_outer.size(); i++){
        if (t_outer > T_outer[i])
        {
            t_outer = T_outer[i];
        }
    }
    t_1 = t_enter;
    t_2 = t_outer;
}
