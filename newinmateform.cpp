#include "newinmateform.h"
#include "ui_newinmateform.h"


newinmateform::newinmateform(QWidget *parent, int n_mode, QString ID) :
    QWidget(parent),
    ui(new Ui::newinmateform)
{
    ui->setupUi(this);

    mode = n_mode;
    workingID = ID;

    ui->lbl_Filename->setText("");
    if (mode == 0)
    {
        ui->pushButton_2->setText("Add entry");
        ui->pushButton_2->setIcon(QIcon(":/images/add_new.png"));
        ui->header->setStyleSheet("QWidget #header { background-color: rgb(255, 255, 255);"
                                  "background-image: url(:/images/add_new_header.png);"
                                  "}");
    }
    else if (mode == 1)
    {
        ui->pushButton_2->setText("Save");
        ui->pushButton_2->setIcon(QIcon(":/images/save_data.png"));
        ui->header->setStyleSheet("QWidget #header { background-color: rgb(255, 255, 255);"
                                  "background-image: url(:/images/update_header.png);"
                                  "}");
        QSqlDatabase db = Database::getDatabase();
        QString query;
        model = new QSqlQueryModel;
        query = "SELECT * FROM INMATE WHERE ID = '" + ID + "'";
        model->setQuery(query, db);
        ui->txtID->setText(workingID);
        ui->txtID->setReadOnly(1);
        ui->txtFirstName->setText((model->data(model->index(0, 2)).toString()));
        ui->txtMidName->setText((model->data(model->index(0, 3)).toString()));
        ui->txtLastName->setText((model->data(model->index(0, 4)).toString()));
        ui->cmbGender->setCurrentText((model->data(model->index(0, 5)).toString()));
        QDate tmpdate = QDate::fromString((model->data(model->index(0, 6))).toString(), "yyyy-M-dd");
        ui->deDOB->setDate(tmpdate);
        ui->txtHair->setText((model->data(model->index(0, 7)).toString()));
        ui->txtEyes->setText((model->data(model->index(0, 8)).toString()));
        ui->txtEth->setText((model->data(model->index(0, 9)).toString()));
        ui->txtAddress->setText((model->data(model->index(0, 10)).toString()));
        ui->txtReason->setText((model->data(model->index(0, 11)).toString()));
        ui->txtCustody->setText((model->data(model->index(0, 12)).toString()));
        ui->cmbAvailable->setCurrentText(model->data(model->index(0, 13)).toString());
        QDateTime tmpdatetime;
        tmpdatetime = QDateTime::fromString((model->data(model->index(0, 14))).toString(), "yyyy-MM-ddTHH:mm:ss");
        ui->deBookin->setDateTime(tmpdatetime);
        tmpdatetime = QDateTime::fromString((model->data(model->index(0, 15))).toString(), "yyyy-MM-ddTHH:mm:ss");
        ui->deBookout->setDateTime(tmpdatetime);
    }
}

newinmateform::~newinmateform()
{
    delete ui;
}

void newinmateform::on_pushButton_clicked()
{
    this->close();
}

void newinmateform::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image File",
    QDir::homePath());
       if(!fileName.isEmpty())
       {
           QImage image(fileName);

           if(image.isNull())
           {
               QMessageBox::critical(this, "Error", "Failed to display image!");
               // return;
           }
           QGraphicsScene* scene = new QGraphicsScene();
           QPixmap* item = new QPixmap(QPixmap::fromImage(image));
           scene->addPixmap(*item);
           ui->gv_Photo->setScene(scene);
           ui->gv_Photo->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
           ui->lbl_Filename->setText(fileName);
       }
}

void newinmateform::on_pushButton_2_clicked()
{
    QString query;
    if (mode == 0)
    {
        query = "INSERT INTO INMATE (`ID`, `Photo`, `Lastname`, `Midname`, `Firstname`, "
                "`Gender`, `DOB`, `Hair`, `Eyes`, `Eth`, `Addr`, `Reason`, `Custody`, `Availability`, `BookIn`, "
                "`BookOut`) VALUES (N'" + ui->txtID->text() + "', N'" + ui->lbl_Filename->text() + "', N'" + ui->txtLastName->text() +"', "
                "N'" + ui->txtMidName->text() +"', N'" + ui->txtFirstName->text() +"', N'" + ui->cmbGender->currentText() +"', "
                "CAST(N'" + ui->deDOB->text() +"' AS Date), N'" + ui->txtHair->text() +"', N'" + ui->txtEyes->text() +"', "
                "N'" + ui->txtEth->text() +"', N'" + ui->txtAddress->text() +"', N'" + ui->txtReason->text() +"', "
                "N'" + ui->txtCustody->text() +"', N'" + ui->cmbAvailable->currentText() + "' ,CAST(N'" + ui->deBookin->text() + "' AS Datetime), "
                "CAST(N'" + ui->deBookout->text() + "' AS Datetime));";
        //qDebug() << query;
    }
    else if (mode == 1)
    {
        query = "UPDATE INMATE "
                "SET `ID` = N'" + ui->txtID->text() + "', `Photo` = N'" + ui->lbl_Filename->text() + "', `Lastname` = N'" + ui->txtLastName->text() +"', "
                "`Midname` = N'" + ui->txtMidName->text() +"', `Firstname` = N'" + ui->txtFirstName->text() +"', `Gender` = N'" + ui->cmbGender->currentText() +"', "
                "`DOB` = CAST(N'" + ui->deDOB->text() +"' AS Date), `Hair` = N'" + ui->txtHair->text() +"', `Eyes` = N'" + ui->txtEyes->text() +"', "
                "`Eth` = N'" + ui->txtEth->text() +"', `Addr` = N'" + ui->txtAddress->text() +"', `Reason` = N'" + ui->txtReason->text() +"', "
                "`Custody` = N'" + ui->txtCustody->text() + "', `Availability` = N'" + ui->cmbAvailable->currentText() + "', `Bookin` = CAST(N'" + ui->deBookin->text() +
                "' AS Datetime), `Bookout` = CAST(N'" + ui->deBookout->text() + "' AS Datetime) "
                "WHERE `ID` = N'" + workingID + "';";
    }
    emit add_new_inmate(query);
    this->close();
}

void newinmateform::showEvent(QShowEvent *) {
    if (mode == 1) {
        QString imagepath = model->data(model->index(0, 1)).toString();
        QImage image(imagepath);
        if(image.isNull());
        else {
            QGraphicsScene* scene = new QGraphicsScene();
            QPixmap* item = new QPixmap(QPixmap::fromImage(image));
            scene->addPixmap(*item);
            ui->gv_Photo->setScene(scene);
            ui->gv_Photo->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
            ui->lbl_Filename->setText(imagepath);
        }
    }
}
