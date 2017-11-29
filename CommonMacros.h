/* Copyright (C) 2017 Alexander Downey */
#ifndef _COMMONMACROS_H
#define _COMMONMACROS_H

#define GETSET(name, type, value) \
    void set##name(type value) { this->value = value; }\
    type get##name() const { return this->value; }\
protected:\
    type value;\
public:


#define GETSETRET(name, type, value) \
    type set##name(type value) { return this->value = value; }\
    type get##name() const { return this->value; }\
protected:\
    type value;\
public:

#endif
