#ifndef SETGRAPHICOPTIONSDIALOG_H
#define SETGRAPHICOPTIONSDIALOG_H

#include <QDialog>

#include "ui_setgraphicoptionsdialog.h"

class SetGraphicOptionsDialog : public QDialog, public Ui::SetGraphicOptionsDialog
{
    Q_OBJECT

public:
    SetGraphicOptionsDialog( QWidget *parent = 0 );

    void setBackgroundColor( QColor var ) { backgroundcolor = var; }
    void setDiagramFrameColor( QColor var ) { diagramframecolor = var; }
    void setHeaderTextColor( QColor var ) { headertextcolor = var; }
    void setHeaderTextFont( QFont var ) { headertextfont = var; }

    QColor BackgroundColor() { return( backgroundcolor ); }
    QColor DiagramFrameColor() { return( diagramframecolor ); }
    QColor HeaderTextColor() { return( headertextcolor ); }
    QFont  HeaderTextFont() { return( headertextfont ); }

private slots:
    void setFixedDiagramSizeOptionsEnabled( int state );
    void chosseBackgroundColor();
    void chosseDiagramFrameColor();
    void chosseHeaderTextColor();
    void chosseHeaderTextFont();

protected:
    void paintEvent( QPaintEvent *event );

private:
    QColor backgroundcolor;
    QColor diagramframecolor;
    QColor headertextcolor;
    QFont  headertextfont;
};

#endif
