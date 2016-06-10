#include <QFileDialog>
#include <QMessageBox>
#include "newinmateform.h"
#include "ui_newinmateform.h"

newinmateform::newinmateform(QWidget *parent, int purpose, QString ID) :
    QWidget(parent),
    ui(new Ui::newinmateform)
{
    ui->setupUi(this);

    workingID = ID;
    ui->lbl_Filename->setText("");
    if (purpose == 0)
    {
        ui->pushButton_2->setText("Add entry");
        ui->pushButton_2->setIcon(QIcon(":/images/add_new.png"));
        ui->lblTitle->setText("Add new inmate");
        ui->lblSubtitle->setText("Input the detailed information of the new inmate, then click Add entry");
    }
    else if (purpose == 1)
    {
        ui->pushButton_2->setText("Update");
        ui->pushButton_2->setIcon(QIcon(":/images/check.png"));
        ui->lblTitle->setText("Update record");
        ui->lblSubtitle->setText("Input updated information for the record, then click Update");
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
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image File", QDir::currentPath());
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
    if (ui->pushButton_2->text() == "Add entry")
    {
        query = "INSERT INMATE ('ID', 'Photo', 'Lastname', 'Midname', 'Firstname', "
                "'Gender', 'DOB', 'Hair', 'Eyes', 'Eth', 'Addr', 'Reason', 'Custody', 'Availability', 'BookIn', "
                "'BookOut') VALUES (N'" + ui->txtID->text() + ", N'" + ui->lbl_Filename->text() + "', N'" + ui->txtLastName->text() +"', "
                "N'" + ui->txtMidName->text() +"', N'" + ui->txtFirstName->text() +"', N'" + ui->cmbGender->currentText() +"', "
                "CAST(N'" + ui->deDOB->text() +"' AS Date), N'" + ui->txtHair->text() +"', N'" + ui->txtEyes->text() +"', "
                "N'" + ui->txtEth->text() +"', N'" + ui->txtAddress->text() +"', N'" + ui->txtReason->text() +"', "
                "N'" + ui->txtCustody->text() +"', N'" + ui->cmbAvailable->currentText() + "' ,CAST(N'" + ui->deBookin->text() + "' AS Date), "
                "CAST(N'" + ui->deBookout->text() + "' AS Date));";
    }
    else if (ui->pushButton_2->text() == "Update")
    {
        query = "UPDATE INMATE"
                "SET ID=N'" + ui->txtID->text() + ", Photo=N'" + ui->lbl_Filename->text() + "', Lastname=N'" + ui->txtLastName->text() +"', "
                "Midname=N'" + ui->txtMidName->text() +"', Firstname=N'" + ui->txtFirstName->text() +"', Gender=N'" + ui->cmbGender->currentText() +"', "
                "DOB=CAST(N'" + ui->deDOB->text() +"' AS Date), Hair=N'" + ui->txtHair->text() +"', Eyes=N'" + ui->txtEyes->text() +"', "
                "Eth=N'" + ui->txtEth->text() +"', Addr=N'" + ui->txtAddress->text() +"', Reason=N'" + ui->txtReason->text() +"', "
                "Custody=N'" + ui->txtCustody->text() + "', Availability=N'" + ui->cmbAvailable->currentText() + "', Bookin=CAST(N'" + ui->deBookin->text() +
                "' AS Date), Bookout=CAST(N'" + ui->deBookout->text() + "' AS Date) WHERE ID=N'" + workingID + "'";
    }
    emit add_new_inmate(query);
    this->close();
}
