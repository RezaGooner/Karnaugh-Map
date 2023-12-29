#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isSave ;


protected:
    void closeEvent(QCloseEvent *event) override
    {
        if (!isSave) {
            QMessageBox msgBox;
            msgBox.setFont(QFont("B Kamran", 12));
            msgBox.setWindowTitle("Exit");
            msgBox.setText("Do you want to Exit without saving?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            msgBox.setButtonText(QMessageBox::Yes, "Exit without saving");
            msgBox.setButtonText(QMessageBox::No, "Stay");
            msgBox.setButtonText(QMessageBox::Cancel, "Save");

            int ret = msgBox.exec();

            if (ret == QMessageBox::Yes) {
                event->accept();
            } else if (ret == QMessageBox::No) {
                event->ignore();
            } else if (ret == QMessageBox::Cancel) {
                on_saveButton_clicked();
                if (isSave)
                    event->accept();
            }

        } else {
            QMessageBox msgBox;
            msgBox.setFont(QFont("B Kamran" , 12));
            msgBox.setWindowTitle("Exit");
            msgBox.setText("Do you want to Exit?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, "Exit");
            msgBox.setButtonText(QMessageBox::No, "Stay");

            int ret = msgBox.exec();
            if (ret == QMessageBox::Yes) {
                event->accept();
            } else {
                event->ignore();
            }
        }
    }



private slots:

    void on_minButton_clicked();

    void on_groupButton_clicked();

    void paintEvent(QPaintEvent *event);

    void on_allSelectButton_clicked();

    void on_saveButton_clicked();

    void on_dcButton_clicked();

    void on_sopposButton_clicked();

    void on_truetableButton_clicked();

    void on_abcde_stateChanged(int arg1);

    void on_Abcde_stateChanged(int arg1);

    void on_abcdE_stateChanged(int arg1);

    void on_abcDE_stateChanged(int arg1);

    void on_abcDe_stateChanged(int arg1);

    void on_abCde_stateChanged(int arg1);

    void on_abCdE_stateChanged(int arg1);

    void on_abCDE_stateChanged(int arg1);

    void on_abCDe_stateChanged(int arg1);

    void on_aBCde_stateChanged(int arg1);

    void on_aBCdE_stateChanged(int arg1);

    void on_aBCDE_stateChanged(int arg1);

    void on_aBCDe_stateChanged(int arg1);

    void on_aBcde_stateChanged(int arg1);

    void on_aBcdE_stateChanged(int arg1);

    void on_aBcDE_stateChanged(int arg1);

    void on_aBcDe_stateChanged(int arg1);

    void on_AbcdE_stateChanged(int arg1);

    void on_AbcDE_stateChanged(int arg1);

    void on_AbcDe_stateChanged(int arg1);

    void on_AbCde_stateChanged(int arg1);

    void on_AbCdE_stateChanged(int arg1);

    void on_AbCDE_stateChanged(int arg1);

    void on_AbCDe_stateChanged(int arg1);

    void on_ABCde_stateChanged(int arg1);

    void on_ABCdE_stateChanged(int arg1);

    void on_ABCDE_stateChanged(int arg1);

    void on_ABCDe_stateChanged(int arg1);

    void on_ABcde_stateChanged(int arg1);

    void on_ABcdE_stateChanged(int arg1);

    void on_ABcDE_stateChanged(int arg1);

    void on_ABcDe_stateChanged(int arg1);

    void on_changeVariableButton_clicked();

    void on_indexButton_clicked();

    void on_dial_sliderMoved(int position);

private:
    Ui::MainWindow *ui;




};
#endif
