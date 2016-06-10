#include <QFileDialog>
#include <QMessageBox>
#include "newinmateform.h"
#include "ui_newinmateform.h"

newinmateform::newinmateform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newinmateform)
{
    ui->setupUi(this);
    ui->lbl_Filename->setText("");
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

}
