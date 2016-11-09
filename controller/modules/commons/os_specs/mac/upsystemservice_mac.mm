
#include <QCoreApplication>
#include <AppKit/AppKit.h>
#include "system/upsystemservice.h"

//static bool alertViewCreate(QVariantMap data) {
//    Q_UNUSED(data);

//    NSString* title = data["title"].toString().toNSString();
//    NSString* message = data["message"].toString().toNSString();
//    QStringList buttons = data["buttons"].toStringList();

//    NSAlert *alert = [[NSAlert alloc] init];
//    for (int i = 0 ; i < buttons.size();i++) {
//        NSString *btn = buttons.at(i).toNSString();
//        [alert addButtonWithTitle:btn];
//    }
//    [alert setMessageText:title];
//    [alert setInformativeText:message];
//    [alert setAlertStyle:NSWarningAlertStyle];

//    NSModalResponse buttonIndex = [alert runModal];
//    buttonIndex = buttonIndex - NSAlertFirstButtonReturn;

//    UPServiceType name = UPServiceType::AlertView;
//    QVariantMap dataFeedback;
//    dataFeedback["buttonIndex"] = (int)buttonIndex;
//    QMetaObject::invokeMethod(UPSystemService::instance(), "received", Qt::DirectConnection,
//                              Q_ARG(UPServiceType, name),
//                              Q_ARG(QVariantMap, dataFeedback));
//    [alert release];

//    return true;
//}

void UPSystemService::initializeMessageHandler()
{
//    registerMessageHandler(alertViewCreate, UPServiceType::AlertView);
}


