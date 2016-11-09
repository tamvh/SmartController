#ifndef QMLCONTROLS_H
#define QMLCONTROLS_H

class QQuickWindow;
class QmlControls
{
public:
  static void registerTypes();

  /// Setup the QQuickWindow instance of the application according to the environment
  /**
   *
   * @brief setupWindow
   * @param window
   */
  static void setupWindow(QQuickWindow* window);

  enum StatusBarStyle {
      StatusBarStyleDefault,
      StatusBarStyleLightContent,
      StatusBarStyleBlackTranslucent,
      StatusBarStyleBlackOpaque
  };

  static void setStatusBarStyle(StatusBarStyle style);
};

#endif // QMLCONTROLS_H
