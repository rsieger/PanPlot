#!/bin/bash
echo
echo PanPlot2

echo - macdeployqt 

cd ~/Development/aforge/panplot2

rm -R '../../Distribution/PanPlot2/PanPlot2.app'
cp -R './PanPlot2-build-Desktop_Qt_5_3_2_LLDB-Release/PanPlot2.app' '../../Distribution/PanPlot2/PanPlot2.app'
cp './trunk/Resources/Info.plist' '../../Distribution/PanPlot2/PanPlot2.app/Contents/Info.plist'

/Developer/Qt/5.3/clang_64/bin/macdeployqt '../../Distribution/PanPlot2/PanPlot2.app'

../patchQtFramework.sh '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtCore.framework'
../patchQtFramework.sh '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtGui.framework'
../patchQtFramework.sh '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtNetwork.framework'
../patchQtFramework.sh '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtPrintSupport.framework'
../patchQtFramework.sh '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtSvg.framework'
../patchQtFramework.sh '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtWidgets.framework'

echo - code signing

codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtCore.framework'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtGui.framework'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtNetwork.framework'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtPrintSupport.framework'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtSvg.framework'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/Frameworks/QtWidgets.framework'

codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/accessible/libqtaccessiblewidgets.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/bearer/libqcorewlanbearer.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/bearer/libqgenericbearer.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqdds.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqgif.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqicns.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqico.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqjp2.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqjpeg.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqmng.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqtga.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqtiff.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqsvg.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqsvg_debug.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqwbmp.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/imageformats/libqwebp.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/platforms/libqcocoa.dylib'
codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app/Contents/PlugIns/printsupport/libcocoaprintersupport.dylib'

codesign --force --verify --sign 'Developer ID Application: Alfred-Wegener-Institut fur Polar- und Meeresforschung (AWI)' '../../Distribution/PanPlot2/PanPlot2.app' # --entitlements './trunk/Resources/PanPlot2.entitlements'

echo - mount package

cd ~/Development/Distribution/PanPlot2
hdiutil attach ~/Development/Distribution/PanPlot2_OSX.dmg

rm -R '/Volumes/PanPlot/PanPlot2.app'
cp -R PanPlot2.app '/Volumes/PanPlot'

cd '/Volumes/PanPlot'
rm -rf .fseventsd
mkdir .fseventsd
touch .fseventsd/no_log
cd ~/Development/Distribution

echo - verify package

codesign -dvv '/Volumes/PanPlot/PanPlot2.app'

echo
hdiutil detach '/Volumes/PanPlot'
