#include "managementwindow.h"
#include "ui_managementwindow.h"

ManagementWindow::ManagementWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagementWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_16->setChecked(true);
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT department AS Department, logtime AS Timestamp, content AS Event FROM LOG", db);
    ui->tableView_2->setModel(model);
}

ManagementWindow::~ManagementWindow()
{
    delete ui;
}

void ManagementWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT department AS Department, logtime AS Timestamp, content AS Event FROM LOG", db);
    ui->tableView_2->setModel(model);
}

void ManagementWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ManagementWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QSqlDatabase db = Database::getDatabase();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
                    "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
                    "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
                    "Availability AS Availability, BookIn AS Bookin, BookOut AS Bookout FROM INMATE", db);
    ui->tableView_3->setModel(model);
    ui->pushSearch->setEnabled(true);
}

void ManagementWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void ManagementWindow::on_tableView_3_doubleClicked(const QModelIndex &index)
{
    QString ID = index.sibling(index.row(), 0).data().toString();
    InmateInfoWindow * inmateInfo = new InmateInfoWindow(0, ID, 1);
    emit row_activated(inmateInfo, 0);
}

void ManagementWindow::on_tableView_3_pressed(const QModelIndex &index)
{
    ui->tableView_3->selectRow(index.row());
}

void ManagementWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QSqlDatabase db = Database::getDatabase();
    QSqlQueryModel *model = new QSqlQueryModel;
    ui->pushSearch->setEnabled(true);
    if (arg1 == "All") {
        model->setQuery("SELECT department AS Department, logtime AS Timestamp, content AS Event FROM LOG", db);
        ui->tableView_2->setModel(model);
    }
    else {
            model->setQuery("SELECT department AS Department, logtime AS Timestamp, content AS Event FROM LOG "
                            "WHERE department = N'" + arg1 + "'", db);
            qDebug() << "SELECT department AS Department, logtime AS Timestamp, content AS Event FROM LOG "
                        "WHERE department = N'" + arg1 + "'";
            ui->tableView_2->setModel(model);
    }
}

void ManagementWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    ui->tableView_2->selectRow(index.row());
}

void ManagementWindow::on_tableView_2_pressed(const QModelIndex &index)
{
    ui->tableView_2->selectRow(index.row());
}

void ManagementWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    ui->tableView_3->selectRow(index.row());
}

void ManagementWindow::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit_2->text();
    QString query;
    query = "SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
            "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
            "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
            "Availability AS Availability, BookIn AS Bookin, BookOut AS Bookout "
            "FROM INMATE WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%' "
            "OR ID LIKE '%" + name + "%'";

    QSqlQueryModel *model2 = new QSqlQueryModel;
    model2->setQuery(query, db);
    ui->tableView_3->setModel(model2);
}

void ManagementWindow::on_lineEdit_2_returnPressed()
{
    on_pushSearch_clicked();
}
