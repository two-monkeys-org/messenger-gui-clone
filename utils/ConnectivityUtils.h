#ifndef CONNECTIVITYUTILS_H
#define CONNECTIVITYUTILS_H

#include <QString>
#include <map>
#include <utils/ClientContext.h>
#include <QNetworkReply>

// @Depricated
namespace Utils{
    enum JSON_TYPE {
        FULL,
        SIMPLE,
        AUTHORIZATION,
        INFOMRATION
    };

    enum HTTP_TYPE {
        FETCH_CONVERSATIONS,
        FETCH_MESSAGES,
        CREATE_CONVERSATION,
        FETCH_USERS,
        NOT_FOUND,
    };

    QString FullMapper();
    QString SimpleMapper();
    QString AuthorizationMapper();
    QString InformationMapper();
    QString buildWithNamespace(std::string, JSON_TYPE);
    Utils::HTTP_TYPE retrieveHeader(QNetworkReply*, std::string);
    Utils::HTTP_TYPE retrieveHeader(QNetworkReply*, HTTP_TYPE);

    static std::map<JSON_TYPE, QString(*)()> jsonMapperToStringMap {
        {FULL, FullMapper},
        {SIMPLE, SimpleMapper},
        {AUTHORIZATION, AuthorizationMapper},
        {INFOMRATION, InformationMapper},
    };

    static std::map<std::string, HTTP_TYPE> httpHeaderMapStrKey {
        {"FETCH_CONVERSATIONS", FETCH_CONVERSATIONS},
        {"FETCH_MESSAGES", FETCH_MESSAGES},
        {"CREATE_CONVERSATION", CREATE_CONVERSATION},
        {"FETCH_USERS", FETCH_USERS},
    };

    static std::map<HTTP_TYPE, std::string> httpHeaderMapStructKey {
        {FETCH_CONVERSATIONS, "FETCH_CONVERSATIONS"},
        {FETCH_MESSAGES, "FETCH_MESSAGES"},
        {CREATE_CONVERSATION, "CREATE_CONVERSATION"},
        {FETCH_USERS, "FETCH_USERS"},
    };
}

#endif // CONNECTIVITYUTILS_H
