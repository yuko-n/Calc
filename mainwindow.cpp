#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>
#include <QGridLayout>
#include <QToolButton>
#include <QFont>
#include <QLabel>

double num_first;
QString all;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QGridLayout *grid = new QGridLayout;
    QVBoxLayout *label_lay = new  QVBoxLayout;
    QHBoxLayout *clear_lay = new  QHBoxLayout;
    line_1 = new QLabel(this);
    line_2 = new QLabel(this);
    QPushButton *clear = new QPushButton(this);
    QPushButton *del = new QPushButton(this);

    //line -> setReadOnly(true);
    line_1 -> setStyleSheet("QLabel {background-color: white}");
    line_2 -> setStyleSheet("QLabel {background-color: white}");
   // line -> setMaxLength(10);
    line_1 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    line_2 -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    clear -> setText("Clear");
    clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    del -> setText("Delete");
    del->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    del->setFont(QFont("consolas", 9));

    label_lay->addWidget(line_1);
    label_lay->addWidget(line_2);
    clear_lay->addWidget(clear);
    clear_lay->addWidget(del);

    grid->setSpacing(1);
    grid->setMargin(1);
    clear_lay->setSpacing(1);
    clear_lay->setMargin(1);

    line_1->setMinimumSize(170, 40);
    line_2->setMinimumSize(170, 40);

    clear->setMinimumSize(84, 40);
    clear->setStyleSheet("QPushButton {background-color: rgb(115, 83, 186); border: 1px solid rgb(115, 83, 186)} QPushButton:hover {background-color: rgb(137, 109, 197); border: 1px solid rgb(115, 83, 186)} QPushButton:pressed {background-color: rgb(239, 195, 245); border: 1px solid rgb(239, 195, 245)}");
    clear->setFont(QFont("consolas", 9));
    del->setMinimumSize(84, 40);
    del->setStyleSheet("QPushButton {background-color: rgb(115, 83, 186); border: 1px solid rgb(115, 83, 186)} QPushButton:hover {background-color: rgb(137, 109, 197); border: 1px solid rgb(115, 83, 186)} QPushButton:pressed {background-color: rgb(239, 195, 245); border: 1px solid rgb(239, 195, 245)}");

    QList<QString> values(
                    { "1", "2", "3", "+",
                      "4", "5", "6", "-",
                      "7", "8", "9", "*",
                      "0", ".", "/", "=",
                      "n^2", "√n", "n!", "log n",
                      "sin n", "cos n", "tg n", "ctg n"
                    });

    QButtonGroup *buttons = new QButtonGroup(this);

    QPushButton *digitButtons[24];

      for (int i=0; i<values.length(); i++){
          digitButtons[i] = new QPushButton();
          if (i<15)   digitButtons[i]->setStyleSheet("QPushButton {background-color: rgb(172, 153, 214); border: 1px solid rgb(172, 153, 214)} QPushButton:hover {background-color: rgb(196, 182, 226); border: 1px solid rgb(196, 182, 226)} QPushButton:pressed {background-color: rgb(239, 195, 245); border: 1px solid rgb(239, 195, 245)}");
          else if (i>15)    digitButtons[i]->setStyleSheet("QPushButton {background-color: rgb(95, 80, 145); border: 1px solid rgb(95, 80, 145)} QPushButton:hover {background-color: rgb(116, 100, 166); border: 1px solid rgb(116, 100, 166)} QPushButton:pressed {background-color: rgb(166, 141, 242); border: 1px solid rgb(166, 141, 242)}");
          else if (i==15)   digitButtons[i]->setStyleSheet("QPushButton {background-color: rgb(208, 206, 186); border: 1px solid rgb(208, 206, 186)} QPushButton:hover {background-color: rgb(230, 229, 219); border: 1px solid rgb(230, 229, 219)} QPushButton:pressed {background-color: rgb(230, 229, 126); border: 1px solid rgb(230, 229, 126)}");
          digitButtons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
          digitButtons[i]->setText(values[i]);
          digitButtons[i]->setFont(QFont("consolas", 9));
          if (i!=3 && i!=7 && i!=11 && i<13)    connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(digits_numbers()));
          else   connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(operations()));
          digitButtons[3]->setCheckable(true);
          buttons->addButton(digitButtons[i], i);
      }
    int pos = 0;

    for (int i=0; i<values.length()/4; i++) {
        for (int j=0; j<4; j++) {
         buttons->button(pos)->setMinimumSize(40, 40);
         grid->addWidget(buttons->button(pos), i, j);
         pos++;
        }
    }
    label_lay->addLayout(clear_lay);
    label_lay->addLayout(grid);

    auto central = new QWidget;
    central ->setStyleSheet("background-color: rgb(15,16,32)");
    central -> setMinimumSize(300, 300);
    central->setLayout(label_lay);
    setCentralWidget(central);
    //connect(digitButtons[0], SIGNAL(clicked()), this, SLOT(digits_numbers()));
    //on_button_clicked(digitButtons);
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString new_label;
    all+=button->text();
    line_1->setText(all);
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    //QString new_label;

    num_first = line_1->text().toDouble();
    button->setChecked(true);
    //all_operations = (line_1->text() + button->text());
    //new_label = (all_operations);
    all+=button->text();
    line_1->setText(all);
    //line_2->setText(QString::number(num_first));
}

/*void MainWindow::on_button_clicked(QPushButton *digitButtons) {
    double labelNumber, num_second;
    int step;
    QString new_label;

    num_second = line_2->text().toDouble();
    step = line_2->text().toInt();

    if(digitButtons[3]->isChecked()){
        labelNumber = num_first + num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        line_2->setText(new_label);
        digitButtons[3]->setChecked(false);
    }
}*/
MainWindow::~MainWindow()
{
}
