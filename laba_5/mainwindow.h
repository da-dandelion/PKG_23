#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <drawings.h>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
        void wheelEvent(QWheelEvent *event) override;
public slots:
    void showCirus(){
        p->hide();
        p = new drawings(type::Cirus);
        l->addWidget(p,0,0,12,1);
        p->show();
    }
    void showSutherland(){
        p->hide();
        p = new drawings(type::Sutherland);
        l->addWidget(p,0,0,12,1);
        p->show();
    }
private:
    drawings* p = new drawings(type::Cirus);
    QGridLayout *l = new QGridLayout;
    Ui::MainWindow *ui;
    QPushButton *pbSutherland;
    QPushButton *pbCirus;

        qreal scaleFactor;
};
#endif // MAINWINDOW_H
