/* splitInput.cpp             */
/* 2009-12-03                 */
/* Dr. Rainer Sieger          */

#include <QApplication>

#include "Application.h"

int MainWindow::splitInput( const QString &s_FilenameIn, const int m, QStringList &sl_Input, QStringList &sl_DataDescription, QStringList &sl_Data, const int i_NumOfFiles )
{
    int i               = 0;
    int i_stopProgress  = 0;

// **********************************************************************************************

    if ( ( sl_Input.filter( "/*" ).isEmpty() == FALSE ) || ( sl_Input.filter( "//" ).isEmpty() == FALSE ) )
    {
        initProgress( i_NumOfFiles, s_FilenameIn, tr( "Checking data..." ), m );

        while ( ( i < m ) && ( i_stopProgress != APPBREAK ) )
        {
            if ( sl_Input.at( i ).startsWith( "/*" ) == TRUE )
            {
                while ( sl_Input.at( i ).startsWith( "*/" ) == FALSE )
                    sl_DataDescription.append( sl_Input.at( i++ ) );
                sl_DataDescription.append( sl_Input.at( i++ ) );
            }

            while ( sl_Input.at( i ).startsWith( "//" ) == TRUE )
                sl_DataDescription.append( sl_Input.at( i++ ) );

            sl_Data.append( sl_Input.at( i ) );

            i_stopProgress = incProgress( i_NumOfFiles, i++ );
        }

        resetProgress( i_NumOfFiles );
    }
    else
    {
        sl_Data = sl_Input;
    }

    sl_Input.clear();

    return( i_stopProgress );
}
