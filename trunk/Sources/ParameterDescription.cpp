/* ParameterDescription.cpp   */
/* 2009-12-03                 */
/* Dr. Rainer Sieger          */

#include "ParameterDescription.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-03

ParameterDescription::ParameterDescription( const int i_ParameterID, const QString& s_ParameterName, const QString& s_ParameterUnit, const int i_startPos, const int i_Count )
{
    i    = i_ParameterID;
    name = s_ParameterName;
    unit = s_ParameterUnit;
    p    = i_startPos;
    c    = i_Count;
    min  = -9999;
    max  = 9999;
}

