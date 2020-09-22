#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_clearButton_clicked();
    void on_expimgButton_clicked();
    void on_pointXYButton_clicked();
    void on_openImgButton_clicked();
    void on_matrixButton_clicked();

private:
	QPoint point;

	QPixmap pix;
	QPoint lastPoint;
	QPoint endPoint;
	
	QList<QPoint> point_list;



    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
