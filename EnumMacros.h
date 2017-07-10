#ifndef _ENUMMACROS_H
#define _ENUMMACROS_H


#define DECLARE_ENUM1(name) \
    name,

#define DECLARE_ENUM2(name, val) \
    name = val,

#define DECLARE_ENUM_TO_STRING(name) \
        static name name##FromString(const std::string &s); \
        static std::string name##ToString(name e);

#define DECLARE_ENUM_LIST(name, a) \
    public: \
        enum name { \
        a(DECLARE_ENUM1, DECLARE_ENUM2) \
        };\
        DECLARE_ENUM_TO_STRING(name)


#define IMPLEMENT_ENUM_STRING_SWITCH(name) \
    case name: \
        sRet = #name;\
        break;

#define IMPLEMENT_STRING_ENUM_IF(name) \
    else if (s == #name) {\
        eRet = name;\
    }

#define IMPLEMENT_ENUM_STRING_SWITCH2(name, num) \
    IMPLEMENT_ENUM_STRING_SWITCH(name)\

#define IMPLEMENT_STRING_ENUM_IF2(name, num) \
    IMPLEMENT_STRING_ENUM_IF(name)\

#define IMPLEMENT_ENUM_TO_STRING(object, name, default_name, default_string, e_list) \
    object::name object::name##FromString(const std::string &s) {\
        name eRet = default_name;\
        if (s == default_string) {\
            eRet = default_name;\
        }\
        e_list(IMPLEMENT_STRING_ENUM_IF, IMPLEMENT_STRING_ENUM_IF2)\
        return eRet;\
    }\
    std::string object::name##ToString(object::name e) { \
        std::string sRet = default_string;\
        switch (e) {\
        e_list(IMPLEMENT_ENUM_STRING_SWITCH, IMPLEMENT_ENUM_STRING_SWITCH2) \
        }\
        return sRet;\
    }



#endif
