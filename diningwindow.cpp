#include "diningwindow.h"

DiningWindow::DiningWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiningWindow)
{
    ui->setupUi(this);
    curView = VIEW_NONE;
    ui->pushSearch->setEnabled(false);
    ui->pushButton_Menu->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    on_pushButton_Menu_clicked();
    curView = VIEW_MENU;
    ui->pushSearch->setEnabled(true);
}

DiningWindow::~DiningWindow()
{
    delete ui;
}

void DiningWindow::on_pushSearch_clicked()
{
    QSqlDatabase db = Database::getDatabase();

    QString name = ui->lineEdit->text();
    QString query;
    if (curView == VIEW_OFFICER)
    {
        query = "SELECT * FROM OFFICER WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%' "
                "OR ID LIKE '%" + name + "%'";
    }
    else if (curView == VIEW_INMATE)
    {
        query = "SELECT ID AS 'ID', Lastname AS 'Last name', Midname AS 'Middle name', Firstname as 'First name', "
                "Gender AS 'Gender', DOB AS 'DOB', Hair AS 'Hair color', Eyes AS 'Eye color', "
                "Eth AS 'Ethnicity', Addr AS 'Home address', Reason AS 'Reason', Custody AS 'Custody', "
                "Availability AS 'Availability', BookIn AS 'Bookin', BookOut AS 'Bookout' "
                "FROM INMATE WHERE Firstname LIKE '%" + name + "%' OR Midname LIKE '%" + name + "%' OR Lastname LIKE '%" + name + "%' "
                "OR ID LIKE '%" + name + "%'";
    }
    else if (curView == VIEW_MENU)
    {
        query = "SELECT ID AS 'ID', _Date AS 'Date', Breakfast as 'Breakfast', "
                "Lunch AS 'Lunch', Dinner AS 'Dinner', Subject AS 'Subject' FROM DINING "
                "WHERE ID LIKE '%" + name + "%'";
    }
    else
        return;
    qDebug() << query;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void DiningWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void DiningWindow::on_pushButton_viewInmates_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS 'ID', Lastname AS 'Last name', Midname AS 'Middle name', Firstname as 'First name', "
                    "Gender AS 'Gender', DOB AS 'DOB', Hair AS 'Hair color', Eyes AS 'Eye color', "
                    "Eth AS 'Ethnicity', Addr AS 'Home address', Reason AS 'Reason', Custody AS 'Custody', "
                    "Availability AS 'Availability', BookIn AS 'Bookin', BookOut AS 'Bookout' FROM INMATE", db);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    curView = VIEW_INMATE;
    ui->pushSearch->setEnabled(true);
    ui->pushButton_Modify->hide();
    ui->pushButton_Add->hide();
    ui->Delete->hide();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
}

void DiningWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    /*QString ID = index.sibling(index.row(), 0).data().toString();
    InmateInfoWindow * inmateInfo = new InmateInfoWindow(0, ID, curView);
    emit row_activated(inmateInfo, 0);*/
}

void DiningWindow::on_pushButton_4_clicked()
{
    QSqlDatabase db = Database::getDatabase();
    QString query;
    query = ui->txtQuery->toPlainText();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query, db);
    ui->tableView->setModel(model);
    ui->stackedWidget->setCurrentIndex(0);
}

void DiningWindow::on_pushButton_Add_clicked()
{
    newmenuform * menu = new newmenuform(0, 0);
    connect(menu, &newmenuform::exec_query, this, &DiningWindow::exec_query);
    menu->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    menu->show();
}

void DiningWindow::on_pushButton_Modify_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.isEmpty())
        return;
    QModelIndex index = indexes.at(0);
    QString ID = index.sibling(index.row(), 0).data().toString();

    newmenuform * menu = new newmenuform(0, 1, ID);
    connect(menu, &newmenuform::exec_query, this, &DiningWindow::exec_query);
    menu->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    menu->show();
}

void DiningWindow::exec_query(QString Squery)
{
    qDebug() << Squery;
    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    query.exec(Squery);

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS 'ID', _Date AS 'Date', Breakfast as 'Breakfast', "
                    "Lunch AS 'Lunch', Dinner AS 'Dinner', Subject AS 'Subject' FROM DINING", db);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->stackedWidget->setCurrentIndex(0);

    QSqlQuery satan_approves(db);
    QString log = "INSERT INTO LOG (department, logtime, content) VALUES ('Dining', "
            "CAST(N'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "' AS Datetime), "
            "N'Record changed.')";

    emit send_status("Record changed.");
}

void DiningWindow::on_pushButton_Menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS 'ID', _Date AS 'Date', Breakfast as 'Breakfast', "
                    "Lunch AS 'Lunch', Dinner AS 'Dinner', Subject AS 'Subject' FROM DINING", db);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    curView = VIEW_MENU;
    ui->pushSearch->setEnabled(true);
    ui->pushButton_Modify->show();
    ui->pushButton_Add->show();
    ui->Delete->show();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
}

void DiningWindow::on_Delete_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.isEmpty())
        return;
    QModelIndex index = indexes.at(0);
    QString ID = index.sibling(index.row(), 0).data().toString();

    QSqlDatabase db = Database::getDatabase();
    QSqlQuery query(db);
    QString Squery = "DELETE FROM DINING WHERE ID = '" + ID + "'";
    query.exec(Squery);

    query.exec("INSERT INTO LOG (department, logtime, content) VALUES ('Dining', "
            "CAST(N'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "' AS Datetime), "
            "N'Record deleted.')");

    emit send_status("Record deleted.");

    on_pushButton_Menu_clicked();
}

void DiningWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}

void DiningWindow::on_tableView_pressed(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}

void DiningWindow::on_lineEdit_returnPressed()
{
    on_pushSearch_clicked();
}

void DiningWindow::on_pushButton_viewOfficers_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    QSqlDatabase db = Database::getDatabase();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ID AS 'ID', Lastname AS 'Last name', Midname AS 'Middle name', Firstname as 'First name', "
                    "Gender AS 'Gender', DOB AS 'DOB', Addr AS 'Address', Phone AS 'Phone', Department AS 'Department' "
                    "FROM OFFICER", db);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->pushSearch->setEnabled(true);
    ui->pushButton_Modify->hide();
    ui->pushButton_Add->hide();
    ui->Delete->hide();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    curView = VIEW_OFFICER;
}
