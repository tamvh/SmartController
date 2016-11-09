#ifndef SMARTTHINGS_UPDATATABLE_P_H
#define SMARTTHINGS_UPDATATABLE_P_H

namespace DB {

class UPDataTable;
class UPDatabase;

class UPDataTablePrivate {
public:
    UPDataTablePrivate(UPDatabase *db) :
        database(db)
    {
    }

public:
    UPDatabase *database;
};

}
#endif // SMARTTHINGS_UPDATATABLE_P_H

