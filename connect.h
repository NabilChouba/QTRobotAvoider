const int MAXCOLORS = 40;


#include <qlcdnumber.h>

#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qlist.H>
#include "obstacle.h"
#include "Robot.h"
#include "network.h"
#include "vecteur.h"
#include <qtimer.h> 
#include <QPixmap.h>
#include <QLabel.h>
#include "frameChoitArth.h"
#include "confRobot.h"
#include "confSigmoid.h"
#include <qtoolbar.h>
#include <QToolButton.h>
#include <QWhatsThis.h>
#include "enveronement.h"
#include "FormCourbe.h"
//
// ConnectWidget - draws connected lines
///


class ConnectWidget : public QWidget
{
	Q_OBJECT
public:

	int stateMode;
	
	QPushButton *ButtonLearnStyle,*ButtonOnLineLearn,*ButtonShowObstacle;
	QPushButton *ButtonSaveStyle,*ButtonAvancePasAPas,*ButtonGoStopRobot,*ButtonLaunchLearn,*ButtonLearnInfo;
	QPushButton *ButtonSaveW,*ButtonLoadW,*ButtonLoadStyle,*ButtonFilter;
	QLCDNumber *LCDErr,*LCDStep;
	QLabel *TextStep,*TextError;

	QPixmap *PixmapLearnOk,*PixmapInLearn,*pixmapStyleLoad,*pixmapStyleSave,*pixmapShowObstacle;
    QPixmap *pixmapOnLineLearn,*pixmapAvancePasAPas,*pixmapSaveW,*pixmapLoadW,*pixmapFilter;
    QPixmap *pixmapOffLineLearn,*pixmapGoRobot,*pixmapStopRobot,*pixmapLaunchLearn,*pixmapModeStyle;
    

	void FilterFile();
	bool newLoadVecteur;
    ConnectWidget( QWidget *parent=0, const char *name=0 ); 
	~ConnectWidget();

	FormchoitArithmetique *monArethemetique;
	FormRobotConf *monFormRobotConf ;
	FormSigmoid *monFormSigmoid ;
	FormCourbe *monFormCourbe;

	QString *loadStylFile;
	QString *saveStylFile;
	 
	 QTimer *timer;
	 bool ShowObst,learnStyl,OnLineLearn;
protected:
    void	paintEvent( QPaintEvent * );
    void	mousePressEvent( QMouseEvent *);
    void	mouseReleaseEvent( QMouseEvent *);
    void	mouseMoveEvent( QMouseEvent *);
    
public:
//pour le trajet
	net			  *n;
	Robot 		  *robotMover;
	QPoint        *pointMyDebut,*pointMyFin,*actualPos;		
	QColor		  *colors;
	QPoint		  *PHautGauche,*PBasDroit;
	QList<QPoint> *path;
//	QList<obstacle> *envrnemt;
	enverenement *envObstacle;
	networkFather *nnt;
	

public slots:

	
	void avanceRobot();
	void avanceRobotAll();
	void saveTrajet();
	void loadStyle();
	void AfficheRobot();
	void ShowObstacle();
	void learnStyle();
	void stopLearnF();
	void OnLineLearnF();
	void ButtonSaveWF();
	void ButtonLoadWF();
	void ButtonFilterF();
	void launchLearn();
	void showConfRobt();
	void showConfSigmoid();
	void showConfArethemetique();
	void notyet();
	void showAbout();
	void drawObstacleMode();
	void ButtonLoadObstacle();
	void ButtonSaveObstacle();
	void deleteAllObstacle(){envObstacle->rest();};
};