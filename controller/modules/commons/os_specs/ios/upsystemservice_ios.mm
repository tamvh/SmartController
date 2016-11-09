
#include <QCoreApplication>
#include <UIKit/UIKit.h>
#include "system/upsystemservice.h"

//static bool presentLocalNotification(QVariantMap data) {
//    UILocalNotification *notification = [UILocalNotification new];

//    // Notification details
//    notification.alertBody = data["message"].toString().toNSString();
//    notification.alertAction = NSLocalizedString(@"View Details", nil);
//    notification.soundName = UILocalNotificationDefaultSoundName;

//    [[UIApplication sharedApplication] presentLocalNotificationNow:notification];
//    return true;
//}

void UPSystemService::initializeMessageHandler()
{
//    registerMessageHandler(presentLocalNotification, UPServiceType::PresentLocalNotification);
}
