#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsView>
#include <QTimer>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Button_clicked();
    void lottoNumbers();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPushButton *button;
    QGraphicsView *graphicsView;
    QTimer *timer;
    QList<QList<int>> Numbers;
    int currentIndex;
    int currentRow;
};

#endif // MAINWINDOW_H
