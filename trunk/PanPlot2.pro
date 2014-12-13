# PanPlot - software to visualize profiles and core logs
# Rainer Sieger
# Alfred Wegener Institute, Bremerhaven, Germany
# last change: 2014-10-04

macx {
    # creating cache file
    cache()

    # Set SDK
    QMAKE_MAC_SDK = macosx10.10

    # Only Intel binaries are accepted so force this
    CONFIG += x86_64

    # Minimum OS X version for submission is 10.6.6
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6

    # Icon
    ICON = ./Resources/icon/Application.icns

    # Replace default Info.plist
    QMAKE_INFO_PLIST = ./Resources/Info.plist

    QMAKE_CFLAGS += -gdwarf-2
    QMAKE_CXXFLAGS += -gdwarf-2
    QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_OBJECTIVE_CFLAGS_RELEASE =  $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
}

win32 {
    # Icon
    RC_FILE = ./Resources/Application.rc
}

linux-g++ {
}

TARGET = PanPlot2
TEMPLATE = app

QT += svg widgets network printsupport

INCLUDEPATH += ./Headers

HEADERS = \
    ./Headers/Application.h \
    ./Headers/Globals.h \
    ./Headers/Webfile.h \
    ./Headers/DataItem.h \
    ./Headers/PlotSettings.h \
    ./Headers/Plotter.h \
    ./Forms/AboutDialog/AboutDialog.h \
    ./Forms/SelectParametersDialog/SelectParametersDialog.h \
    ./Forms/SetEncodingDialog/SetEncodingDialog.h \
    ./Forms/SetGraphicOptionsDialog/SetGraphicOptionsDialog.h \
    ./Forms/SetParameterOptionsDialog/SetGlobalParameterOptionsDialog.h \
    ./Forms/SetParameterOptionsDialog/SetParameterOptionsDialog.h \
    ./Forms/SetPresetOptionsDialog/SetPresetOptionsDialog.h \
    ./Forms/SetTickOptionsDialog/SetTickOptionsDialog.h \
    ./Forms/SetXAxisOptionsDialog/SetXAxisOptionsFloatDialog.h \
    ./Forms/SetXAxisOptionsDialog/SetXAxisOptionsDateTimeDialog.h

SOURCES = \
    ./Sources/ApplicationCreateMenu.cpp \
    ./Sources/ApplicationErrors.cpp \
    ./Sources/ApplicationInit.cpp \
    ./Sources/ApplicationMainWindow.cpp \
    ./Sources/ApplicationPreferences.cpp \
    ./Sources/ApplicationTools.cpp \
    ./Sources/DataFile.cpp \
    ./Sources/PlotSettings.cpp \
    ./Sources/DataItem.cpp \
    ./Sources/NiceLabel.cpp \
    ./Sources/readData.cpp \
    ./Sources/setXAxisOptionsDialog.cpp \
    ./Sources/showDatasetDescription.cpp \
    ./Sources/showParameterStatistic.cpp \
    ./Sources/Plotter.cpp \
    ./Sources/preset.cpp \
    ./Sources/Webfile.cpp \
    ./Forms/AboutDialog/AboutDialog.cpp \
    ./Forms/SelectParametersDialog/SelectParametersDialog.cpp \
    ./Forms/SetEncodingDialog/SetEncodingDialog.cpp \
    ./Forms/SetGraphicOptionsDialog/SetGraphicOptionsDialog.cpp \
    ./Forms/SetParameterOptionsDialog/SetGlobalParameterOptionsDialog.cpp \
    ./Forms/SetParameterOptionsDialog/SetParameterOptionsDialog.cpp \
    ./Forms/SetPresetOptionsDialog/SetPresetOptionsDialog.cpp \
    ./Forms/SetTickOptionsDialog/SetTickOptionsDialog.cpp \
    ./Forms/SetXAxisOptionsDialog/SetXAxisOptionsFloatDialog.cpp \
    ./Forms/SetXAxisOptionsDialog/SetXAxisOptionsDateTimeDialog.cpp

FORMS = \
    ./Forms/AboutDialog/aboutdialog.ui \
    ./Forms/SelectParametersDialog/selectparametersdialog.ui \
    ./Forms/SetPresetOptionsDialog/setpresetoptionsdialog.ui \
    ./Forms/SetEncodingDialog/setencodingdialog.ui \
    ./Forms/SetGraphicOptionsDialog/setgraphicoptionsdialog.ui \
    ./Forms/SetParameterOptionsDialog/setglobalparameteroptionsdialog.ui  \
    ./Forms/SetParameterOptionsDialog/setparameteroptionsdialog.ui  \
    ./Forms/SetTickOptionsDialog/settickoptionsdialog.ui \
    ./Forms/SetXAxisOptionsDialog/setxaxisoptionsfloatdialog.ui \
    ./Forms/SetXAxisOptionsDialog/setxaxisoptionsdatetimedialog.ui
