#ifndef SETXAXISOPTIONSDATETIMEDIALOG_H
#define SETXAXISOPTIONSDATETIMEDIALOG_H

#include <QDialog>

#include "ui_setxaxisoptionsdatetimedialog.h"

class SetXAxisOptionsDateTimeDialog : public QDialog, public Ui::SetXAxisOptionsDateTimeDialog
{
    Q_OBJECT

public:
    SetXAxisOptionsDateTimeDialog( QWidget *parent = 0 );

    double AutoGraphMin() const { return( axgmin ); }
    double AutoGraphMax() const { return( axgmax ); }
    double AutoTickmarkSpacing() const { return( axtms ); }

    double ManualGraphMin() const { return( mxgmin ); }
    double ManualGraphMax() const { return( mxgmax ); }
    double ManualTickmarkSpacing() const { return( mxtms ); }

    void setAutoNiceLabel( double var1, double var2, double var3 ) { axtms = var1; axgmin = var2; axgmax = var3; }
    void setManualNiceLabel( double var1, double var2, double var3 ) { mxtms = var1; mxgmin = var2; mxgmax = var3; }

public slots:
    void setDialogItems( int state );

private:
    double  axgmin;             // Graphic minimum, x-Axis, automatically
    double  axgmax;             // Graphic maximum, x-Axis, automatically
    double  axtms;              // Tick mark spacing, x-Axis, automatically

    double  mxgmin;             // Graphic minimum, x-Axis, manually
    double  mxgmax;             // Graphic maximum, x-Axis, manually
    double  mxtms;              // Tick mark spacing, x-Axis, manually
};

#endif
