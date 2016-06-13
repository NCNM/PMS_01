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
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    QModelIndex index = indexes.at(0);
    QString ID = index.sibling(index.row(), 0).data().toString();
    if (ID[0] != 'I' && ID[1] != 'M')
    {
        QMessageBox::critical(this, "Unable to delete", "No entry selected!");
        return;
    }
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    query.exec("DELETE FROM INMATE WHERE ID = '" + ID + "'");

    query.exec("INSERT INTO LOG (logtime, content) VALUES ("
            "CAST(N'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "' AS Datetime), "
            "N'Record deleted.')");

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
    ui->stackedWidget->setCurrentIndex(0);

    QSqlDatabase db = Database::getDatabase();
    model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS ID, Lastname AS \"Last name\", Midname AS \"Middle name\", Firstname as \"First name\", "
                    "Gender AS Gender, DOB AS DOB, Hair AS \"Hair color\", Eyes AS \"Eye color\", "
                    "Eth AS \"Ethnicity\", Addr AS \"Home address\", Reason AS Reason, Custody AS Custody, "
                    "Availability AS Availability, BookIn AS Bookin, BookOut AS Bookout FROM INMATE WHERE "
                    "Bookin > NOW() AND DATEDIFF(NOW(), BookIn) <= 7", db);

    ui->tableView->setModel(model);
}

void EntryReleaseForm::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QSqlDatabase db = Database::getDatabase();
    model = new QSqlQueryModel;
    model->setQuery("SELECT mon AS Monday, tue AS Tuesday, wed AS Wednesday, "
                    "thu AS Thursday, fri AS Friday, sat AS Saturday, sun AS Sunday "
                    "FROM VISIT_TIMES", db);

    ui->tblVisitTimes->setModel(model);
}

void EntryReleaseForm::on_pushButton_6_clicked()
{
    ui->txtQuery->clear();
}

void EntryReleaseForm::on_tableView_doubleClicked(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
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
    QSqlQuery satan_approves;
    satan_approves.prepare(query);
    satan_approves.exec();
    on_pushButton_update_clicked();
}

void EntryReleaseForm::on_tableView_pressed(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}

void EntryReleaseForm::on_pushButton_9_clicked()
{
    QString query;

    query = "DELETE FROM VISIT_TIMES";
    QSqlQuery satan_approves;
    satan_approves.prepare(query);
    satan_approves.exec();

    QString range;
    range = ui->teStartTime->text() + " - " + ui->teEndTime->text();

    query = "INSERT INTO VISIT_TIMES (static) VALUES ('666')";
    satan_approves.prepare(query);
    satan_approves.exec();

    if (ui->chkMon->isChecked() == true) {
        query = "UPDATE VISIT_TIMES SET mon = '" + range + "' WHERE static = '666'";
        satan_approves.prepare(query);
        satan_approves.exec();
    }
    if (ui->chkTue->isChecked() == true) {
        query = "UPDATE VISIT_TIMES SET tue = '" + range + "' WHERE static = '666'";
        satan_approves.prepare(query);
        satan_approves.exec();
    }
    if (ui->chkWed->isChecked() == true) {
        query = "UPDATE VISIT_TIMES SET wed = '" + range + "' WHERE static = '666'";
        satan_approves.prepare(query);
        satan_approves.exec();
    }
    if (ui->chkThu->isChecked() == true) {
        query = "UPDATE VISIT_TIMES SET thu = '" + range + "' WHERE static = '666'";
        satan_approves.prepare(query);
        satan_approves.exec();
    }
    if (ui->chkFri->isChecked() == true) {
        query = "UPDATE VISIT_TIMES SET fri = '" + range + "' WHERE static = '666'";
        satan_approves.prepare(query);
        satan_approves.exec();
    }
    if (ui->chkSat->isChecked() == true) {
        query = "UPDATE VISIT_TIMES SET sat = '" + range + "' WHERE static = '666'";
        satan_approves.prepare(query);
        satan_approves.exec();
    }
    if (ui->chkSun->isChecked() == true) {
        query = "UPDATE VISIT_TIMES SET sun = '" + range + "' WHERE static = '666'";
        satan_approves.prepare(query);
        satan_approves.exec();
    }
    on_pushButton_19_clicked();
}
