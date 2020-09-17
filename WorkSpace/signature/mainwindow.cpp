#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(900, 500);    //窗口大小设置为600*500

    press = false;
    /*
	button = new QPushButton(this);
	button->setText(tr("Clear"));
    button->move(480,400);
	connect(button, SIGNAL(clicked()), this, SLOT(zoomIn()));
	*/
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QPen mypen;
    mypen.setWidth(7);
	mypen.setColor(Qt::black);
	painter.setPen(mypen);

    int i = 0;
	// draw point
    while(point_list.size()!=0 && i !=point_list.size())
	{
		painter.drawPoint(point_list.at(i));
		i++;
	}

	/*
	QPainter pp(&pix);
	pp.drawLine(lastPoint, endPoint);
	lastPoint = endPoint;
	QPainter painter(this);
	painter.drawPixmap(0,0,pix);
	*/
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	qDebug() << event->pos();
	
	if(event->button() == Qt::LeftButton)
	{
		this->press = true;
	}
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons()&Qt::LeftButton)
	{
		if(this->press)
		{
		    point = event->pos();
	        point_list.append(point);
			update();	
		}
	}
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{

		this->press = false;
	
}
}

void MainWindow::on_clearButton_clicked()
{
    qDebug() << point_list.size();
    point_list.clear();
    update();
}

void MainWindow::on_expimgButton_clicked()
{
/*
	QPixmap pixmap = QWidget::grab(
		QRect(ui->scrollAreaWidgetContents->x(), 
			  ui->scrollAreaWidgetContents->y(), 
			  ui->scrollAreaWidgetContents->frameGeometry().width(), 
			  ui->scrollAreaWidgetContents->frameGeometry().height()
			  )
        );*/
	/*
    qDebug() << "export Image";

    QPixmap pixmap(this->size());
    render(&pixmap);
    pixmap.save(QCoreApplication::applicationDirPath() + "/1.jpg");
*/


    /*
    //QPixmap pixmap = QPixmap::grabWidget(this);
    //QPixmap pixmap = QPixmap::grabWidget(this);
    QPixmap pixmap = QWidget::grab();
    QSize picSize(28, 28);
    QPixmap ret = pixmap.scaled(picSize);
    ret.save("..\\..\\ExportPic\\num.png");

    */
}
