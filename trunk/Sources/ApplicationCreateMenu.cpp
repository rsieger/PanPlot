// ***********************************************************************************************
// *                                                                                             *
// * createMenu.cpp - creates application menus                                                  *
// *                                                                                             *
// * Dr. Rainer Sieger - 2008-05-18                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Erstellen der Menue-Aktionen. */

void MainWindow::createActions()
{
// File menu
    newWindowAction = new QAction(tr("&New window"), this);
    newWindowAction->setShortcut(tr("Ctrl+N"));
    connect(newWindowAction, SIGNAL(triggered()), this, SLOT(newWindow()));

    openFileAction = new QAction(tr("&Open..."), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(doReadData()));

    openFolderAction = new QAction(tr("Select &Folder..."), this);
    openFolderAction->setShortcut(tr("Ctrl+F"));
    connect(openFolderAction, SIGNAL(triggered()), this, SLOT(chooseFolder()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveDataFile()));

    saveAsAction = new QAction(tr("Save as..."), this);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveDataFileAs()));

    hideWindowAction = new QAction(tr("&Close window"), this);
    hideWindowAction->setShortcut(tr("Ctrl+W"));
    connect(hideWindowAction, SIGNAL(triggered()), this, SLOT(hideWindow()));

    savePlotBMPAction = new QAction(tr("Save plot as BMP..."), this);
    savePlotBMPAction->setShortcut(tr("Ctrl+B"));
    connect(savePlotBMPAction, SIGNAL(triggered()), this, SLOT(doSavePlotBMP()));

    savePlotPDFAction = new QAction(tr("Save plot as PDF..."), this);
    savePlotPDFAction->setShortcut(tr("Ctrl+D"));
    connect(savePlotPDFAction, SIGNAL(triggered()), this, SLOT(doSavePlotPDF()));

    savePlotPNGAction = new QAction(tr("Save plot as PNG..."), this);
    savePlotPNGAction->setShortcut(tr("Ctrl+G"));
    connect(savePlotPNGAction, SIGNAL(triggered()), this, SLOT(doSavePlotPNG()));

    savePlotSVGAction = new QAction(tr("Save plot as SVG..."), this);
    savePlotSVGAction->setShortcut(tr("Ctrl+V"));
    connect(savePlotSVGAction, SIGNAL(triggered()), this, SLOT(doSavePlotSVG()));

    printPlotAction = new QAction(tr("&Print plot..."), this);
    printPlotAction->setShortcut(tr("Ctrl+P"));
    connect(printPlotAction, SIGNAL(triggered()), this, SLOT(doPrintPlot()));

    reloadFileAction = new QAction(tr("&Reload"), this);
    reloadFileAction->setShortcut(tr("Ctrl+R"));
    connect(reloadFileAction, SIGNAL(triggered()), this, SLOT(doReloadFile()));

    setEncodingDialogAction = new QAction(tr("Set encoding..."), this);
    setEncodingDialogAction->setShortcut(tr("Ctrl+,"));
    connect(setEncodingDialogAction, SIGNAL(triggered()), this, SLOT(doSetEncodingDialog()));

    exitAction = new QAction(tr("&Quit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitApplication()));

    // Show menu
    showPlotVAction = new QAction(tr("Data plot &vertical"), this);
    showPlotVAction->setShortcut(tr("F5"));
    connect(showPlotVAction, SIGNAL(triggered()), this, SLOT(doShowPlotV()));

    showPlotHAction = new QAction(tr("Data plot &horizontal"), this);
    showPlotHAction->setShortcut(tr("F6"));
    connect(showPlotHAction, SIGNAL(triggered()), this, SLOT(doShowPlotH()));

    showDatasetDescriptionAction = new QAction(tr("Show &data set description"), this);
    showDatasetDescriptionAction->setShortcut(tr("Ctrl+D"));
    connect(showDatasetDescriptionAction, SIGNAL(triggered()), this, SLOT(doShowDatasetDescription()));

    printDatasetDescriptionAction = new QAction(tr("Print data set description..."), this);
    connect(printDatasetDescriptionAction, SIGNAL(triggered()), this, SLOT(doPrintDatasetDescription()));

    saveDatasetDescriptionTextAction = new QAction(tr("Save data set description to text file"), this);
    connect(saveDatasetDescriptionTextAction, SIGNAL(triggered()), this, SLOT(doSaveDatasetDescriptionText()));

    saveDatasetDescriptionPDFAction = new QAction(tr("Save data set description to PDF file"), this);
    connect(saveDatasetDescriptionPDFAction, SIGNAL(triggered()), this, SLOT(doSaveDatasetDescriptionPDF()));

    showParameterStatisticAction = new QAction(tr("Show p&arameter statistic"), this);
    showParameterStatisticAction->setShortcut(tr("Ctrl+A"));
    connect(showParameterStatisticAction, SIGNAL(triggered()), this, SLOT(doShowParameterStatistic()));

    printParameterStatisticAction = new QAction(tr("Print parameter statistic..."), this);
    connect(printParameterStatisticAction, SIGNAL(triggered()), this, SLOT(doPrintParameterStatistic()));

    saveParameterStatisticTextAction = new QAction(tr("Save parameter statistic to text file"), this);
    connect(saveParameterStatisticTextAction, SIGNAL(triggered()), this, SLOT(doSaveParameterStatisticText()));

    saveParameterStatisticPDFAction = new QAction(tr("Save parameter statistic to PDF text"), this);
    connect(saveParameterStatisticPDFAction, SIGNAL(triggered()), this, SLOT(doSaveParameterStatisticPDF()));

    // Options menu
    setGraphicOptionsDialogAction = new QAction(tr("&Graphic options"), this);
    setGraphicOptionsDialogAction->setShortcut(tr("Alt+G"));
    connect(setGraphicOptionsDialogAction, SIGNAL(triggered()), this, SLOT(doSetGraphicOptionsDialog()));

    setTickOptionsDialogAction = new QAction(tr("&Tick options"), this);
    setTickOptionsDialogAction->setShortcut(tr("Alt+T"));
    connect(setTickOptionsDialogAction, SIGNAL(triggered()), this, SLOT(doSetTickOptionsDialog()));

    setGlobalParameterOptionsDialogAction = new QAction(tr("&Parameter options"), this);
    setGlobalParameterOptionsDialogAction->setShortcut(tr("Alt+P"));
    connect(setGlobalParameterOptionsDialogAction, SIGNAL(triggered()), this, SLOT(doSetGlobalParameterOptionsDialog()));

    selectParametersDialogAction = new QAction(tr("&Select parameters"), this);
    selectParametersDialogAction->setShortcut(tr("Alt+S"));
    connect(selectParametersDialogAction, SIGNAL(triggered()), this, SLOT(doSelectParametersDialog()));

    setXAxisOptionsDialogAction = new QAction(tr("&X-Axis options"), this);
    setXAxisOptionsDialogAction->setShortcut(tr("Alt+X"));
    connect(setXAxisOptionsDialogAction, SIGNAL(triggered()), this, SLOT(doSetXAxisOptionsDialog()));

    for ( int i=0; i < _MAX_NUM_OF_PARAMETERS_ ; i++ )
    {
        setParameterOptionsDialogAction[i] = new QAction( this );
        setParameterOptionsDialogAction[i]->setVisible( false );
        connect(setParameterOptionsDialogAction[i], SIGNAL(triggered()), this, SLOT(doSetParameterOptionsDialog()));
    }

    // Preset submenu
    presetHNAction = new QAction(tr("Horizontal"), this);
    connect(presetHNAction, SIGNAL(triggered()), this, SLOT(doPresetHN()));

    presetHRAction = new QAction(tr("Horizontal, reverse geocode range"), this);
    connect(presetHRAction, SIGNAL(triggered()), this, SLOT(doPresetHR()));

    presetVNAction = new QAction(tr("Vertical"), this);
    connect(presetVNAction, SIGNAL(triggered()), this, SLOT(doPresetVN()));

    presetVRAction = new QAction(tr("Vertical, reverse geocode range"), this);
    connect(presetVRAction, SIGNAL(triggered()), this, SLOT(doPresetVR()));

    presetCMAction = new QAction(tr("Random marker color"), this);
    connect(presetCMAction, SIGNAL(triggered()), this, SLOT(doPresetCM()));

    presetCLAction = new QAction(tr("Random line color"), this);
    connect(presetCLAction, SIGNAL(triggered()), this, SLOT(doPresetCL()));

    presetCCAction = new QAction(tr("Random plot color"), this);
    connect(presetCCAction, SIGNAL(triggered()), this, SLOT(doPresetCC()));

    // Help menu
    aboutAction = new QAction(tr("&About ") + getApplicationName(), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    showHelpAction = new QAction(getApplicationName() + tr(" &Help"), this);
    showHelpAction->setShortcut(tr("F1"));
    connect(showHelpAction, SIGNAL(triggered()), this, SLOT(displayHelp()));

#if defined(Q_OS_WIN)
    newWindowAction->setStatusTip(tr("Create a new file"));
    openFileAction->setStatusTip(tr("Choose an existing file"));
    openFolderAction->setStatusTip(tr("Choose an existing folder"));
    saveAction->setStatusTip(tr("Save the document to disk"));
    saveAsAction->setStatusTip(tr("Save the document under a new name"));
    reloadFileAction->setStatusTip(tr("Reload dataset"));
    setEncodingDialogAction->setStatusTip(tr("Set encoding of dataset"));
    exitAction->setStatusTip(tr("Exit the application"));
    showPlotVAction->setStatusTip(tr("Shows the plot vertical"));
    showPlotHAction->setStatusTip(tr("Shows the plot horizontal"));
    showDatasetDescriptionAction->setStatusTip(tr("Shows the description of dataset"));
    showParameterStatisticAction->setStatusTip(tr("Shows minimum and maximum of parameters"));
    setEncodingDialogAction->setStatusTip(tr("Set encoding of dataset"));
    setGraphicOptionsDialogAction->setStatusTip(tr("Set graphic options"));
    setTickOptionsDialogAction->setStatusTip(tr("Set tick options"));
    setGlobalParameterOptionsDialogAction->setStatusTip(tr("Set all parameter options"));
    selectParametersDialogAction->setStatusTip(tr("Select parameters"));
    aboutAction->setStatusTip(tr("Show the application's About box"));
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    showHelpAction->setStatusTip(tr("Show the application's help"));
#endif

}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Verbindet Menues mit Aktionen. */

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu( tr( "&File" ) );
    fileMenu->addAction( openFileAction );
    fileMenu->addAction( saveAction ); saveAction->setEnabled( false );
    fileMenu->addAction( saveAsAction ); saveAsAction->setEnabled( false );
    fileMenu->addAction( reloadFileAction ); reloadFileAction->setEnabled( false );
    fileMenu->addSeparator();

#if defined(Q_OS_LINUX)
    ;
#endif

#if defined(Q_OS_MAC)
    fileMenu->addAction( newWindowAction );
    newWindowAction->setEnabled( false );
    fileMenu->addAction( hideWindowAction );
#endif

#if defined(Q_OS_WIN)
    fileMenu->addAction( hideWindowAction );
#endif

    fileMenu->addSeparator();
    fileMenu->addAction( setEncodingDialogAction ); setEncodingDialogAction->setEnabled( true );
    fileMenu->addSeparator();
    fileMenu->addAction( savePlotBMPAction ); savePlotBMPAction->setEnabled( false );
    fileMenu->addAction( savePlotPDFAction ); savePlotPDFAction->setEnabled( false );
    fileMenu->addAction( savePlotPNGAction ); savePlotPNGAction->setEnabled( false );
    fileMenu->addAction( savePlotSVGAction ); savePlotSVGAction->setEnabled( false );
    fileMenu->addAction( printPlotAction ); printPlotAction->setEnabled( false );
    fileMenu->addSeparator();
    fileMenu->addAction( printDatasetDescriptionAction ); printDatasetDescriptionAction->setEnabled( false );
    fileMenu->addAction( saveDatasetDescriptionTextAction ); saveDatasetDescriptionTextAction->setEnabled( false );
    fileMenu->addAction( saveDatasetDescriptionPDFAction ); saveDatasetDescriptionPDFAction->setEnabled( false );
    fileMenu->addSeparator();
    fileMenu->addAction( printParameterStatisticAction ); printParameterStatisticAction->setEnabled( false );
    fileMenu->addAction( saveParameterStatisticTextAction ); saveParameterStatisticTextAction->setEnabled( false );
    fileMenu->addAction( saveParameterStatisticPDFAction ); saveParameterStatisticPDFAction->setEnabled( false );

    fileMenu->addSeparator();
    fileMenu->addAction( exitAction );

// **********************************************************************************************

    showMenu = menuBar()->addMenu( tr( "&Windows" ) );
    showMenu->addAction( showPlotVAction ); showPlotVAction->setEnabled( false );
    showMenu->addAction( showPlotHAction ); showPlotHAction->setEnabled( false );
    showMenu->addSeparator();
    showMenu->addAction( showDatasetDescriptionAction ); showDatasetDescriptionAction->setEnabled( false );
    showMenu->addAction( showParameterStatisticAction ); showParameterStatisticAction->setEnabled( false );

// **********************************************************************************************

    optionMenu = menuBar()->addMenu( tr( "&Options" ) );
    presetMenu = optionMenu->addMenu( tr( "Presets") ); presetMenu->setEnabled( false );
    presetMenu->addAction( presetHNAction );
    presetMenu->addAction( presetHRAction );
    presetMenu->addAction( presetVNAction );
    presetMenu->addAction( presetVRAction );
    presetMenu->addSeparator();
    presetMenu->addAction( presetCMAction );
    presetMenu->addAction( presetCLAction );
    presetMenu->addAction( presetCCAction );
    optionMenu->addSeparator();
    optionMenu->addAction( setGraphicOptionsDialogAction ); setGraphicOptionsDialogAction->setEnabled( false );
    optionMenu->addAction( setTickOptionsDialogAction ); setTickOptionsDialogAction->setEnabled( false );
    optionMenu->addAction( setGlobalParameterOptionsDialogAction ); setGlobalParameterOptionsDialogAction->setEnabled( false );
    optionMenu->addSeparator();
    optionMenu->addAction( selectParametersDialogAction ); selectParametersDialogAction->setEnabled( false );
    optionMenu->addSeparator();
    optionMenu->addAction( setXAxisOptionsDialogAction ); setXAxisOptionsDialogAction->setEnabled( false );

    separatorAction = optionMenu->addSeparator();

    for ( int i=0; i < _MAX_NUM_OF_PARAMETERS_ ; i++ )
        optionMenu->addAction( setParameterOptionsDialogAction[i] );

// **********************************************************************************************

    helpMenu = menuBar()->addMenu( tr( "&Help" ) );
    helpMenu->addAction( aboutAction );
    helpMenu->addAction( aboutQtAction );
    helpMenu->addSeparator();
    helpMenu->addAction( showHelpAction );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::enableMenuItems( const QStringList &sl_FilenameList )
{
    bool b_containsBinaryFile = containsBinaryFile( sl_FilenameList );

// **********************************************************************************************

    QList<QAction*> showMenuActions = showMenu->actions();

    if ( b_containsBinaryFile == false )
    {
        for ( int i=0; i<showMenuActions.count(); ++i )
            showMenuActions.at( i )->setEnabled( true );
    }
    else
    {
        for ( int i=0; i<showMenuActions.count(); ++i )
            showMenuActions.at( i )->setEnabled( false );
    }
}
