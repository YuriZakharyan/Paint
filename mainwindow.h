#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QColorDialog>
#include <QFileDialog>
#include "display.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void colorSelectGroup_clicked(QAbstractButton* button);

    void on_brushSize_slider_sliderReleased();
    void on_brushSize_slider_sliderMoved(int position);
    void on_brushSize_slider_valueChanged(int value);

    void on_clearAll_clicked();
    void on_clearPen_clicked();

    void on_color_custom_clicked();

    void on_saveButton_clicked();

    void on_pencilButton_clicked();

    void on_textButton_toggled(bool checked);

private:

    Ui::MainWindow *ui;
};
extern bool drawText;
#endif // MAINWINDOW_H
