#ifndef SETPARAMETEROPTIONSDIALOG_H
#define SETPARAMETEROPTIONSDIALOG_H

#include <QDialog>

#include "ui_setparameteroptionsdialog.h"

class SetParameterOptionsDialog : public QDialog, public Ui::SetParameterOptionsDialog
{
    Q_OBJECT

public:
    SetParameterOptionsDialog( QWidget *parent = 0 );

    void setDataTextColor( QColor var ) { datatextcolor = var; }
    void setDataTextFont( QFont var ) { datatextfont = var; }
    void setMarkerColor( QColor var ) { markercolor = var; }
    void setLineColor( QColor var ) { linecolor = var; }
    void setColorizedGreaterRefColor( QColor var ) { colorizedgreaterrefcolor = var; }
    void setColorizedLessRefColor( QColor var ) { colorizedlessrefcolor = var; }
    void setDiagramBackgroundColor( QColor var ) { diagrambackgroundcolor = var; }
    void setReflineColor( QColor var ) { reflinecolor = var; }
    void setPatternComboBox( int Pattern );
    void setYReverseRangeRadioButton( bool YReverseGraphRange );

    QColor MarkerColor() { return( markercolor ); }
    QColor LineColor() { return( linecolor ); }
    QColor ColorizedGreaterRefColor() { return( colorizedgreaterrefcolor ); }
    QColor ColorizedLessRefColor() { return( colorizedlessrefcolor ); }
    QColor DiagramBackgroundColor() { return( diagrambackgroundcolor ); }
    QColor DataTextColor() { return( datatextcolor ); }
    QColor ReflineColor() { return( reflinecolor ); }
    QFont  DataTextFont() { return( datatextfont ); }

    int    PatternComboBox();

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

    bool DialogItemsNotEmpty();

private slots:
    void chosseMarkerColor();
    void chosseLineColor();
    void chosseColorizedGreaterRefColor();
    void chosseColorizedLessRefColor();
    void chosseDiagramBackgroundColor();
    void chosseReflineColor();
    void chosseDataTextColor();
    void chosseDataTextFont();

public slots:
    void setDialogItems( int State );
    void setManuallyPrecision( int Precision );
    void setManuallyScale( QString Value );
    void enableOK();

protected:
    void paintEvent( QPaintEvent *event );

private:
    QColor markercolor;
    QColor linecolor;
    QColor colorizedgreaterrefcolor;
    QColor colorizedlessrefcolor;
    QColor diagrambackgroundcolor;
    QColor datatextcolor;
    QColor reflinecolor;
    QFont  datatextfont;

    int     anfrac;             // nFrac, y-Axis, automatically
    double  axtms;              // Tick mark spacing, y-Axis, automatically
    double  axgmin;             // Graphic minimum, y-Axis, automatically
    double  axgmax;             // Graphic maximum, y-Axis, automatically

    int     mnfrac;             // nFrac, y-Axis, manually
    double  mxtms;              // Tick mark spacing, y-Axis, manually
    double  mxgmin;             // Graphic minimum, y-Axis, manually
    double  mxgmax;             // Graphic maximum, y-Axis, manually
};

#endif
