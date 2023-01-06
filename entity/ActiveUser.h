#ifndef ACTIVEUSER_H
#define ACTIVEUSER_H

#include <string>


class ActiveUser
{
public:
    ActiveUser();
    std::string toJson();
    ActiveUser* setName();
    ActiveUser* setSurname();
    ActiveUser* setEmail();
    ActiveUser* setPassword();
};

#endif // ACTIVEUSER_H
