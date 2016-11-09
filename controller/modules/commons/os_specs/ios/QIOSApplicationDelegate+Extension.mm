#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import"QIOSApplicationDelegate+Extension.h"

@implementation QIOSApplicationDelegate (Extension)
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    Q_UNUSED(launchOptions);
    [application setMinimumBackgroundFetchInterval:UIApplicationBackgroundFetchIntervalMinimum];
    // Override point for customization after application launch.

    // iOS 8+ app must register for presenting local notification first
    if ([UIApplication instancesRespondToSelector:@selector(registerUserNotificationSettings:)]) {
        [application registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert|UIUserNotificationTypeBadge|UIUserNotificationTypeSound categories:nil]];
    }

    NSLog(@"Application did finish launching");
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    Q_UNUSED(application);
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    NSLog(@"Application will resign active");
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    Q_UNUSED(application);
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    NSLog(@"In the background");
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    Q_UNUSED(application);
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    NSLog(@"In the foreground");
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    Q_UNUSED(application);
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    NSLog(@"Application did become active");
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    Q_UNUSED(application);
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

-(void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler{
    // We will add content here soon.
    Q_UNUSED(application);
    Q_UNUSED(completionHandler);
    NSLog(@"In the completionHandler");
}
@end
