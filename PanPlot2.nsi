; Script nerated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "PanPlot2"
!define PRODUCT_VERSION "14.4"
!define PRODUCT_PUBLISHER "PANGAEA"
!define PRODUCT_WEB_SITE "http://www.pangaea.de"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\PanPlot2.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\License\License.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\PanPlot2.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2_Win.exe"
InstallDir "$PROGRAMFILES\PANGAEA\PanPlot2"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show
RequestExecutionLevel admin

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\PanPlot2.exe"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Qt5Core.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Qt5Gui.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Qt5Network.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Qt5Widgets.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Qt5PrintSupport.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Qt5Svg.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\icudt54.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\icuin54.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\icuuc54.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\libgcc_s_dw2-1.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\libstdc++-6.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\libwinpthread-1.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\libeay32.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\ssleay32.dll"

  SetOutPath "$INSTDIR\platforms"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\platforms\qminimal.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\platforms\qwindows.dll"
  
  SetOutPath "$INSTDIR\Examples"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Examples\PanPlot2.png"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Examples\Demo1.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Examples\Demo2.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Examples\Demo3.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\Examples\Demo4.txt"
  
  SetOutPath "$INSTDIR\License"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\License\gpl-3.0.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\License\License.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\PanPlot2\License\Readme.txt"
  
  CreateDirectory "$SMPROGRAMS\PANGAEA"
  CreateDirectory "$SMPROGRAMS\PANGAEA\PanPlot2"
  CreateShortCut "$SMPROGRAMS\PANGAEA\PanPlot2\PanPlot2.lnk" "$INSTDIR\PanPlot2.exe"
  CreateShortCut "$DESKTOP\PanPlot2.lnk" "$INSTDIR\PanPlot2.exe"
SectionEnd

Section -AdditionalIcons
  CreateShortCut "$SMPROGRAMS\PANGAEA\PanPlot2\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\PanPlot2.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\PanPlot2.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\PanPlot2.exe"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Network.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\Qt5PrintSupport.dll"
  Delete "$INSTDIR\Qt5Svg.dll"
  Delete "$INSTDIR\icudt54.dll"
  Delete "$INSTDIR\icuin54.dll"
  Delete "$INSTDIR\icuuc54.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\libeay32.dll"
  Delete "$INSTDIR\ssleay32.dll"
  Delete "$INSTDIR\platforms\qminimal.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\License\Readme.txt"
  Delete "$INSTDIR\License\License.txt"
  Delete "$INSTDIR\License\gpl-3.0.txt"
  Delete "$INSTDIR\Examples\PanPlot2.png"
  Delete "$INSTDIR\Examples\Demo1.txt"
  Delete "$INSTDIR\Examples\Demo2.txt"
  Delete "$INSTDIR\Examples\Demo3.txt"
  Delete "$INSTDIR\Examples\Demo4.txt"

  Delete "$SMPROGRAMS\PANGAEA\PanPlot2\Uninstall.lnk"
  Delete "$SMPROGRAMS\PANGAEA\PanPlot2\PanPlot2.lnk"
  Delete "$DESKTOP\PanPlot2.lnk"

  RMDir "$SMPROGRAMS\PANGAEA\PanPlot2"
  RMDir "$INSTDIR\Examples"
  RMDir "$INSTDIR\License"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd
