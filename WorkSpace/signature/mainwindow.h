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

private:
	QPoint point;
	/*
	QPoint lastPoint;
	QPoint endPoint;
	*/
	QList<QPoint> point_list;

	bool press;


    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
