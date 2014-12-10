// ***********************************************************************************************
// *                                                                                             *
// * setXAxixOptionsDialog.cpp - Calls setXAxixOptions dialogs                                   *
// *                                                                                             *
// * Dr. Rainer Sieger - 2013-09-21                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include "Application.h"

/*! @brief Ruft die setXAxixOptions Dialoge auf. */

void MainWindow::doSetXAxisOptionsDialog()
{
    switch( gv_PS.at( gv_PP.at( 0 ) ).Type() )
    {
        case isDateTime:
            doSetXAxisOptionsDateTimeDialog();
            break;
        default:
            doSetXAxisOptionsFloatDialog();
            break;
    }
}
