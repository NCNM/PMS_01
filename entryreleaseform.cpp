#include "entryreleaseform.h"
#include "ui_entryreleaseform.h"
#include "newinmateform.h"
#include <QDebug>
#include <QMessageBox>

EntryReleaseForm::EntryReleaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryReleaseForm)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();
    model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
                    "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
                    "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
                    "Availability AS Availability, BookIn AS Bookin, BookOut AS Bookout FROM INMATE", db);
    ui->tableView->setModel(model);

    ui->pushSearch->setEnabled(true);

    ui->pushButton_update->setChecked(true);
}

EntryReleaseForm::~EntryReleaseForm()
{
    delete ui;
}

void EntryReleaseForm::on_pushButton_3_clicked()
{
    // model->select();
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    QModelIndex index = indexes.at(0);
    QString ID = index.sibling(index.row(), 0).data().toString();
    newinmateform* nif = new newinmateform(0, 1, ID);
    connect(nif, &newinmateform::add_new_inmate, this, &EntryReleaseForm::add_inmate_triggered);
    nif->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    connect(nif, &newinmateform::add_new_inmate, this,
            &EntryReleaseForm::add_inmate_triggered);
    nif->show();
}

void EntryReleaseForm::on_pushButton_2_clicked()
{
    // model->insertRow(model->rowCount());
    newinmateform* nif = new newinmateform(0, 0, 0);
    connect(nif, &newinmateform::add_new_inmate, this, &EntryReleaseForm::add_inmate_triggered);
    nif->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    connect(nif, &newinmateform::add_new_inmate, this,
            &EntryReleaseForm::add_inmate_triggered);
    nif->show();
}

void EntryReleaseForm::on_pushButton_clicked()
{
    //model->removeRow(ui->tableView->currentIndex().row());

    QString ID = ui->tableView->currentIndex().data().toString();

    if (ID[0] != 'I' && ID[1] != 'M')
    {
        QMessageBox::information(this, "Alert", "You must choose the Inmate ID!");
        return;
    }

    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    query.exec("DELETE FROM INMATE WHERE ID = '" + ID + "'");

    QMessageBox::information(this, "Alert", "Success!");

    on_pushButton_update_clicked();
}

void EntryReleaseForm::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit->text();
    QString query;
    query = "SELECT * FROM INMATE WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%'";

    QSqlQueryModel *model2 = new QSqlQueryModel;
    model2->setQuery(query, db);
    ui->tableView->setModel(model2);
}

void EntryReleaseForm::on_pushButton_update_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();
    model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
                    "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
                    "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
                    "Availability AS Availability, BookIn AS Bookin, BookOut AS Bookout FROM INMATE", db);

    ui->tableView->setModel(model);

    ui->pushSearch->setEnabled(true);
}

void EntryReleaseForm::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void EntryReleaseForm::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void EntryReleaseForm::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void EntryReleaseForm::on_pushButton_6_clicked()
{
    ui->txtQuery->clear();
}

void EntryReleaseForm::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString ID = index.sibling(index.row(), 0).data().toString();
    InmateInfoWindow * inmateInfo = new InmateInfoWindow(0, ID, 1);
    emit row_activated(inmateInfo, 0);
}

void EntryReleaseForm::on_pushButton_5_clicked()
{
    QSqlDatabase db = Database::getDatabase();
    QString query;
    query = ui->txtQuery->toPlainText();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
    ui->stackedWidget->setCurrentIndex(0);
}

void EntryReleaseForm::add_inmate_triggered(QString query) {
    QSqlQuery qqq;
    qqq.prepare(query);
    qqq.exec();
    QSqlDatabase db = Database::getDatabase();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
    model->setQuery("SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
                    "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
                    "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
                    "Availability AS Availability, BookIn AS Bookin, BookOut AS Bookout FROM INMATE", db);
    ui->tableView->setModel(model);
    ui->stackedWidget->setCurrentIndex(0);
}
