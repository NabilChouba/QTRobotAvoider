// FormCourbe.h: interface for the FormCourbe class.
//
//////////////////////////////////////////////////////////////////////

#ifndef FormCourbe_included
#define FormCourbe_included

#include <qlcdnumber.h>

#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qlist.H>
#include <QPixmap.h>
#include <QLabel.h>
#include <qtoolbar.h>
#include <QToolButton.h>
#include <QWhatsThis.h>
#include <QList.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <QColor.h>




class FormCourbe : public QWidget
{ 
    Q_OBJECT

public:
	FormCourbe( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
	void FormCourbe::courbeDraw(  );
	int dx;
bool scaled;
	double Xscals;
	QList<QPoint> *TabErrorGraph[10];
	int curentGraph;
	
    //FormCourbe( QWidget *parent=0, const char *name=0 );
	QPushButton *TranslatePlus,*TranslateMoin,*zoomPlus,*zoomMoin,*clearAllCourbe;
protected:
	
    void	paintEvent( QPaintEvent * );

public slots:
	void funZoomPlus();
	void funZoomMoin();
	void funclearAllCourbe();
	void funTranslatePlus();
	void funTranslateMoin();


};
#endif