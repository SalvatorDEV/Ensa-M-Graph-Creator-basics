#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include<edge.h>
#include <sommet.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow :public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
   MainWindow(QGraphicsScene *scene);


    ~MainWindow();
   // void itemMoved();
    void addNode();
     void addEdge(int a,int b,int c);
    void randomOne(int som,int aret,int maxP);
//liste des nodes
    QVector <sommet *> listeSom;
    QVector <edge *> listeEdge;

    sommet* GetSomById(int id);
    void colorier();
public slots:


protected:




private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    friend class sommet;
    Ui::MainWindow *my_ui;
    QGraphicsScene *mascene;
    MainWindow *mongraphe;

};
#endif // MAINWINDOW_H
