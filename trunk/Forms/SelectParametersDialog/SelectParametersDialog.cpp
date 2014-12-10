// ***********************************************************************************************
// *                                                                                             *
// * SelectParametersDialog.cpp - Selects parameter from parameter list                          *
// *                                                                                             *
// * Dr. Rainer Sieger - 2009-05-13                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "Application.h"
#include "SelectParametersDialog.h"

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void MainWindow::doSelectParametersDialog()
{
    QStringList sl_ParameterList;
    QStringList sl_ItemListLeft;
    QStringList sl_ItemListRight;

//  bool        b_showShortName         = false;
//  bool        b_showMethod            = false;
//  bool        b_showComment           = false;

    bool        b_sortParameterList     = false;

    int         i_maxNumOfParameters    = 256;

// ***********************************************************************************************************************

    saveGraphicOptions();
    saveParameterOptions();

    this->setUpdatesEnabled( false );

    for ( int i=0; i<gv_PS.count(); i++ )
        sl_ParameterList.append( gv_PS.at( i ).Parameter() );

    for ( int i=0; i<gv_PP.count(); i++ )
    {
        if ( gv_PP.at( i ) > -1 )
            sl_ItemListRight.append( gv_PS.at( gv_PP.at( i ) ).Parameter() );
    }

    for ( int i=0; i<gv_PS.count(); i++ )
    {
        if ( sl_ItemListRight.contains( sl_ParameterList.at( i ) ) == false )
            sl_ItemListLeft.append( sl_ParameterList.at( i ) );
    }

// ***********************************************************************************************************************

    SelectParametersDialog dialog( sl_ParameterList, sl_ItemListLeft, sl_ItemListRight, i_maxNumOfParameters );

    dialog.sortList_checkBox->setChecked( b_sortParameterList );

    if ( dialog.sortList_checkBox->isChecked() == true )
        dialog.lb1->sortItems();

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( sizeParameterDialog );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        b_sortParameterList = dialog.sortList_checkBox->isChecked();

        for ( int i=0; i<gv_PS.count(); i++ )
            gv_PP[i] = -1;

        for ( int j=0; j<dialog.lb2->count(); ++j )
        {
            for ( int i=0; i<sl_ParameterList.count(); i++ )
            {
                if ( sl_ParameterList.at( i ) == dialog.lb2->item( j )->text() )
                    gv_PP[j] = gv_PS.at( i ).ID();
            }
        }
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    posDialog           = dialog.pos();
    sizeParameterDialog = dialog.size();

    this->setUpdatesEnabled( true );

    doShowPlot();
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

SelectParametersDialog::SelectParametersDialog( QStringList sl_ParameterList, QStringList sl_ItemListLeft, QStringList sl_ItemListRight, int i_maxNumOfParameters, QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(SelectAll_pushButton, SIGNAL(clicked()), this, SLOT(selectAll()));
    connect(DeselectAll_pushButton, SIGNAL(clicked()), this, SLOT(deselectAll()));
    connect(sortList_checkBox, SIGNAL(clicked()), this, SLOT(sortList()));
    connect(Left2Right_pushButton, SIGNAL(clicked()), this, SLOT(slotLeft2Right()));
    connect(Right2Left_pushButton, SIGNAL(clicked()), this, SLOT(slotRight2Left()));
    connect(lb1, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotLeft2Right()));
    connect(lb2, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotRight2Left()));

    lb1->setSelectionMode( QAbstractItemView::ExtendedSelection );
    lb2->setSelectionMode( QAbstractItemView::ExtendedSelection );

    OK_pushButton->setWhatsThis( "Close dialog" );
    Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    i_maxNumOfItems = i_maxNumOfParameters;

    for ( int i=0; i<sl_ItemListLeft.count(); ++i )
        lb1->addItem( sl_ItemListLeft.at( i ) );

    for ( int i=0; i<sl_ItemListRight.count(); ++i )
        lb2->addItem( sl_ItemListRight.at( i ) );

    list = sl_ParameterList;

    enableOKButton();
}

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/*
 * SLOT slotLeft2Right
 *
 * Move all selected items of the first ListBox into the
 * second ListBox
 */

void SelectParametersDialog::slotLeft2Right()
{
    int n = 0;

    for ( int i=0; i<lb1->count(); ++i )
    {
        if ( lb1->item( i )->isSelected() == true )
            ++n;
    }

    if ( n<i_maxNumOfItems )
    {
        n = lb1->count()-1;

        for ( int i=0; i<=n; ++i )
        {
            if ( lb1->item( i )->isSelected() == true )
                lb2->addItem( lb1->item( i )->text() );
        }

        for ( int i=n; i>=0; --i )
        {
            if ( lb1->item( i )->isSelected() == true )
                lb1->takeItem( i );
        }
    }
    else
    {
        QMessageBox::information( this, "PanPlot2", QString( "The application you have choosen\nsupports a maximum of %1 parameters." ).arg( i_maxNumOfItems ) );

        for ( int i=0; i<lb1->count(); ++i )
            lb1->setCurrentItem( lb1->item( i ), QItemSelectionModel::Deselect );
    }

    if ( sortList_checkBox->isChecked() )
        lb1->sortItems();

    enableOKButton();
}

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/*
 * SLOT slotRight2Left
 *
 * Move all selected items of the second ListBox into the
 * first ListBox
 */

void SelectParametersDialog::slotRight2Left()
{
    int n = lb2->count()-1;

    for ( int i=0; i<=n; ++i )
    {
        if ( lb2->item( i )->isSelected() == true )
            lb1->addItem( lb2->item( i )->text() );
    }

    for ( int i=n; i>=0; --i )
    {
        if ( lb2->item( i )->isSelected() == true )
            lb2->takeItem( i );
    }

    enableOKButton();
}

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

void SelectParametersDialog::selectAll()
{
    for ( int i=0; i<lb1->count(); ++i )
        lb1->setCurrentItem( lb1->item( i ), QItemSelectionModel::Select );

    slotLeft2Right();
}

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

void SelectParametersDialog::deselectAll()
{
    sortList();
}

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

void SelectParametersDialog::sortList()
{
    while ( lb1->count() > 0 )
        lb1->takeItem( 0 );

    while ( lb2->count() > 0 )
        lb2->takeItem( 0 );

    for ( int i=0; i<list.count(); ++i )
        lb1->addItem( list.at( i ) );

    if ( sortList_checkBox->isChecked() )
        lb1->sortItems();

    enableOKButton();
}

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

void SelectParametersDialog::enableOKButton()
{
    if ( ( lb2->count() > 1 ) && ( lb2->count() <= i_maxNumOfItems ) )
    {
        SelectAll_pushButton->setDefault( false );
        OK_pushButton->setEnabled( true );
        OK_pushButton->setDefault( true );
        OK_pushButton->setFocus();
    }
    else
    {
        OK_pushButton->setEnabled( false );
        OK_pushButton->setDefault( false );
        SelectAll_pushButton->setDefault( true );
        SelectAll_pushButton->setFocus();

        if ( lb2->count() > i_maxNumOfItems )
            QMessageBox::information( this, "Pan2Applic", QString( "The application you have choosen\nsupports a maximum of %1 parameters.\nPlease remove %2 parameter(s) from the\nlist or click on cancel." ).arg( i_maxNumOfItems ).arg( lb2->count() - i_maxNumOfItems ) );
    }
}
