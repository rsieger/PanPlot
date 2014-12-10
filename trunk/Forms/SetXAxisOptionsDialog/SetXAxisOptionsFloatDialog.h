#ifndef SETXAXISOPTIONSFLOATDIALOG_H
#define SETXAXISOPTIONSFLOATDIALOG_H

#include <QDialog>

#include "ui_setxaxisoptionsfloatdialog.h"

class SetXAxisOptionsFloatDialog : public QDialog, public Ui::SetXAxisOptionsFloatDialog
{
    Q_OBJECT

public:
    SetXAxisOptionsFloatDialog( QWidget *parent = 0 );

    double AutoGraphMin() const { return( axgmin ); }
    double AutoGraphMax() const { return( axgmax ); }
    double AutoTickmarkSpacing() const { return( axtms ); }
    int    AutoPrecision() const { return( anfrac ); }

    double ManualGraphMin() const { return( mxgmin ); }
    double ManualGraphMax() const { return( mxgmax ); }
    double ManualTickmarkSpacing() const { return( mxtms ); }
    int    ManualPrecision() const { return( mnfrac ); }

    void setAutoNiceLabel( int var1, double var2, double var3, double var4 ) { anfrac = var1; axtms = var2; axgmin = var3; axgmax = var4; }
    void setManualNiceLabel( int var1, double var2, double var3, double var4 ) { mnfrac = var1; mxtms = var2; mxgmin = var3; mxgmax = var4; }

    void setReflineColor( QColor var ) { reflinecolor = var; }

    QColor ReflineColor() { return( reflinecolor ); }

    bool DialogItemsNotEmpty();

private slots:
    void chosseReflineColor();

public slots:
    void setDialogItems( int State );
    void setManuallyPrecision( int Precision );
    void setManuallyScale( QString Value );
    void enableOK();

protected:
    void paintEvent( QPaintEvent *event );

private:
    int     anfrac;             // nFrac, x-Axis, automatically
    double  axtms;              // Tick mark spacing, x-Axis, automatically
    double  axgmin;             // Graphic minimum, x-Axis, automatically
    double  axgmax;             // Graphic maximum, x-Axis, automatically

    int     mnfrac;             // nFrac, x-Axis, manually
    double  mxtms;              // Tick mark spacing, x-Axis, manually
    double  mxgmin;             // Graphic minimum, x-Axis, manually
    double  mxgmax;             // Graphic maximum, x-Axis, manually

    QColor  reflinecolor;
};

#endif
