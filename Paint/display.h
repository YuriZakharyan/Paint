#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class QLineEdit;

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    void setColor(QColor selectedColor);
    void setBrushSize(int selectedSize);
    void clearAll();
    void pencil();

    QImage getImage();

private:

    //display
    QImage displayImage;
    //Flag to indicate whether we are currently drawing something (used on mouse events)

    int brushSize;
    bool drawingActive;
    bool eventFilter(QObject *obj, QEvent *event);
   // bool drawText;
    QLineEdit* textLn;
    //Latest mouse point
    QPoint latestPoint;
    //Color variable
    QColor currentColor;

};

#endif // CANVASWIDGET_H
