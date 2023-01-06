#include "ConnectivityUtils.h"


QString Utils::FullMapper() {
    return "{\
            \"email\":\"" + ClientContext::getEmail() + "\", \
            \"name\":\"" + ClientContext::getName() + "\", \
            \"surname\":\"" + ClientContext::getSurname() + "\", \
            \"password\":\"" + ClientContext::getPassword() + "\" \
            }";
}


QString Utils::SimpleMapper() {
    return "{\
            \"email\":\"" + ClientContext::getEmail() + "\", \
            \"name\":\"" + ClientContext::getName() + "\", \
            \"surname\":\"" + ClientContext::getSurname() + "\" \
            }";
}


QString Utils::AuthorizationMapper() {
    return "{\
            \"email\":\"" + ClientContext::getEmail() + "\", \
            \"password\":\"" + ClientContext::getPassword() + "\" \
            }";
}


QString Utils::InformationMapper() {
    return "{\
            \"email\":\"" + ClientContext::getEmail() + "\", \
            \"name\":\"" + ClientContext::getName() + "\", \
            \"surname\":\"" + ClientContext::getSurname() + "\" \
            }";
}


QString Utils::buildWithNamespace(std::string nmspc, Utils::JSON_TYPE type) {
    QString res = jsonMapperToStringMap[type]();

    return QString::fromStdString("{\"namespace\":\"" + nmspc + "\", \"payload\": ") + res + "}";
}


Utils::HTTP_TYPE Utils::retrieveHeader(QNetworkReply* response, std::string expected) {
    return httpHeaderMapStrKey[response->rawHeader(QByteArray::fromStdString("NAMESPACE")).toStdString()];
}


Utils::HTTP_TYPE Utils::retrieveHeader(QNetworkReply* response, HTTP_TYPE expected) {
    foreach(QByteArray header, response->rawHeaderList()) {
        std::string strHeader = header.toStdString();
        qDebug() << header;

        if(strHeader == httpHeaderMapStructKey[expected]) {
            return httpHeaderMapStrKey[strHeader];
        }
    }
}

