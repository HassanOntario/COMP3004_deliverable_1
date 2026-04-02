#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QString>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool initialize();           // call once at startup
    QSqlDatabase& db();

private:
    DatabaseManager() = default;
    QSqlDatabase m_db;
    bool runSchemaFile(const QString& path);
};

#endif
