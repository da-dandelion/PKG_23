#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTableWidget>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

private slots:
    void Direction(const QModelIndex &index);
    void ProviderChoice();
    void OpenFile();
    void addImageToTable(const QString &imagePath);
    void addToTable(const QString &fileName, const QString &size, const QString &resolution, const QString &colorDepth, const QString &compression);

private:
    void addItemToTable(const QString &fileName, const QString &size, const QString &resolution, const QString &colorDepth, const QString &compression);
    Ui::Widget *ui;
    QFileSystemModel *provider;
    QTableWidget *info;
    double calculateCompressionRatio(const QSize &imageSize, qint64 fileSize);
};

#endif // WIDGET_H
