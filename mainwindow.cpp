#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
     this->setWindowTitle("TextPad by Gaurav Yadav");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentfile.clear();
    ui->plainTextEdit->setPlainText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName((this));
    QFile file(filename);
    currentfile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "warning","Cannot Open File: " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString Text = in.readAll();
    ui->plainTextEdit->setPlainText(Text);
    file.close();

}

void MainWindow::on_actionExit_triggered()
{
QApplication::quit();
}

void MainWindow::on_actionCopy_All_triggered()
{
ui->plainTextEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
ui->plainTextEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
ui->plainTextEdit->cut();
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this);
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "warning","Cannot Save File: " + file.errorString());
        return;
    }
    currentfile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString Text =  ui->plainTextEdit->toPlainText();
     out<<Text;
    file.close();
}
