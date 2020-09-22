#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "compressheader.h"

#include <QPainter>
#include <QSize>
#include <QTime>  
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(900, 500);    //窗口大小设置为900*500
    pix = QPixmap(900,200);
    pix.fill(Qt::white);
    //press = false;
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

	QPainter pp(&pix);
	pp.drawLine(lastPoint, endPoint);
	lastPoint = endPoint;
	QPainter painter(this);
	painter.drawPixmap(0,0,pix);
	/*
	int i = 0;
	while(point_list.size()!=0 && i !=point_list.size())
	{
		painter.drawPoint(point_list.at(i));
		i++;
    }
    */
	/*
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
    */
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
		lastPoint = event->pos();
	}
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() && Qt::LeftButton)
	{
		endPoint = event->pos();
		point_list.append(endPoint);
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

void MainWindow::on_clearButton_clicked()
{
    qDebug() << point_list.size();
    point_list.clear();

    QPixmap clearPix = QPixmap();

    // clearPix.fill(Qt::white);
    // pix = clearPix;
    pix.fill(Qt::white);
	// painter.drawPixmap(0,0,pix);

    update();
}

void MainWindow::on_expimgButton_clicked()
{
	qDebug() << "width:" << pix.width() << " height:" << pix.height();

	QPixmap pixmap = QWidget::grab(
	    QRect(0, 0, pix.width(), pix.height())
	);
	render(&pixmap);
	
	QString ImgPath = QFileDialog::getSaveFileName(this,tr("Save Image"),"../../",tr("Images (*.png *.bmp *.jpg)")); //选择路径
	
	ImgPath += ".bmp";
	pixmap.save(ImgPath);

	//-------------------------图片压缩--------------------------------------- 
	//-------------ifilename------------------------
	//warning: .length() int 隐式转换为 size_t
	char *ifilename = nullptr;
	QByteArray ba = ImgPath.toLatin1();
	ifilename = (char *)malloc(ba.length() + 1);
	memset(ifilename, 0, ba.length());
	memcpy(ifilename, ba.data(), ba.length());
	ifilename[ba.length()] = '\0';
	qDebug()<< "ifilename" << ifilename;
	//-------------ofilename-------------------------------------
	char *ofilename;
	QString current_date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
	QString OutputImg = "../../Compress/Output" + current_date;
	ba = OutputImg.toLatin1();
	ofilename = (char *)malloc(ba.length() + 1);
	memset(ofilename, 0, ba.length());
	memcpy(ofilename, ba.data(), ba.length());
	ofilename[ba.length()] = '\0';

	/*
	char a[60] = "../../ExportPic/test_out_put"; 
	ofilename = a;
	*/
	compress_main(ifilename, ofilename);
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

void MainWindow::on_openImgButton_clicked()
{
    qDebug() << "show picture!";
    QString OpenFile;
    QImage image;
    //打开文件夹中的图片文件
    OpenFile = QFileDialog::getOpenFileName(this, "选择已压缩图片", "../../", "All(*)");
    if( OpenFile != "" )
    {
    	qDebug() << "OpenFile:" << OpenFile;

    	char *ifilename = nullptr;
		QByteArray ba = OpenFile.toLatin1();
		ifilename = (char *)malloc(ba.length() + 1);
		memset(ifilename, 0, ba.length());
		memcpy(ifilename, ba.data(), ba.length());
		ifilename[ba.length()] = '\0';


    	QString current_date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
    	
		char *ofilename;
		QString OutputImg = "../../nonCompress/DecompressImg" + current_date;
		ba = OutputImg.toLatin1();
		ofilename = (char *)malloc(ba.length() + 1);
		memset(ofilename, 0, ba.length());
		memcpy(ofilename, ba.data(), ba.length());
		ofilename[ba.length()] = '\0';

        decompress_main(ifilename, ofilename);
		
		if( image.load(OutputImg) )
        {
            //ui->label->setPixmap(QPixmap::fromImage(image));
            ui->label->setPixmap(QPixmap::fromImage(image.scaled(ui->label->size())));
        }
        
    }

}

void MainWindow::on_saveButton_clicked()
{
	qDebug() << "save image!";
    QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"../../",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    qDebug() << "filename1:" << filename1;
}

void MainWindow::on_pointXYButton_clicked()
{
    int i = 0;
	// draw point
	if(!point_list.size())
		qDebug() << "empty" ;
    while(i < point_list.size())
    {
        qDebug() << "point_list" << i << ":" << point_list[i].x();
    	i++;
    }
    /*
    while(point_list.size()!=0 && i !=point_list.size())
	{
		painter.drawPoint(point_list.at(i));
		i++;
	}
    */
}
