#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QClipboard"

bool flAutoCopy;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(APPLICATION_NAME);

    /* При создании главного окна производим установку начальных параметров
     * из настроек, сохранённых в операционной системе
     * */
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    /* Устанавливаем состояние чекбокса из настроек приложения по заданному ключу.
     * Если ключ не существует, то будет установлен параметр по умолчанию,
     * то есть false
     * */
    ui->lEEndSymb->setText(settings.value(SETTINGS_ENDSYMB, ";").toString());
    ui->lEcountSymb->setText(settings.value(SETTINGS_COUNT, "17").toString());
    //ui->lEcountSymb->setText() = "12";
    flAutoCopy = false;
    ui->autoCopyCB->setChecked(flAutoCopy);
}

MainWindow::~MainWindow()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    /* Сохранение информации о включённости функции сворачивания
     * в трей производится в соответствии с состоянием чекбокса.
     * */
    settings.setValue(SETTINGS_ENDSYMB, ui->lEEndSymb->text());
    settings.setValue(SETTINGS_COUNT, ui->lEcountSymb->text());
    settings.sync();
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString str=ui->textEdit->toPlainText();
    QString charStr;

    QString strHex = str.toLocal8Bit().toHex();
    QString charHex = "{";
    QString endSymb = ui->lEEndSymb->text();
    int16_t countSymb = ui->lEcountSymb->text().toInt();


    if (str.length() > countSymb) {
        countSymb = str.length();
        ui->lEcountSymb->setStyleSheet("QLineEdit { background: rgb(204, 0, 51); selection-background-color: rgb(51, 0 ,51); }");
    } else {
        ui->lEcountSymb->setStyleSheet("QLineEdit { background: rgb(255,255,255); selection-background-color: rgb(102,153,255); }");
    }
    //countSymb += 1;
    for (int i = 0 ; i < countSymb; i++)
    {
        if (i > str.length()) {
            charHex += "0x20, ";
            continue;
        }
        charStr = str[i];
        if ("00" == charStr.toLocal8Bit().toHex()) {
            continue;
        }
        charHex += "0x" + charStr.toLocal8Bit().toHex();
        charHex += ", ";
//        if ((i + 1) != str.length())
//        {
//            charHex += ", ";
//        }
    }
    charHex += "0x00}" + endSymb + " // " + str;

    ui->textBrowser->setText(charHex);

    QClipboard *clipbrd = QGuiApplication::clipboard();
    if (flAutoCopy)
        clipbrd->setText(ui->textBrowser->toPlainText());
}

void MainWindow::on_textEdit_textChanged()
{
    on_pushButton_clicked();
}

void MainWindow::on_copyBtn_clicked()
{
    QClipboard *clipbrd = QGuiApplication::clipboard();
    QString text = ui->textBrowser->toPlainText();
    clipbrd->setText(text);
}

void MainWindow::on_autoCopyCB_stateChanged(int arg1)
{
    if (arg1 == 2)
        flAutoCopy = true;
}

void MainWindow::on_pasteBtn_clicked()
{
    QClipboard *clipbrd = QGuiApplication::clipboard();
    QString text = ui->textBrowser->toPlainText();
    ui->textEdit->setText(clipbrd->text());
    //clipbrd->setText(text);
}
