#include "display.h"
#include <QToolTip>
#include <QLineEdit>
#include <mainwindow.h>
#include <QCoreApplication>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
    , brushSize(1)
    , drawingActive(false)
{
    //Set up image
    qApp->installEventFilter(this);

    displayImage = QImage(this->size(), QImage::Format_RGB32);

    displayImage.fill(Qt::white);
    currentColor = Qt::black;

    textLn = new QLineEdit(this);
    textLn->setMaxLength(50);
    textLn->setHidden(true);
    textLn->setDisabled(true);
    textLn->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(233, 99, 0); }");
}

void CanvasWidget::setColor(QColor selectedColor) {
    currentColor = selectedColor;
}

void CanvasWidget::setBrushSize(int selectedSize) {
    brushSize = selectedSize;
}

void CanvasWidget::clearAll()
{
    displayImage = QImage(this->size(), QImage::Format_RGB32);
    displayImage.fill(Qt::white);
    this->update();
}

//Mouse event methods
void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    //Check if the button mouse that was clicked was the left one
    if (event->button() == Qt::LeftButton)
    {
        //Save last mouse point
        latestPoint = event->pos();

        if (!drawText) {
            textLn->setVisible(false);
            textLn->setEnabled(false);
            drawingActive = true;
        }
        else {
          textLn->setVisible(true);
          textLn->setEnabled(true);
          textLn->setFocus();
          textLn->move(latestPoint.x(), latestPoint.y());
        }
    }
}
void CanvasWidget::pencil(){
    brushSize = 1;
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    //Check again if the left mouse button was clicked and whether we are drawing something
    if ((event->buttons() & Qt::LeftButton) && drawingActive)
    {
        //Creating new painter
        QPainter painter(&displayImage);

        painter.setPen(QPen(currentColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        //Draw line
        painter.drawLine(latestPoint, event->pos());

        latestPoint = event->pos();

        this->update();
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drawingActive = false;
    }
}

//Draw method
void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter canvasPainter(this);
    canvasPainter.drawImage(this->rect(), displayImage, displayImage.rect());

}

//Resize function
void CanvasWidget::resizeEvent(QResizeEvent *event)
{
    //On resize delete everything (not an optimal solution to be true...)
    displayImage = QImage(this->size(), QImage::Format_RGB32);
    displayImage.fill(Qt::white);
}


QImage CanvasWidget::getImage()
{
    return displayImage;
}

bool CanvasWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == textLn && drawText && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return)
        {
            QPainter painter(&displayImage);
            //Set parameters according to settings (hard-coded for now)
            painter.setPen(QPen(currentColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            QRectF txt(latestPoint.x(), latestPoint.y(), 150, 150);
            painter.drawText(txt, textLn->text());

            this->update();
            textLn->clear();
            textLn->setVisible(false);
            textLn->setDisabled(true);
        }
    }
}
