/****************************************************************************
** ConnectWidget meta object code from reading C++ file 'connect.h'
**
** Created: Thu May 27 13:26:05 2004
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_ConnectWidget
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "connect.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *ConnectWidget::className() const
{
    return "ConnectWidget";
}

QMetaObject *ConnectWidget::metaObj = 0;

void ConnectWidget::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("ConnectWidget","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString ConnectWidget::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("ConnectWidget",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* ConnectWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void(ConnectWidget::*m1_t0)();
    typedef void(ConnectWidget::*m1_t1)();
    typedef void(ConnectWidget::*m1_t2)();
    typedef void(ConnectWidget::*m1_t3)();
    typedef void(ConnectWidget::*m1_t4)();
    typedef void(ConnectWidget::*m1_t5)();
    typedef void(ConnectWidget::*m1_t6)();
    typedef void(ConnectWidget::*m1_t7)();
    typedef void(ConnectWidget::*m1_t8)();
    typedef void(ConnectWidget::*m1_t9)();
    typedef void(ConnectWidget::*m1_t10)();
    typedef void(ConnectWidget::*m1_t11)();
    typedef void(ConnectWidget::*m1_t12)();
    typedef void(ConnectWidget::*m1_t13)();
    typedef void(ConnectWidget::*m1_t14)();
    typedef void(ConnectWidget::*m1_t15)();
    typedef void(ConnectWidget::*m1_t16)();
    typedef void(ConnectWidget::*m1_t17)();
    typedef void(ConnectWidget::*m1_t18)();
    typedef void(ConnectWidget::*m1_t19)();
    typedef void(ConnectWidget::*m1_t20)();
    typedef void(ConnectWidget::*m1_t21)();
    m1_t0 v1_0 = Q_AMPERSAND ConnectWidget::avanceRobot;
    m1_t1 v1_1 = Q_AMPERSAND ConnectWidget::avanceRobotAll;
    m1_t2 v1_2 = Q_AMPERSAND ConnectWidget::saveTrajet;
    m1_t3 v1_3 = Q_AMPERSAND ConnectWidget::loadStyle;
    m1_t4 v1_4 = Q_AMPERSAND ConnectWidget::AfficheRobot;
    m1_t5 v1_5 = Q_AMPERSAND ConnectWidget::ShowObstacle;
    m1_t6 v1_6 = Q_AMPERSAND ConnectWidget::learnStyle;
    m1_t7 v1_7 = Q_AMPERSAND ConnectWidget::stopLearnF;
    m1_t8 v1_8 = Q_AMPERSAND ConnectWidget::OnLineLearnF;
    m1_t9 v1_9 = Q_AMPERSAND ConnectWidget::ButtonSaveWF;
    m1_t10 v1_10 = Q_AMPERSAND ConnectWidget::ButtonLoadWF;
    m1_t11 v1_11 = Q_AMPERSAND ConnectWidget::ButtonFilterF;
    m1_t12 v1_12 = Q_AMPERSAND ConnectWidget::launchLearn;
    m1_t13 v1_13 = Q_AMPERSAND ConnectWidget::showConfRobt;
    m1_t14 v1_14 = Q_AMPERSAND ConnectWidget::showConfSigmoid;
    m1_t15 v1_15 = Q_AMPERSAND ConnectWidget::showConfArethemetique;
    m1_t16 v1_16 = Q_AMPERSAND ConnectWidget::notyet;
    m1_t17 v1_17 = Q_AMPERSAND ConnectWidget::showAbout;
    m1_t18 v1_18 = Q_AMPERSAND ConnectWidget::drawObstacleMode;
    m1_t19 v1_19 = Q_AMPERSAND ConnectWidget::ButtonLoadObstacle;
    m1_t20 v1_20 = Q_AMPERSAND ConnectWidget::ButtonSaveObstacle;
    m1_t21 v1_21 = Q_AMPERSAND ConnectWidget::deleteAllObstacle;
    QMetaData *slot_tbl = QMetaObject::new_metadata(22);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(22);
    slot_tbl[0].name = "avanceRobot()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "avanceRobotAll()";
    slot_tbl[1].ptr = *((QMember*)&v1_1);
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "saveTrajet()";
    slot_tbl[2].ptr = *((QMember*)&v1_2);
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "loadStyle()";
    slot_tbl[3].ptr = *((QMember*)&v1_3);
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "AfficheRobot()";
    slot_tbl[4].ptr = *((QMember*)&v1_4);
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "ShowObstacle()";
    slot_tbl[5].ptr = *((QMember*)&v1_5);
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "learnStyle()";
    slot_tbl[6].ptr = *((QMember*)&v1_6);
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "stopLearnF()";
    slot_tbl[7].ptr = *((QMember*)&v1_7);
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "OnLineLearnF()";
    slot_tbl[8].ptr = *((QMember*)&v1_8);
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "ButtonSaveWF()";
    slot_tbl[9].ptr = *((QMember*)&v1_9);
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "ButtonLoadWF()";
    slot_tbl[10].ptr = *((QMember*)&v1_10);
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "ButtonFilterF()";
    slot_tbl[11].ptr = *((QMember*)&v1_11);
    slot_tbl_access[11] = QMetaData::Public;
    slot_tbl[12].name = "launchLearn()";
    slot_tbl[12].ptr = *((QMember*)&v1_12);
    slot_tbl_access[12] = QMetaData::Public;
    slot_tbl[13].name = "showConfRobt()";
    slot_tbl[13].ptr = *((QMember*)&v1_13);
    slot_tbl_access[13] = QMetaData::Public;
    slot_tbl[14].name = "showConfSigmoid()";
    slot_tbl[14].ptr = *((QMember*)&v1_14);
    slot_tbl_access[14] = QMetaData::Public;
    slot_tbl[15].name = "showConfArethemetique()";
    slot_tbl[15].ptr = *((QMember*)&v1_15);
    slot_tbl_access[15] = QMetaData::Public;
    slot_tbl[16].name = "notyet()";
    slot_tbl[16].ptr = *((QMember*)&v1_16);
    slot_tbl_access[16] = QMetaData::Public;
    slot_tbl[17].name = "showAbout()";
    slot_tbl[17].ptr = *((QMember*)&v1_17);
    slot_tbl_access[17] = QMetaData::Public;
    slot_tbl[18].name = "drawObstacleMode()";
    slot_tbl[18].ptr = *((QMember*)&v1_18);
    slot_tbl_access[18] = QMetaData::Public;
    slot_tbl[19].name = "ButtonLoadObstacle()";
    slot_tbl[19].ptr = *((QMember*)&v1_19);
    slot_tbl_access[19] = QMetaData::Public;
    slot_tbl[20].name = "ButtonSaveObstacle()";
    slot_tbl[20].ptr = *((QMember*)&v1_20);
    slot_tbl_access[20] = QMetaData::Public;
    slot_tbl[21].name = "deleteAllObstacle()";
    slot_tbl[21].ptr = *((QMember*)&v1_21);
    slot_tbl_access[21] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"ConnectWidget", "QWidget",
	slot_tbl, 22,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
