#ifndef SPIRALGEN_H
#define SPIRALGEN_H

#include <QMainWindow>

namespace Ui {
class SpiralGen;
}

class SpiralGen : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpiralGen(QWidget *parent = 0);
    ~SpiralGen();
    void DrawSprail();
    double Radians(double);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SpiralGen *ui;
    QImage sourceImg;

    QPainterPath * liner;
};

#endif // SPIRALGEN_H
