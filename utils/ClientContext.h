#ifndef CLIENTCONTEXT_H
#define CLIENTCONTEXT_H

#include <string>
#include <QString>

class ClientContext
{
public:
    static void setName(QString name) { ClientContext::name = name; };
    static void setSurname(QString surname) { ClientContext::surname = surname; };
    static void setEmail(QString email) { ClientContext::email = email; };
    static void setPassword(QString password) { ClientContext::password = password; };
    static void setUuid(QString uuid) { ClientContext::uuid = uuid; };

    static QString getName() { return ClientContext::name; };
    static QString getSurname() { return ClientContext::surname; };
    static QString getEmail() { return ClientContext::email; };
    static QString getPassword() { return ClientContext::password; };
    static QString getUuid() { return ClientContext::uuid; };

private:
    static QString name;
    static QString surname;
    static QString email;
    static QString password;
    static QString uuid;
};

#endif // CLIENTCONTEXT_H
