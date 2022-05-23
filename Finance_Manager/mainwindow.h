#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Logic.h"

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

    void set_up_user_combo_box();

    void reset_combo_box();

    // triggers
    void on_actionQuit_triggered();

    void on_actionSave_triggered();

    void add_user_button_clicked();

    void remove_user_button_clicked();

    void on_select_by_id_combo_box_activated(int index);

    void create_purchase_button_clicked();


    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void update_user_button_clicked();

private:
    Ui::MainWindow *ui;

    Logic app_logic;

};
#endif // MAINWINDOW_H
