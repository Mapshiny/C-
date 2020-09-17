#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(600, 500);    //窗口大小设置为600*500
	pix = QPixmap(200, 200);
	pix.fill(Qt::white);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
	QPainter pp(&pix);
	qDebug() << "lastpoint: " << lastPoint << " endPoint: " << endPoint << endl;
	pp.drawLine(lastPoint, endPoint);
	lastPoint = endPoint;
	QPainter painter(this);
	painter.drawPixmap(0,0,pix);
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	qDebug() << event->pos();
	if(event->button() == Qt::LeftButton)
		lastPoint = event->pos();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons()&Qt::LeftButton)
	{
		endPoint = event->pos();
		update();
	}
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		endPoint = event->pos();
		update();
	}
}
