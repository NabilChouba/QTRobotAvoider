/****************************************************************************
** FormCourbe meta object code from reading C++ file 'FormCourbe.h'
**
** Created: Sat May 29 21:30:02 2004
**      by: The Qt MOC ($Id: //depot/qt/main/src/moc/moc.y#178 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_FormCourbe
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 8
#elif Q_MOC_OUTPUT_REVISION != 8
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "FormCourbe.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *FormCourbe::className() const
{
    return "FormCourbe";
}

QMetaObject *FormCourbe::metaObj = 0;

void FormCourbe::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("FormCourbe","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION
QString FormCourbe::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("FormCourbe",s);
}

#endif // QT_NO_TRANSLATION
QMetaObject* FormCourbe::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void(FormCourbe::*m1_t0)();
    typedef void(FormCourbe::*m1_t1)();
    typedef void(FormCourbe::*m1_t2)();
    typedef void(FormCourbe::*m1_t3)();
    typedef void(FormCourbe::*m1_t4)();
    m1_t0 v1_0 = Q_AMPERSAND FormCourbe::funZoomPlus;
    m1_t1 v1_1 = Q_AMPERSAND FormCourbe::funZoomMoin;
    m1_t2 v1_2 = Q_AMPERSAND FormCourbe::funclearAllCourbe;
    m1_t3 v1_3 = Q_AMPERSAND FormCourbe::funTranslatePlus;
    m1_t4 v1_4 = Q_AMPERSAND FormCourbe::funTranslateMoin;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(5);
    slot_tbl[0].name = "funZoomPlus()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "funZoomMoin()";
    slot_tbl[1].ptr = *((QMember*)&v1_1);
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "funclearAllCourbe()";
    slot_tbl[2].ptr = *((QMember*)&v1_2);
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "funTranslatePlus()";
    slot_tbl[3].ptr = *((QMember*)&v1_3);
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "funTranslateMoin()";
    slot_tbl[4].ptr = *((QMember*)&v1_4);
    slot_tbl_access[4] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"FormCourbe", "QWidget",
	slot_tbl, 5,
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
