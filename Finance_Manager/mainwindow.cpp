#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QMessageBox>

// MainWindow related functions
void MainWindow::set_up_user_combo_box(){
    //setting up combo box to select user
    for(unsigned int i = 1; i <= app_logic.get_main_repository().get_size(); i++){
        string new_item = "";
        new_item += std::to_string(app_logic.get_main_repository().get_user_by_id(i).get_id());
        new_item += " (";
        new_item += app_logic.get_main_repository().get_user_by_id(i).get_name();
        new_item += ")";
        ui->select_by_id_combo_box->addItem(QString::fromStdString(new_item), app_logic.get_main_repository().get_user_by_id(i).get_id());
    }
}


void MainWindow::update_user_data_ui(){
}

// Main Window constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // reading data from csv file
    app_logic.read_from_file();

    // validating account_balance and id
    ui->account_balance_line_edit->setValidator(new QIntValidator(1, 999999999));

    //setting up combo box to select user
    set_up_user_combo_box();
    connect(ui->select_by_id_combo_box,SIGNAL(activated(int)),this,SLOT(on_select_by_id_combo_box_activated(int)));

    // setting placeholders
    ui->user_id_label->setText("no user selected");
    ui->name_line_edit->setPlaceholderText("none");
    ui->account_balance_line_edit->setPlaceholderText("0");

    // connecting buttons
    connect(ui->add_user_button, SIGNAL(released()), this, SLOT(add_user_button_clicked()));
    connect(ui->remove_user_button, SIGNAL(released()), this, SLOT(remove_user_button_clicked()));
    connect(ui->create_purchase_button, SIGNAL(released()), this, SLOT(create_purchase_button_clicked()));

    //setting up purchases table UI
    ui->purchases_table->setColumnCount(2);
    ui->purchases_table->setRowCount(1);
}


// Main Window destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// triggers
void MainWindow::on_actionQuit_triggered()
{
     QApplication::quit();
}


void MainWindow::on_actionSave_triggered()
{
    app_logic.write_to_file();
}


void MainWindow::add_user_button_clicked()
{
    // takes user information from ui and creates a new user

    string _name = ui->name_line_edit->text().toStdString();

    unsigned int _account_balance = 0;
    _account_balance = ui->account_balance_line_edit->text().toInt();

    app_logic.add_user_to_repository(_name, _account_balance);

}


void MainWindow::remove_user_button_clicked()
{
    // removing the currently selected user
    app_logic.remove_user_from_repository(ui->user_id_label->text().toStdString());

}


void MainWindow::on_select_by_id_combo_box_activated(int index)
{
    // moving user data to the UI
    User current_user = app_logic.get_main_repository().get_user_by_id(index+1);
    ui->user_id_label->setText(QString::fromStdString(std::to_string(current_user.get_id())));
    ui->account_balance_line_edit->setText(QString::fromStdString(std::to_string(current_user.get_account_balance())));
    ui->name_line_edit->setText(QString::fromStdString(current_user.get_name()));
}


void MainWindow::create_purchase_button_clicked()
{
    // extracting new item data and creating a purchase for that item
    unsigned int current_user_id = ui->user_id_label->text().toUInt();
    QString new_item_name = ui->item_name_line_edit->text();
    QString new_item_price = ui->item_price_line_edit->text();
    app_logic.get_main_repository().user_purchase_item_by_id(current_user_id, new_item_name.toStdString(), new_item_price.toUInt());

    int current_account_balance = ui->account_balance_line_edit->text().toUInt();
    current_account_balance -= new_item_price.toInt();

    if(current_account_balance < 0){
        QMessageBox::warning(
            this,
            tr("Finance Manager"),
            tr("Account balance not enough.") );
        return;
    }
    ui->account_balance_line_edit->setText(QString::fromStdString(std::to_string(current_account_balance)));

    // updating account balance
    app_logic.get_main_repository().change_user_balance_by_id(current_user_id, current_account_balance);

    // updating UI
    ui->purchases_table->setRowCount(ui->purchases_table->rowCount()+1);
    ui->purchases_table->setItem(ui->purchases_table->rowCount()-2,0, new QTableWidgetItem(new_item_name));
    ui->purchases_table->setItem(ui->purchases_table->rowCount()-2,1, new QTableWidgetItem(new_item_price));

}

void MainWindow::on_actionUndo_triggered()
{
    app_logic.undo();
}


void MainWindow::on_actionRedo_triggered()
{
    app_logic.redo();
}

