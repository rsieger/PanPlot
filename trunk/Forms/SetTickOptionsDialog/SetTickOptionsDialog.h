#ifndef SETTICKOPTIONSDIALOG_H
#define SETTICKOPTIONSDIALOG_H

#include <QDialog>

#include "ui_settickoptionsdialog.h"

class SetTickOptionsDialog : public QDialog, public Ui::SetTickOptionsDialog
{
    Q_OBJECT

public:
    SetTickOptionsDialog( QWidget *parent = 0 );

    void setTickmarkColor( QColor var ) { tickmarkcolor = var; }
    void setTicklineColor( QColor var ) { ticklinecolor = var; }
    void setMinorTicklineColor( QColor var ) { minorticklinecolor = var; }

    QColor TickmarkColor() { return( tickmarkcolor ); }
    QColor TicklineColor() { return( ticklinecolor ); }
    QColor MinorTicklineColor() { return( minorticklinecolor ); }

private slots:
    void chosseTickmarkColor();
    void chosseTicklineColor();
    void chosseMinorTicklineColor();

protected:
    void paintEvent( QPaintEvent *event );

private:
    QColor tickmarkcolor, ticklinecolor, minorticklinecolor;
};

#endif
