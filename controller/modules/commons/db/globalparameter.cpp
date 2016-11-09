#include <QVariant>

#include "globalparameter.h"

#include "updatabase.h"
#include "updbglobalconfigurationstable.h"

DB::UPDatabase *getApplicationDB();

GlobalParameterBase::GlobalParameterBase(const QString &key, const QVariant& defaultValue) :
    m_value(defaultValue),
    m_hasValue(false),
    m_key(key)
{
}

QVariant GlobalParameterBase::value()
{
    if (!m_hasValue) {
        UPDBGlobalConfigurationsTable db(getApplicationDB());
        m_value = db.getValue(m_key, m_value);
        m_hasValue = true;
    }
    return m_value;
}

void GlobalParameterBase::setValue(const QVariant& v)
{
    if (m_value == v) {
        return;
    }

    UPDBGlobalConfigurationsTable db(getApplicationDB());
    db.setValue(m_key, v);
    m_value = v;
    m_hasValue = true;
}

struct GlobalParameterSet::Private {
    typedef std::shared_ptr<UPDBGlobalConfigurationsTable> DataTableTypePtr;
    DataTableTypePtr dataTable;
};

GlobalParameterSet::GlobalParameterSet(const QString &group) :
    m_group(group),
    d(new Private)
{
}

QVariant GlobalParameterSet::value(const QString &key)
{
    if (!d->dataTable) {
        d->dataTable = Private::DataTableTypePtr(new UPDBGlobalConfigurationsTable(getApplicationDB()));
    }
    return d->dataTable->getValue(m_group + "_" + key, QVariant());
}

void GlobalParameterSet::setValue(const QString &key, const QVariant& v)
{
    if (!d->dataTable) {
        d->dataTable = Private::DataTableTypePtr(new UPDBGlobalConfigurationsTable(getApplicationDB()));
    }
    d->dataTable->setValue(m_group + "_" + key, v);
}
