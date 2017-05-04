#include <math.h>
#include <QFileDialog>
#include <QPainter>
#include <QPen>

#include "spiralgen.h"
#include "ui_spiralgen.h"

SpiralGen::SpiralGen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpiralGen)
{
    ui->setupUi(this);
    liner = new QPainterPath();
}

SpiralGen::~SpiralGen()
{
    delete ui;
}

void SpiralGen::DrawSprail()
{
    float b;                                   // Sampled brightness
    float dist = 10;                            // Distance between rings
    float radius = dist/2;                     // Current radius
    float aradius;                             // Radius with brighness applied up
    float bradius;                             // Radius with brighness applied down
    float alpha = 0;                           // Initial rotation
    float density = 75;                        // Density
    int counter=0;                             // Counts the samples
    float ampScale = 2.4;                      // Controls the amplitude
    float x, y, xa, ya, xb, yb;                // current X and y + jittered x and y
    float k;                                   // current radius
    float endRadius;

    int mask = 255;

    QRgb *grays = (QRgb *)sourceImg.scanLine(0);

    k = density/radius;
    alpha += k;
    radius += dist/(360/k);
    x = aradius*cos(Radians(alpha))+sourceImg.width()/2;
    y = -aradius*sin(Radians(alpha))+sourceImg.height()/2;

    endRadius = sqrt(pow((sourceImg.width()/2), 2)+pow((sourceImg.height()/2), 2));

    bool shapeOn = false;

    while(radius<endRadius)
    {
        k = density/radius;
        alpha += k;
        radius += dist/(360/k);
        x = aradius*cos(Radians(alpha))+sourceImg.width()/2;
        y = -aradius*sin(Radians(alpha))+sourceImg.height()/2;

        //检测是否在图片范围内
        if ((x>=0) && (x<sourceImg.width()) && (y>00) && (y<sourceImg.height()))
        {
            int c = qGray(grays[((int)x)+((int)y)*(sourceImg.width())]);
            b = ((255-c)/255.0)*dist*ampScale;  // 根据灰度值计算出明暗度

            aradius = radius+(b/dist);

            xa =  aradius*cos(Radians(alpha))+sourceImg.width()/2;
            ya = -aradius*sin(Radians(alpha))+sourceImg.height()/2;

            k = (density/2)/radius ;


            alpha += k;
            radius += dist/(360/k);
            bradius = radius-(b/dist);
            xb =  bradius*cos(Radians(alpha))+sourceImg.width()/2;
            yb = -bradius*sin(Radians(alpha))+sourceImg.height()/2;

            if(mask==c)
            {
                if(shapeOn)
                {
                   //关闭输出
                }
                shapeOn = false;
            }
            else
            {
                if(!shapeOn)
                {
                    //添加到路径中去
                    shapeOn = true;
                }
                liner->moveTo(xa,ya);
                liner->lineTo(xb,yb);
            }

        }
        else
        {
            //如果是在图片外边了
            if(shapeOn)
            {
                shapeOn = false;
            }
        }

    }

}

double SpiralGen::Radians(double a)
{

    return a*M_PI/180.0;
}

void SpiralGen::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,tr("文件"),tr("./"),tr("Image(*.jpg *.png)"));
    sourceImg = QImage(file);
}

void SpiralGen::on_pushButton_2_clicked()
{
    DrawSprail();

    QImage s(sourceImg.width(),sourceImg.height(),QImage::Format_RGB32);
    s.fill(Qt::white);
    QPainter painter(&s);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawPath(*liner);
    painter.end();
    ui->label->setPixmap(QPixmap::fromImage(s));
}
