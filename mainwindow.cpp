#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFont>
#include <QLabel>

bool waitingForOperand = true;
QString all;
QString pendingAdditiveOperator;
QString pendingMultiplicativeOperator;
double sumSoFar = 0.0;
double factorSoFar = 0.0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QGridLayout *grid = new QGridLayout;
    QVBoxLayout *label_lay = new  QVBoxLayout;
    QHBoxLayout *clear_lay = new  QHBoxLayout;
    line_1 = new QLineEdit("0");
    line_2 = new QLineEdit("0");
    line_buff = new QLineEdit("0");
    line_1->setReadOnly(true);
    line_2->setReadOnly(true);
    QPushButton *clear = new QPushButton(this);
    QPushButton *del = new QPushButton(this);
    connect(clear, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(del, SIGNAL(clicked()), this, SLOT(del()));

    line_1 -> setStyleSheet("QLineEdit {background-color: rgb(242, 244, 243); border: 1px solid rgb(242, 244, 243)}");
    line_2 -> setStyleSheet("QLineEdit {background-color: rgb(127, 124, 136); border: 1px solid rgb(127, 124, 136)}");
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
          if (i!=3 && i!=7 && i!=11 && i<13)    connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(digitClicked()));
          else if (i==3 || i==7) connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(additiveOperatorClicked()));
          else if (i==13) connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(pointClicked()));
          else if (i==14 || i==11) connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(multiplicativeOperatorClicked()));
          else if (i==15) connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(equalClicked()));
          else if (i>15) connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
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
}

void MainWindow::digitClicked()
{
    QPushButton *clickedButton = (QPushButton *)sender();
    all+=clickedButton->text();
    int digitValue = clickedButton->text().toInt();
    if (line_buff->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        line_buff->clear();
        waitingForOperand = false;
    }
    line_buff->setText(line_buff->text() + QString::number(digitValue));
    line_1->setText(all);
}
bool MainWindow::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == "+") {
        sumSoFar += rightOperand;
    } else if (pendingOperator == "-") {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == "*") {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == "/") {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}

int MainWindow::fact(double n)
{
    int f=1, i;
    for(i = 2; i<=n; ++i) {
        f=f*i;
    }
    return f;
}

void MainWindow::unaryOperatorClicked()
{
    QPushButton *clickedButton = (QPushButton *)sender();
    QString clickedOperator = clickedButton->text();
    double operand = line_1->text().toDouble();
    double result = 0.0;

    if (clickedOperator == ("√n")) {
        if (operand < 0.0) {
            line_2->setText(tr("####"));
            return;
        }
        result = sqrt(operand);
    }
    else if (clickedOperator == ("n^2")) {
        result = pow(operand, 2.0);
    }
    else if (clickedOperator == ("n!")) {
        if (operand == 0.0) {
            line_2->setText(tr("####"));
            return;
        }
        result = fact(operand);
    }
    else if (clickedOperator == ("log n")) {
            if (operand == 0.0) {
                line_2->setText(tr("####"));
                return;
            }
            result = log(operand);
        }
    else if (clickedOperator == ("sin n")) {
            result = sin(operand);
        }
    else if (clickedOperator == ("cos n")) {
            result = cos(operand);
        }
    else if (clickedOperator == ("tg n")) {
            if (operand == 0.0) {
                line_2->setText(tr("####"));
                return;
            }
            result = tan(operand);
        }
    else if (clickedOperator == ("ctg n")) {
            if (operand == 0.0) {
                line_2->setText(tr("####"));
                return;
            }
            result = 1/tan(operand);
        }
    line_2->setText(QString::number(result));
    waitingForOperand = true;
}

void MainWindow::additiveOperatorClicked()
 {
     QPushButton *clickedButton = (QPushButton *)sender();
     all+=clickedButton->text();
     QString clickedOperator = clickedButton->text();
     double operand = line_buff->text().toDouble();
     if (!pendingMultiplicativeOperator.isEmpty()) {
         if (!calculate(operand, pendingMultiplicativeOperator)) {
             line_2->setText(tr("####"));
             return;
         }
         line_buff->setText(QString::number(factorSoFar));
         operand = factorSoFar;
         factorSoFar = 0.0;
         pendingMultiplicativeOperator.clear();
     }
     if (!pendingAdditiveOperator.isEmpty()) {
             if (!calculate(operand, pendingAdditiveOperator)) {
                 line_2->setText(tr("####"));
                 return;
             }
     line_2->setText(QString::number(sumSoFar));
     } else {
              sumSoFar = operand;
          }
     pendingAdditiveOperator = clickedOperator;
     waitingForOperand = true;
}

void MainWindow::multiplicativeOperatorClicked()
{
    QPushButton *clickedButton = (QPushButton *)sender();
    all+=clickedButton->text();
    QString clickedOperator = clickedButton->text();
    double operand = line_buff->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            line_2->setText(tr("####"));
            return;
        }
        line_2->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void MainWindow::equalClicked()
{
    double operand = line_buff->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            line_2->setText(tr("####"));
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            line_2->setText(tr("####"));
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    line_2->setText(QString::number(sumSoFar));
    line_1->setText(all);
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void MainWindow::pointClicked()
{
    if (waitingForOperand)
        line_1->setText("0");
    if (!line_1->text().contains(".")){
        line_1->setText(line_1->text() + ("."));
        line_buff->setText(line_buff->text() + ("."));
        all+=".";
    }
    waitingForOperand = false;
}
void MainWindow::del()
{
     if (waitingForOperand)
         return;

     QString text = line_buff->text();
     text.chop(1);
     all.chop(1);
     if (text.isEmpty()) {
         text = "0";
         waitingForOperand = true;
     }
     line_1->setText(text);
     line_buff->setText(text);
}

void MainWindow::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    all.clear();
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    line_1->clear();
    line_2->clear();
    line_buff->clear();
    waitingForOperand = true;
}
MainWindow::~MainWindow()
{
}
