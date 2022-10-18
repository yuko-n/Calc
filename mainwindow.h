#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLabel *line_1;
    QLabel *line_2;
   private slots:
    void digits_numbers();
    void operations();
    //void on_button_clicked(QPushButton *digitButtons);
};

#endif // MAINWINDOW_H
