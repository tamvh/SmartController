#include <UIKit/UIKit.h>
#include <QDebug>

bool ios_applicationSetStatusBarStyle(int style) {
    [[UIApplication sharedApplication] setStatusBarStyle:(UIStatusBarStyle) style];
    return true;
}

void ios_applicationSetStatusBarHidden(bool hidden) {
    [[UIApplication sharedApplication] setStatusBarHidden:hidden withAnimation:UIStatusBarAnimationNone];
}
