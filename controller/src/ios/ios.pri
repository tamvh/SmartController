INCLUDEPATH += $$PWD
#LIBS += -framework CoreBluetooth
OTHER_FILES += $$PWD/Info.plist
QMAKE_INFO_PLIST = $$PWD/Info.plist
#QMAKE_XCODE_CODE_SIGN_IDENTITY = "iPhone Developer"
#IOS_DEPLOY_FILES = $$PWD/MyLaunchScreen.nib
QMAKE_PRODUCT_BUNDLE_IDENTIFIER = "vn.com.vng.smartlamp.hoanh"
QMAKE_XCODE_CODE_SIGN_IDENTITY = "iPhone Developer"
QMAKE_IOS_DEPLOYMENT_TARGET = "8.0"

#deployment.files = $$IOS_DEPLOY_FILES
#deployment.path = .
#QMAKE_BUNDLE_DATA += deployment

    # Set up default LaunchScreen to support iPhone6/6+
#    launch_screen = LaunchScreen.xib
#    copy_launch_screen.input = $$QMAKESPEC/$$launch_screen
#    copy_launch_screen.output = $$OUT_PWD/$${TARGET}.xcodeproj/$$launch_screen
#    QMAKE_SUBSTITUTES += copy_launch_screen
#    launch_screens.files = $$copy_launch_screen.output
#    QMAKE_BUNDLE_DATA += launch_screens

SOURCES +=

OBJECTIVE_SOURCES += \
