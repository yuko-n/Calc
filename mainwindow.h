#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLineEdit *line_1;
    QLineEdit *line_2;
    QLineEdit *line_buff;
   private slots:
    void digits_numbers();
    void operations();
    void digitClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void del();
    void clearAll();
private:
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);
    //void on_button_clicked(QPushButton *digitButtons);
};

#endif // MAINWINDOW_H
