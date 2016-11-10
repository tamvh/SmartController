INCLUDEPATH += $$PWD

ios: {
    OBJECTIVE_SOURCES += $$PWD/os_specs/ios/upsystemservice_ios.mm \
                        $$PWD/os_specs/ios/QIOSApplicationDelegate+Extension.mm
    OBJECTIVE_HEADERS += $$PWD/os_specs/ios/qiosapplicationdelegate.h \
                        $$PWD/os_specs/ios/QIOSApplicationDelegate+Extension.h
}
macx: {
    OBJECTIVE_SOURCES += $$PWD/os_specs/mac/upsystemservice_mac.mm
}
android: {
    SOURCES += $$PWD/os_specs/android/upsystemservice_android.cpp
}


SOURCES += \
    $$PWD/users/zuserinfo.cpp \
    $$PWD/db/globalparameter.cpp \
    $$PWD/db/updatabase.cpp \
    $$PWD/db/updatatable.cpp \
    $$PWD/db/updbglobalconfigurationstable.cpp \
    $$PWD/system/upsystemservice.cpp \
    $$PWD/system/upsystemsettings.cpp \
    $$PWD/utils/textnormalizer.cpp \
    $$PWD/utils/stringutil.cpp \
    $$PWD/networks/core/httpjsonresponse.cpp \
    $$PWD/networks/core/httprequest.cpp \
    $$PWD/networks/core/networkerrorresponse.cpp \
    $$PWD/networks/core/networkmanager.cpp \
    $$PWD/networks/core/networkrequest.cpp \
    $$PWD/networks/core/networkresponse.cpp \
    $$PWD/networks/core/httpclient.cpp

HEADERS += \
    $$PWD/users/zuserinfo.h \
    $$PWD/db/globalparameter.h \
    $$PWD/db/updatabase.h \
    $$PWD/db/updatatable.h \
    $$PWD/db/updatatable_p.h \
    $$PWD/db/updbglobalconfigurationstable.h \
    $$PWD/system/singleton.h \
    $$PWD/system/upsystemservice.h \
    $$PWD/system/upsystemsettings.h \
    $$PWD/utils/textnormalizer.h \
    $$PWD/utils/stringutil.h \
    $$PWD/networks/core/httpjsonresponse.h \
    $$PWD/networks/core/httprequest.h \
    $$PWD/networks/core/networkerror.h \
    $$PWD/networks/core/networkerrorresponse.h \
    $$PWD/networks/core/networkmanager.h \
    $$PWD/networks/core/networkrequest.h \
    $$PWD/networks/core/networkresponse.h \
    $$PWD/networks/core/httpclient.h

