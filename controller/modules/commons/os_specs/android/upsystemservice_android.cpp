//#include <QtAndroidExtras/QAndroidJniObject>
//#include <QtAndroidExtras/QAndroidJniEnvironment>

#include "system/upsystemservice.h"

//static bool alertViewCreate(QVariantMap data)
//{
//    QStringList buttons = data["buttons"].toStringList();

//    QAndroidJniObject title = QAndroidJniObject::fromString(data["title"].toString());
//    QAndroidJniObject message = QAndroidJniObject::fromString(data["message"].toString());

//    QAndroidJniEnvironment env;

//    // Initializing category filter
//    jobjectArray jButtons = (jobjectArray)env->NewObjectArray(buttons.length(), env->FindClass("java/lang/String"), NULL);
//    for (int i = 0; i < buttons.length(); i++) {
//        jstring s = env->NewStringUTF(buttons.at(i).toStdString().c_str());
//        env->SetObjectArrayElement(jButtons, i, s);
//        env->DeleteLocalRef(s);
//    }

//    // showAlert(String title, String message, String[] buttons)
//    QAndroidJniObject::callStaticMethod<void>("vn/com/vng/smartthings/SmartThingsMainActivity",
//                                              "showAlert",
//                                              "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;)V",
//                                              title.object<jstring>(),
//                                              message.object<jstring>(),
//                                              jButtons);
//    env->DeleteLocalRef(jButtons);
//    return true;
//}

void UPSystemService::initializeMessageHandler()
{
//    registerMessageHandler(alertViewCreate, UPServiceType::AlertView);
}
