#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define ORGANIZATION_NAME "RCL"
#define ORGANIZATION_DOMAIN "www.rcl-corp.ru"
#define APPLICATION_NAME "ToAsciiArray"

#define SETTINGS_COUNT   "settings/count"
#define SETTINGS_ENDSYMB "settings/endsymb"

#include <QMainWindow>
#include <QSettings>

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
    void on_pushButton_clicked();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
