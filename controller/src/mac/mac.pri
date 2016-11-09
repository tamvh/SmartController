INCLUDEPATH += $$PWD

LIBS += -framework AVFoundation -framework Cocoa
OTHER_FILES += $$PWD/Info.plist
#QMAKE_INFO_PLIST = $$PWD/Info.plist

# Copy the custom Info.plist to the app bundle
#plist.path = "$$DESTDIR/$$join(TARGET,,,.app)/Contents"
plist.path = "$$DESTDIR/Contents"
plist.files = $$PWD/Info.plist
QMAKE_BUNDLE_DATA += plist
