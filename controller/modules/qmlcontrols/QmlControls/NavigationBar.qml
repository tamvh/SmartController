import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2 as QtControls
import QtQuick.Layouts 1.1
import QmlControls 0.1

import "./priv"

Rectangle {
  id: navigationBar

  // The tint color to apply to the navigation bar background. It is equivalent to color. It apply the naming convenient of UIKit
  property string tintColor : "#007aff"

  property alias barTintColor : navigationBar.color
  property string lineColor: "#acacac"
  property bool backButtonVisible : true
  // The view objects within NavigationView
  property ListModel views : ListModel{}

  // The top most navigation item
  property NavigationItem navigationItem : dummyNavigationItem
  property ListModel navigationItems : ListModel{}

  property NavigationBarTitleAttributes titleAttributes : NavigationBarTitleAttributes {}

  signal leftClicked()

  width: parent.width
//  height: Unit.dp(44)
  height: QmlDevice.screenFillStatusBar ? Unit.dp(44 + 20) : Unit.dp(44)
  color : "#f8f8f8"

  anchors.top: parent.top
  anchors.topMargin: 0
  anchors.right: parent.right
  anchors.rightMargin: 0
  anchors.left: parent.left
  anchors.leftMargin: 0

  NavigationItem {
    id : dummyNavigationItem
  }
  QtControls.StackView {
      id : stack
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.bottom: parent.bottom
      height : Unit.dp(44)
      delegate: NavigationBarTransition {}
  }

  Button {
    id: backButton
    width: Unit.dp(36)
    height: Unit.dp(44)
    anchors.left: parent.left
    anchors.leftMargin: Unit.dp(0)
    anchors.bottom: parent.bottom
    visible: navigationBar.backButtonVisible
    iconName: "arrows-right"
    rotation: 180
    iconColor: navigationBar.tintColor
    onClicked: {
      navigationBar.leftClicked();
    }
  }

  Repeater {
      id: viewsListener
      model : navigationBar.views
      delegate: Item {

          property var navigationItem : NavigationItem {}
          property color savedBarTintColor
          property color savedLineColor
          property  bool savedbackButtonVisible;
          Component {
              id: creator
              NavigationBarItem {
                  title: navigationItem.title
                  titleSize: Unit.sp(18)
                  backStage: index > 0
                  leftBarButtonItems: navigationItem.leftBarButtonItems
                  rightBarButtonItems: navigationItem.rightBarButtonItems
                  barTintColor : navigationBar.barTintColor
                  titleView.color: titleAttributes.textColor
                  lineColor: navigationBar.lineColor

              }
          }

          function place(parent,item) {
              item.parent = parent;
              item.anchors.centerIn = parent;
          }

          Component.onCompleted: {
              savedBarTintColor = navigationBar.barTintColor
              savedLineColor = navigationBar.lineColor
              savedbackButtonVisible = navigationBar.backButtonVisible;

              if (model.object.hasOwnProperty("navigationItem")) {
                  navigationItem = model.object.navigationItem;
              }

              navigationItems.append({ object: navigationItem});
              navigationBar.navigationItem = navigationItem;

              var object = creator.createObject(stack);

              if (navigationItem.leftBarButtonItem) {
                   navigationItem.leftBar = navigationItem.leftBarButtonItem;
              }

              if (navigationItem.rightBarButtonItem) {
                   navigationItem.rightBar = navigationItem.rightBarButtonItem;
              }

              if (navigationItem.rightBar) {
                  place(object.rightBar,navigationItem.rightBar);
              }

              if (navigationItem.leftBar) {
                  place(object.leftBar,navigationItem.leftBar);
              }

              if (navigationItem.barTintColor) {
                  navigationBar.barTintColor = navigationItem.barTintColor;
              }

               //if (navigationItem.backButtonVisible) {
                   navigationBar.backButtonVisible = navigationItem.backButtonVisible;
//              }

              if (navigationItem.lineColor) {
                  object.lineColor = navigationItem.lineColor;
              }
              if (navigationItem.titleColor) {
                  object.titleView.color = navigationItem.titleColor;
              }

              stack.push(object);
          }

          Component.onDestruction: {
              navigationBar.barTintColor = savedBarTintColor
              navigationBar.lineColor = savedLineColor
              navigationBar.backButtonVisible = savedbackButtonVisible
              stack.pop();
              navigationItems.remove(navigationItems.count - 1);
              if (navigationItems.count > 0)
                navigationBar.navigationItem = navigationItems.get(navigationItems.count - 1).object;
              else
                navigationBar.navigationItem = dummyNavigationItem;
          }
      }
  }


}
