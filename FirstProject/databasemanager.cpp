#include "databasemanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager inst;
    return inst;
}

bool DatabaseManager::initialize() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("hinton_market.db");  // relative to working dir

    if (!m_db.open()) {
        qCritical() << "Cannot open DB:" << m_db.lastError().text();
        return false;
    }

    // Only run schema.sql if this is a fresh DB (tables don't exist yet)
    QSqlQuery check(m_db);
    check.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='Users'");
    if (!check.next()) {
        qDebug() << "New database — running schema.sql...";
        runSchemaFile(":/schema.sql");  // embedded as Qt resource (see Step 3)
    } else {
        qDebug() << "Existing database loaded.";
    }

    m_db.exec("PRAGMA foreign_keys = ON");
    return true;
}

bool DatabaseManager::runSchemaFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Cannot open schema file:" << path;
        return false;
    }
    QString sql = QTextStream(&file).readAll();
    // Split on ";" to execute statements individually
    QStringList statements = sql.split(";", Qt::SkipEmptyParts);
    for (const QString& stmt : statements) {
        QString trimmed = stmt.trimmed();
        if (!trimmed.isEmpty()) {
            QSqlQuery q(m_db);
            if (!q.exec(trimmed)) {
                qWarning() << "SQL error:" << q.lastError().text() << "\n" << trimmed;
            }
        }
    }
    return true;
}

QSqlDatabase& DatabaseManager::db() {
    return m_db;
}
