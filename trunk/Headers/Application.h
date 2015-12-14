/* Application.h              */
/* 2013-05-15                 */
/* Dr. Rainer Sieger          */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtSvg/QtSvg>

#include <QTextEdit>
#include <QTextCodec>
#include <QTextStream>
#include <QStringListModel>
#include <QListView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QProcess>
#include <QTimer>
#include <QMimeData>
#include <QDesktopServices>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>
#include <QStatusBar>
#include <QSettings>
#include <QTableWidget>
#include <QScrollArea>
#include <QHeaderView>
#include <QPainter>
#include <QColorDialog>
#include <QFontDialog>
#include <QDropEvent>
#include <QImage>
#include <QImageWriter>

#include <qmath.h>

#include "Globals.h"
#include "DataItem.h"
#include "PlotSettings.h"
#include "Plotter.h"
#include "Webfile.h"

class QAction;
class QLabel;
class QProgressDialog;
class QProgressBar;
class QTimer;
class QDateTime;
class QUrl;
class QTextEdit;
class QStringListModel;
class QListView;
class QTableWidget;
class QScrollArea;
class RenderArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO( "author", "Rainer Sieger" )
    Q_CLASSINFO( "url", "http://www.pangaea.de" )

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    int         gi_EOL;                          //!< End-of-Line Zeichen fuer die Outputdateien
    int         gi_Codec;                        //!< Zeichenkodierung
    int         gi_Extension;                    //!< Dateierweiterung fuer Ausgabedateien
    int         gi_ActionNumber;                 //!< Die ActionNumber wird bei jedem angewandenten Tool um 1 erhoeht.
    int         gi_NumOfProgramStarts;           //!< Anzahl der Programmstarts

    bool        gb_showProgressBar;              //!< Soll der ProgressBar im Fenster unten rechts angezeigt werden?

    int         gi_SavePlotFormat;               //!< Format für die Ausgabedatei (PNG, BMP, Printer)
    int         gi_ParameterOrientation;         //!< Orientierung der Parametertitel (0 deg, 45 deg, 90 deg)
    int         gi_PlotOrientation;              //!< Orientierung des Plots
    int         gi_MarkerSize;                   //!< Groesse der Marker
    int         gi_LineWidth;                    //!< Breite der Linien
    int         gi_ColorizedPattern;             //!< Pattern fuer Colorized
    int         gi_marginTop;                    //!< Rand oben
    int         gi_marginBottom;                 //!< Rand unten
    int         gi_marginLeft;                   //!< Rand links
    int         gi_marginRight;                  //!< Rand rechts
    int         gi_marginScale;                  //!< Rand um Scaletexte
    int         gi_diagramWidth;                 //!< Diagrammbreite
    int         gi_diagramHeight;                //!< Diagrammhoehe
    int         gi_diagramDistance;              //!< Abstand zwischen zwei Diagrammen
    int         gi_diagramFrameWidth;            //!< Breite des Diarammrahmens
    int         gi_TickmarkWidth;                //!< Breite der Tickmarks
    int         gi_MinorTickmarkWidth;           //!< Breite der Minor Tickmarks
    int         gi_TicklineWidth;                //!< Breite der Ticklines
    int         gi_MinorTicklineWidth;           //!< Breite der Minor Ticklines
    int         gi_TickmarkLength;               //!< Laenge der Tickmarks
    int         gi_numMinorXTicks;               //!< Anzahl der Minor Ticks zwischen in Major Ticks, X-Achse
    int         gi_numMinorYTicks;               //!< Anzahl der Minor Ticks zwischen in Major Ticks, Y-Achse
    int         gi_DateTimeFormat;               //!< Format fuer die Anzeige, wenn X-Achse Date/Time ist

    QColor      gc_MarkerColor;                  //!< Farbe der Marker
    QColor      gc_LineColor;                    //!< Farbe der Linien
    QColor      gc_ColorizedGreaterRefColor;     //!< Farbe fuer Colorized
    QColor      gc_ColorizedLessRefColor;        //!< Farbe fuer Colorized
    QColor      gc_DiagramBackgroundColor;       //!< Farbe fuer den Diagramm Hintergrund
    QColor      gc_BackgroundColor;              //!< Farbe fuer den Hintergrund
    QColor      gc_HeaderTextColor;              //!< Farbe fuer Header Text
    QColor      gc_DataTextColor;                //!< Farbe fuer Data Text
    QColor      gc_TickmarkColor;                //!< Farbe der Tickmarks
    QColor      gc_TicklineColor;                //!< Farbe der Ticklines
    QColor      gc_MinorTicklineColor;           //!< Farbe der MinorTicklines
    QColor      gc_DiagramFrameColor;            //!< Farbe des Diagrammrahmens

    bool        gb_fixedDiagramSize;             //!< true = Diagramhoehe und -breite wird gesetzt, false = Diagramhoehe und -breite wird berechnet aus Window->height()
    bool        gb_Antialiasing;

    bool        gb_drawXTickmarkLabels;
    bool        gb_drawYTickmarkLabels;

    bool        gb_drawXRefline;
    bool        gb_drawYRefline;

    bool        gb_drawMajorXTicklines;
    bool        gb_drawMajorXTicksLeft;
    bool        gb_drawMajorXTicksRight;
    bool        gb_drawMajorXTicksInside;
    bool        gb_drawMajorXTicksOutside;

    bool        gb_drawMajorYTicklines;
    bool        gb_drawMajorYTicksTop;
    bool        gb_drawMajorYTicksBottom;
    bool        gb_drawMajorYTicksInside;
    bool        gb_drawMajorYTicksOutside;

    bool        gb_drawMinorXTicklines;
    bool        gb_drawMinorXTicksLeft;
    bool        gb_drawMinorXTicksRight;
    bool        gb_drawMinorXTicksInside;
    bool        gb_drawMinorXTicksOutside;

    bool        gb_drawMinorYTicklines;
    bool        gb_drawMinorYTicksTop;
    bool        gb_drawMinorYTicksBottom;
    bool        gb_drawMinorYTicksInside;
    bool        gb_drawMinorYTicksOutside;

    bool        gb_XReverseGraphRange;
    bool        gb_YReverseGraphRange;

    bool        gb_drawDataText;
    bool        gb_drawMarkers;
    bool        gb_drawLines;
    bool        gb_drawColorized;
    bool        gb_drawDiagramBackground;
    bool        gb_drawBackground;

    bool        gb_manuallyXScale;

    QFont       gf_HeaderTextFont;
    QFont       gf_DataTextFont;

    QStringList gsl_FilenameList;                //!< Liste aller InputDateinamen incl. Pfad.

    QString     gs_FilenameFormat;               //!< Bestimmt in die Form des automatisch erzeugten neuen Dateinamens. \%a = aktuelle Actionnumber, \%N = Dateiname.
    QString     gs_Path;                         //!< Der zuletzt verwendete Pfad.
    QString     gs_Version;                      //!< Aktuelle Version des Programms.
    QString     gs_FilenamePlot;                 //!< Dateiname für Imagedatei vom Plot

    QStringList            gsl_DataDescription;
    QVector<DataItem>      gv_Data;
    QVector<PlotSettings>  gv_PS;
    QVector<int>           gv_PP;

    //******************************************************************************************************************

    int readData( const QString &FilenameIn, const int Codec );
    int readDataFile( const QString &FilenameIn );
    int writeDataFile( const QString &FilenameOut );

    int splitInput( QStringList &Input, QStringList &DataDescription, QStringList &Data );
    int buildDataVector( const QStringList &DataList, QVector<DataItem> &DataVector, QVector<PlotSettings> &PS, QVector<int> &PP );
    int setRange( const QVector<DataItem> &Data, QVector<PlotSettings> &PS );
    int sortParameter( const QVector<PlotSettings> &PS, QVector<int> &PP );
    void calcStatistics( const int j, QVector<PlotSettings> &PS, QList<double> &Stat );

    void setMainWindowWidget( const int widget, bool b_saveOptions=true );

    void showParameterStatistic( const QVector<PlotSettings> &PS );
    void saveParameterStatistic( const QString &Filename, const QVector<PlotSettings> &PS, const int Format );
    QString createParameterStatisticOutputText( const QString &Filename, const QVector<PlotSettings> &PS );

    void showDatasetDescription( const QStringList &DatasetDescription );
    void saveDatasetDescription( const QString &Filename, const QStringList &DataDescription, const int Format );
    QString createDataDescriptionOutputText( const QString &Filename, const QStringList &DataDescription );

    // ApplicationTools
    void initPointer();
    void savePlot(const int PlotFormat, const QString &FilenamePlot );
    void saveGraphicOptions( const bool updateGraphicOptions = false );
    void saveParameterOptions( const bool updateGraphicOptions = false );
    void setUpdateGlobalParameterOptions( const bool var=true ) { ugpo = var; }

    QColor setColor( const QString &Color );
    QString ColorStr( const QColor &Color );

    QFont setFont( const QString &Font );
    QString FontStr( const QFont &Font );

    bool setBool( const bool b1=true, const bool b2 = true, const bool b3 = true );
    bool UpdateGlobalParameterOptions() const { return( ugpo ); }

    inline int rangedRand( unsigned int min, unsigned int max ){ return( ( qrand() % ( max - min ) + 1 ) + min ); }

    // NiceLabel
    void calcLooseLabel( const double min, const double max, int &nfrac, double &tickMarkSpacing, double &graphmin, double &graphmax );
    double nicenum( const double x, const bool round );
    double expt( const double a, int n );

protected:
    void dragEnterEvent( QDragEnterEvent *event );
    void dropEvent( QDropEvent *event );
    void closeEvent( QCloseEvent *event );
    void onError( const int err );

signals:
    void finishedBuildFilelist( bool );

private slots:
    int  chooseFile();
    int  chooseFiles();
    int  chooseFolder( const QString &Folder = "" );
    int  saveFile();
    int  saveFileAs();
    void hideWindow();
    void newWindow();
    int  saveDataFile();
    int  saveDataFileAs();
    void displayHelp();
    void about();
    void clearStatusMessage();

    void doReadData( bool reloadFile = false );
    void doReloadFile();
    void doSetEncodingDialog();
    void doSetPresetOptionsDialog();

    void doShowPlot();
    void doShowPlotV();
    void doShowPlotH();

    void doSavePlotBMP();
    void doSavePlotPDF();
    void doSavePlotPNG();
    void doSavePlotSVG();
    void doPrintPlot();

    void doShowDatasetDescription();
    void doPrintDatasetDescription();
    void doSaveDatasetDescriptionText();
    void doSaveDatasetDescriptionPDF();

    void doShowParameterStatistic();
    void doPrintParameterStatistic();
    void doSaveParameterStatisticText();
    void doSaveParameterStatisticPDF();

    void doSelectParametersDialog();

    void doPresetVR(); // vertical, reverse geocode range
    void doPresetVN(); // vertical
    void doPresetHR(); // horizontal, reverse geocode range
    void doPresetHN(); // horizontal
    void doPresetCM(); // marker color
    void doPresetCL(); // line color
    void doPresetCC(); // colorized color

    void doSetGraphicOptionsDialog();
    void doSetTickOptionsDialog();

    void doSetGlobalParameterOptionsDialog();
    void doSetParameterOptionsDialog();

    void doSetXAxisOptionsDialog();
    void doSetXAxisOptionsFloatDialog();
    void doSetXAxisOptionsDateTimeDialog();

private:
    QStringList expandCommandline();
    QStringList renameFiles( const QStringList Filename, const QString &searchStr, const QString &replaceStr );
    bool buildFilename( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QString &Filename, QString &FilenameIn, QString &FilenameOut );
    bool existsFirstFile( const int ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList );
    bool isEmptyLine( const QString &String );
    int NumOfSections( const QString &String );
    int buildFileList( QStringList &FilenameList, const QString &Filename, const bool extractZipFile = true );
    int calcFileSizeClass( const QString &FilenameIn, const int NumOfFiles, const int lowerLimit = 100, const int upperLimit = 1000 );
    int copyStringList( const QStringList InStringList, QStringList &OutStringList, const QString &s_Pattern = "*" );
    int emptyDir( const QString &Dir );
    int extractZipFile( const QString &Filename, const bool createNewDir = false, const bool delZipFile = false );
    int incFileProgress( const int NumOfFiles, const int FileNumber );
    int incProgress( const int NumOfFiles, const int Step );
    int readFile( const QString &FilenameIn, QStringList &Input, const int Codec = -1, const int NumOfFiles = 0, const qint64 Bytes = 0 );
    int removeFile( const QString &Filename );
    int downloadFile( const QString &Url, const QString &absoluteFilePath );
    unsigned int incProgress( const int NumOfFiles, const unsigned int filesize, const unsigned int length, const QString &InputStr );
    void appendItem( QStringList &List, const QString &Item, const QString &SS = "", const QString &RS = "" );
    void clearFilenameList( int &ActionNumber, QStringList &FilenameList );
    void clearList( QStringList& List );
    void clearMessage();
    void createActions();
    void createMenus();
    void createStatusBar( const bool showProgressBar );
    void endTool( const int err, const int stopProgress, int &ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList, const QString &doneMessage = "Done", const QString &canceledMessage = "Converter was canceled", const bool clearList = false, const bool incActionNumber = true );
    void initFileProgress( const int NumOfFiles, const QString &FilenameIn, const QString &MessageText );
    void initProgress( const int NumOfFiles, const QString &Filename, const QString &MessageText, const int totalNumberOfSteps );
    void initProgress( const int totalNumberOfSteps );
    void listDir( QStringList &Filename, const QString &Directory, const bool extractZipFile = true );
    void loadPreferences();
    void resetFileProgress( const int NumOfFiles );
    void resetProgress( const int NumOfFiles = 0 );
    void savePreferences();
    void setNormalCursor();
    void setStatusBar( const QString &Message = "", const int seconds = 0 );
    void setStatusBarFileInProgress( const QString &Filename, const QString &Message = "", const int i_seconds = 0 );
    void setWTitle( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList FilenameList );
    void setWaitCursor();
    void showFilenameList( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList FilenameList );
    void showList( const QStringList List );
    void showMessage( const QString &Message, QStringList &MessageList );
    void wait( const int msec );

    QString getApplicationName( const bool replaceUnderline = false );
    QString getDataLocation();
    QString getDocumentDir();
    QString getPreferenceFilename();
    QString getVersion();
    QString setEOLChar( const int EOL );
    QString setExtension( const int Extension );

    QMenu	*fileMenu;
    QMenu	*showMenu;
    QMenu   *optionMenu;
    QMenu   *presetMenu;
    QMenu	*helpMenu;

    QAction *newWindowAction;
    QAction *openFileAction;
    QAction *openFolderAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *hideWindowAction;
    QAction *savePlotBMPAction;
    QAction *savePlotPDFAction;
    QAction *savePlotPNGAction;
    QAction *savePlotSVGAction;
    QAction *printPlotAction;
    QAction *reloadFileAction;
    QAction *exitAction;
    QAction *showDatasetDescriptionAction;
    QAction *printDatasetDescriptionAction;
    QAction *saveDatasetDescriptionTextAction;
    QAction *saveDatasetDescriptionPDFAction;
    QAction *showParameterStatisticAction;
    QAction *printParameterStatisticAction;
    QAction *saveParameterStatisticTextAction;
    QAction *saveParameterStatisticPDFAction;
    QAction *showPlotVAction;
    QAction *showPlotHAction;
    QAction *selectParametersDialogAction;
    QAction *setEncodingDialogAction;
    QAction *presetVRAction;
    QAction *presetVNAction;
    QAction *presetHRAction;
    QAction *presetHNAction;
    QAction *presetCMAction;
    QAction *presetCLAction;
    QAction *presetCCAction;
    QAction *setGlobalParameterOptionsDialogAction;
    QAction *setGraphicOptionsDialogAction;
    QAction *setTickOptionsDialogAction;
    QAction *setXAxisOptionsDialogAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *showHelpAction;

    QAction *setParameterOptionsDialogAction[_MAX_NUM_OF_PARAMETERS_];
    QAction *separatorAction;

    QProgressDialog *ProgressDialog;
    QProgressDialog *FileProgressDialog;
    QProgressBar    *ProgressBar;
    QLabel          *StatusMessage;
    RenderArea      *renderArea;

    QStringListModel    *Model;
    QListView           *ListView;
    QTextEdit           *textViewer;
    QTableWidget        *DataDescriptionTable;
    QTableWidget        *ParameterTable;
    QScrollArea         *scrollArea;

    QPoint	posWindow;              //!< Position des Programmfensters.
    QSize	sizeWindow;             //!< Groesse des Programmfensters.

    QPoint	posDialog;              //!< Position der Dialoge.
    QSize	sizeParameterDialog;	//!< Groesse des Parameterdialogs.

    bool    ugpo;                   //!< Globale Parameter Options muessen gesetzt werden.
};

#endif
