#ifndef SETGLOBALPARAMETEROPTIONSDIALOG_H
#define SETGLOBALPARAMETEROPTIONSDIALOG_H

#include <QDialog>

#include "ui_setglobalparameteroptionsdialog.h"

class SetGlobalParameterOptionsDialog : public QDialog, public Ui::SetGlobalParameterOptionsDialog
{
    Q_OBJECT

public:
    SetGlobalParameterOptionsDialog( QWidget *parent = 0 );

    void setDataTextColor( QColor var ) { datatextcolor = var; }
    void setDataTextFont( QFont var ) { datatextfont = var; }
    void setMarkerColor( QColor var ) { markercolor = var; }
    void setLineColor( QColor var ) { linecolor = var; }
    void setColorizedColor( QColor var ) { colorizedcolor = var; }
    void setDiagramBackgroundColor( QColor var ) { diagrambackgroundcolor = var; }
    void setPatternComboBox( int Pattern );
    void setParameterOrientationRadioButton( int ParameterOrientation );

    QColor MarkerColor() { return( markercolor ); }
    QColor LineColor() { return( linecolor ); }
    QColor ColorizedColor() { return( colorizedcolor ); }
    QColor DiagramBackgroundColor() { return( diagrambackgroundcolor ); }
    QColor DataTextColor() { return( datatextcolor ); }

    QFont  DataTextFont() { return( datatextfont ); }

    int    PatternComboBox();
    int    ParameterOrientationRadioButton();

private slots:
    void chosseMarkerColor();
    void chosseLineColor();
    void chosseColorizedColor();
    void chosseDiagramBackgroundColor();
    void chosseDataTextColor();
    void chosseDataTextFont();

protected:
    void paintEvent( QPaintEvent *event );

private:
    QColor markercolor;
    QColor linecolor;
    QColor colorizedcolor;
    QColor diagrambackgroundcolor;
    QColor datatextcolor;
    QFont  datatextfont;
};

#endif
