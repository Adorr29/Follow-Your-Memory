/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Error.hpp
*/

#pragma once

#include <exception>
#include <string>

using namespace std;

class Error : public exception
{
public:
    Error(const string &_message);
    const char *what() const throw();

private:
    const string message;
};
