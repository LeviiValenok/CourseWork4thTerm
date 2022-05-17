#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include <QTableWidget>
#include <QString>
int numberOfDirectories = 0;
int numberOfFiles = 0;
struct passwd *user = NULL;
string *directoriesArray;
string *filesArray;
int depth = 0;
//using namespace std;
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    directoriesArray = new string[1];
    filesArray = new string[1];
    startPage(directoriesArray, filesArray, numberOfDirectories, numberOfFiles);
//    QTableWidget *tableWidget = new QTableWidget(this);
//    tableWidget->setRowCount(numberOfDirectories+numberOfFiles+1);
//    tableWidget->setColumnCount(2);
//    QTableWidgetItem *newItem = new QTableWidgetItem(.arg(1*1));
//    tableWidget->setItem(1,1, newItem);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(numberOfDirectories+numberOfFiles+1);
    ui->tableWidget->setColumnWidth(0, 400);
   for(int ridx = 0;ridx< numberOfDirectories ;ridx++){
            QString qstr = QString::fromStdString(directoriesArray[ridx]);
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(qstr);
            ui->tableWidget->setItem(ridx,0, item);

    }

}



MainWindow::~MainWindow() {
    delete ui;
}

