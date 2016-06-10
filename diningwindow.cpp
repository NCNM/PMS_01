#include "diningwindow.h"

DiningWindow::DiningWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiningWindow)
{
    ui->setupUi(this);
    curView = VIEW_NONE;
    ui->pushSearch->setEnabled(false);
    ui->pushButton_viewInmates->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
                    "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
                    "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
                    "BookIn AS Bookin, BookOut AS Bookout FROM INMATE", db);
    ui->tableView->setModel(model);

    curView = VIEW_OFFICER;
    ui->pushSearch->setEnabled(true);
}

DiningWindow::~DiningWindow()
{
    delete ui;
}



void DiningWindow::on_pushButton_viewInmates_clicked(bool checked)
{
    ui->stackedWidget->setCurrentIndex(0);
    QSqlDatabase db = Database::getDatabase();
/*
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("INMATE");
    model->select();
    ui->tableView->setModel(model);
*/

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
                    "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
                    "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
                    "BookIn AS Bookin, BookOut AS Bookout FROM INMATE", db);
    ui->tableView->setModel(model);

    curView = VIEW_INMATE;
    ui->pushSearch->setEnabled(true);
}

void DiningWindow::on_pushButton_viewOfficers_clicked(bool checked)
{
    ui->stackedWidget->setCurrentIndex(0);
    QSqlDatabase db = Database::getDatabase();

    /*QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM OFFICER", db);
    ui->tableView->setModel(model);*/

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM OFFICER", db);
    ui->tableView->setModel(model);

    curView = VIEW_OFFICER;
    ui->pushSearch->setEnabled(true);
}

void DiningWindow::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit->text();
    QString query;
    if (curView == VIEW_OFFICER)
    {
        query = "SELECT * FROM OFFICER WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%'";
    }
    else if (curView == VIEW_INMATE)
    {
        query = "SELECT * FROM INMATE WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%'";
    }
    else
        return;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
}

void DiningWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void DiningWindow::on_pushButton_viewInmates_clicked()
{

}

void DiningWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QString inmateID = index.sibling(row, 0).data().toString();
    InmateInfoWindow * inmateInfo = new InmateInfoWindow;
    emit row_activated(inmateInfo, 0);
}
