#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>

bool drawText = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set number button group listener
    ui->colorSelectGroup->connect(ui->colorSelectGroup, SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(colorSelectGroup_clicked(QAbstractButton*)));
    //Set default brush size label
    ui->brushSize_label->setText("1");
    //Set default color to color indicator
    ui->colorIndicator->setStyleSheet("background-color: black");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//============================================================
//Color method
//============================================================
void MainWindow::colorSelectGroup_clicked(QAbstractButton* button)
{

    QString buttonName = button->objectName();

    //Default color - black
    QColor selectedColor;

    //Set color according to button name
    if (buttonName == "color_red") {
        selectedColor = Qt::red;
        ui->colorIndicator->setStyleSheet("background-color: red");
    }
    else if (buttonName == "color_blue") {
        selectedColor = Qt::blue;
        ui->colorIndicator->setStyleSheet("background-color: blue");
    }
    else if (buttonName == "color_green") {
        selectedColor = Qt::darkGreen;
        ui->colorIndicator->setStyleSheet("background-color: green");
    }
    else if (buttonName == "color_yellow") {
        selectedColor = Qt::yellow;
        ui->colorIndicator->setStyleSheet("background-color: yellow");
    }
    else if (buttonName == "color_grey") {
        selectedColor = Qt::gray;
        ui->colorIndicator->setStyleSheet("background-color: gray");
    }
    else if (buttonName == "color_white") {
        selectedColor = Qt::white;
        ui->colorIndicator->setStyleSheet("background-color: white");
    }
    else {
        //Default color
        selectedColor = Qt::black;
        ui->colorIndicator->setStyleSheet("background-color: black");
    }
    //Call appropriate method
    ui->display->setColor(selectedColor);

}

//============================================================
//Slider methods
//============================================================
void MainWindow::on_brushSize_slider_sliderReleased()
{
    //Call appropriate method to set brush size
    ui->display->setBrushSize(ui->brushSize_slider->value());
}

void MainWindow::on_brushSize_slider_sliderMoved(int position)
{
    ui->brushSize_label->setText(QString::number(position));
}

void MainWindow::on_brushSize_slider_valueChanged(int value)
{
    ui->brushSize_label->setText(QString::number(value));
    ui->display->setBrushSize(value);

}


void MainWindow::on_clearAll_clicked()
{
    ui->display->clearAll();
}
void MainWindow::on_clearPen_clicked(){
    QColor newcolor = QColor(Qt::white);
    ui->display->setColor(newcolor);
}
void MainWindow::on_color_custom_clicked()
{
    //Open custom color dialog
    QColor customColor = QColorDialog::getColor(Qt::white, this, QString("Select a draw color"), QColorDialog::ShowAlphaChannel);
    //Update indicator and brush
    ui->colorIndicator->setStyleSheet("background-color: " + customColor.name());
    ui->display->setColor(customColor);
}

void MainWindow::on_saveButton_clicked()
{
    QImage canvasImage = ui->display->getImage();
    //Get filename path
    QString filePath = QFileDialog::getSaveFileName(this, "SaveImage", "", "PNG (*.png);;JPEG (*.jpg *.jpeg)");

    if (filePath == "") {
        return;
    }
    //Save image
    canvasImage.save(filePath);
}

void MainWindow::on_pencilButton_clicked()
{
    on_brushSize_slider_sliderMoved(1);
    on_brushSize_slider_valueChanged(1);
}

void MainWindow::on_textButton_toggled(bool checked)
{
    if (checked) {
        drawText = true;
    }
    else {
        drawText = false;
    }
}
