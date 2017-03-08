/****************************************************************************
** FormRobotConf meta object code from reading C++ file 'confRobot.h'
**
** Created: Mon Dec 1 20:26:03 2003
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_FormRobotConf
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "confRobot.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *FormRobotConf::className() const
{
    return "FormRobotConf";
}

QMetaObject *FormRobotConf::metaObj = 0;

void FormRobotConf::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("FormRobotConf","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString FormRobotConf::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("FormRobotConf",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* FormRobotConf::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void(FormRobotConf::*m1_t0)();
    m1_t0 v1_0 = Q_AMPERSAND FormRobotConf::ok;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "ok()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"FormRobotConf", "QWidget",
	slot_tbl, 1,
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
