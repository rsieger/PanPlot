#ifndef _GLOBALS

    #define _GLOBALS

// Application constants

    const QString _PROGRAMDOI_            = "doi:10.1594/PANGAEA.816201";
    const QString _PROGRAMREADME_         = "http://wiki.pangaea.de/wiki/PanPlot";

    const QString _VERSION_               = "14.4";     // Version number, 2015-12-28
    const QString _DATAFORMATVERSION_     = "1.2";      // Data format version, 2013-10-12
    const QChar   _PSEPARATOR_            = '|';

    const int   _NOERROR_                 = 0;
    const int   _ERROR_                   = 1;
    const int   _APPBREAK_                = 2;
    const int   _NODATAFOUND_             = 3;
    const int   _DATAFOUND_               = 4;
    const int   _CHOOSEABORTED_           = 5;
    const int   _FILENOEXISTS_            = 6;
    const int   _PRINTCANCELED_           = 101;

    const int   _ZIP_                     = 1;
    const int   _GZIP_                    = 2;

// EOL
    const int   _UNIX_                    = 0;    // LF
    const int   _MACOS_                   = 1;    // CR
    const int   _WIN_                     = 2;    // CR+LF

// Encoding
    const int   _SYSTEM_                  = -1;   // System
    const int   _UTF8_                    = 0;    // UTF-8
    const int   _APPLEROMAN_              = 1;    // Apple Roman
    const int   _LATIN1_                  = 2;    // Latin-1 = ISO 8859-1

// Extension
    const int   _TXT_                     = 0;
    const int   _CSV_                     = 1;

// Constants
    const int _MAX_NUM_OF_PARAMETERS_     = 1000;

    const int _SHOWLIST_                  = 0;
    const int _SHOWDATADESCRIPTIONTABLE_  = 1;
    const int _SHOWPARAMETERTABLE_        = 2;
    const int _SHOWPLOTV_                 = 3;
    const int _SHOWPLOTH_                 = 4;

    const int _PRINTLIST_                 = 10;
    const int _PRINTDATADESCRIPTIONTABLE_ = 11;
    const int _PRINTPARAMETERTABLE_       = 12;
    const int _PRINTPLOT_                 = 13;

    const int _SAVELIST_                  = 20;
    const int _SAVEDATADESCRIPTIONTABLE_  = 21;
    const int _SAVEPARAMETERTABLE_        = 22;
    const int _SAVEPLOT_                  = 23;

    const int _FORMATNULL_                = 0;
    const int _FORMATTEXT_                = 1;
    const int _FORMATPDF_                 = 2;
    const int _FORMATPNG_                 = 3;
    const int _FORMATBMP_                 = 4;
    const int _FORMATSVG_                 = 5;
    const int _FORMATPRINT_               = 6;

    const int _FORMATISODATETIME_         = 0;
    const int _FORMATYEAR_                = 1;
    const int _FORMATYEARMONTH_           = 2;
    const int _FORMATISODATE_             = 3;
    const int _FORMATISODATETIMESECS_     = 4;

#endif
