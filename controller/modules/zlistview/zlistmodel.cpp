#include "zlistmodel.h"
#include <QtQml>
#include "zlistdatamodel.h"
ZListModel::ZListModel()
{

}

void ZListModel::registerTypes()
{
    qmlRegisterType<ZListDataModel>("List", 0, 1, "ZListDataModel");
}
