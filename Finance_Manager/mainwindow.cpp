#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QMessageBox>

// MainWindow related functions
void MainWindow::set_up_user_combo_box(){
    //setting up combo box to select user
    for(User current_user : app_logic.get_main_repository().get_rep()){
        string new_item = "";
        new_item += std::to_string(current_user.get_id());
        new_item += " (";
        new_item += current_user.get_name();
        new_item += ")";
        ui->select_by_id_combo_box->addItem(QString::fromStdString(new_item), current_user.get_id());
    }
}

void MainWindow::reset_combo_box(){
    // reconstructing combo box in order to have all users
    ui->select_by_id_combo_box->clear();
    if(app_logic.get_main_repository().get_rep().size() == 0){
        return;
    }
    set_up_user_combo_box();
}

// Main Window constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setting window icon and title
    setWindowIcon(QIcon(":/images/images/accounting.png"));
    setWindowTitle("Finance Manager");

    // reading data from csv file
    app_logic.read_from_file();

    // validating account_balance and id
    ui->account_balance_line_edit->setValidator(new QIntValidator(1, 999999999));
    ui->item_price_line_edit->setValidator(new QIntValidator(1, 999999999));

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
    connect(ui->update_user_button, SIGNAL(released()), this, SLOT(update_user_button_clicked()));

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


    if(ui->name_line_edit->text().isEmpty() || ui->account_balance_line_edit->text().isEmpty()){
        QMessageBox::warning(
            this,
            tr("Finance Manager"),
            tr("Please set a name and account balance for the new user.") );
        return;
    }

    string _name = ui->name_line_edit->text().toStdString();

    unsigned int _account_balance = 0;
    _account_balance = ui->account_balance_line_edit->text().toInt();

    app_logic.add_user_to_repository(_name, _account_balance);
    reset_combo_box();
}


void MainWindow::remove_user_button_clicked()
{
    // removing the currently selected user

    if(ui->user_id_label->text() == "no user selected"){
    QMessageBox::warning(
        this,
        tr("Finance Manager"),
        tr("No user selected.") );
        return;
    }
    else if (app_logic.get_main_repository().get_rep().size() == 0 ||
             app_logic.get_main_repository().is_user_in_repository(ui->user_id_label->text().toUInt() == false)
             ){
        QMessageBox::warning(
            this,
            tr("Finance Manager"),
            tr("User not found.") );
            return ;
    }


    app_logic.remove_user_from_repository(ui->user_id_label->text().toStdString());
    reset_combo_box();
}


void MainWindow::on_select_by_id_combo_box_activated(int index)
{
    // moving user data to the UI
    User current_user = app_logic.get_main_repository().get_user_by_id(index);
    ui->user_id_label->setText(QString::fromStdString(std::to_string(current_user.get_id())));
    ui->account_balance_line_edit->setText(QString::fromStdString(std::to_string(current_user.get_account_balance())));
    ui->name_line_edit->setText(QString::fromStdString(current_user.get_name()));

    // updating UI
    for(auto const& [key, val] : app_logic.get_main_repository().get_user_by_id(index).get_purchased_price()){
        ui->purchases_table->setRowCount(ui->purchases_table->rowCount()+1);
        ui->purchases_table->setItem(ui->purchases_table->rowCount()-2,0, new QTableWidgetItem(QString::fromStdString(key)));
        ui->purchases_table->setItem(ui->purchases_table->rowCount()-2,1, new QTableWidgetItem(val));
    }

}


void MainWindow::create_purchase_button_clicked()
{
    // extracting new item data and creating a purchase for that item
    if(ui->user_id_label->text() == "no user selected"){
    QMessageBox::warning(
        this,
        tr("Finance Manager"),
        tr("No user selected.") );
        return;
    }
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
    else if(new_item_price.isEmpty()){
        QMessageBox::warning(
            this,
            tr("Finance Manager"),
            tr("Please set a price for the purchase.") );
        return;
    }
    else if(new_item_name.isEmpty()){
        QMessageBox::warning(
            this,
            tr("Finance Manager"),
            tr("Please set a name for the purchased item.") );
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


void MainWindow::update_user_button_clicked()
{
    // updating user based on current data from UI
    unsigned int _id = ui->user_id_label->text().toUInt();
 //   for(int i = 1; i < ui->purchases_table->rowCount(); i++){
 //       std::pair<string, int> current_purchase;
  //      current_purchase.first = ui->purchases_table->item(i, 0)->text().toStdString();
    //    current_purchase.second = ui->purchases_table->item(i, 1)->text().toInt();
   //     app_logic.update_user_in_repository(_id, current_purchase);
   // }
    app_logic.set_name_by_id(_id,  ui->item_name_line_edit->text().toStdString());
    app_logic.set_balance_by_id(_id, ui->account_balance_line_edit->text().toUInt());
}

