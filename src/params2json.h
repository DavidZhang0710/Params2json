#ifndef PARAMS2JSON_H
#define PARAMS2JSON_H

# include "json/json.h"

template <typename T>
struct add_const_if_const {
    using type = T;
};

template <typename T>
struct add_const_if_const<const T> {
    using type = const T;
};

template <typename T>
struct add_const_auto {
    using type = typename std::conditional<std::is_class<T>::value || std::is_enum<T>::value || std::is_same<T,uint32_t>::value ,
                                           const T, typename add_const_if_const<T>::type>::type;
};

#define DECLARE_MEMBER(member_name, member_type) \
    member_type member_name;                     \
    constexpr static const char* member_name##_name = #member_name;

#define STRUCT_WITH_5MEMBERS(func, a_type, a, b_type, b, c_type, c, d_type, d, e_type, e)              \
    namespace params2json {                                                                                \
    struct func##_s {                                                                                  \
        DECLARE_MEMBER(a, a_type)                                                                      \
        DECLARE_MEMBER(b, b_type)                                                                      \
        DECLARE_MEMBER(c, c_type)                                                                      \
        DECLARE_MEMBER(d, d_type)                                                                      \
        DECLARE_MEMBER(e, e_type)                                                                      \
        func##_s(typename add_const_auto<a_type>::type& _a, typename add_const_auto<b_type>::type& _b, \
                 typename add_const_auto<c_type>::type& _c, typename add_const_auto<d_type>::type& _d, \
                 typename add_const_auto<e_type>::type& _e) {                                          \
            a = _a;                                                                                    \
            b = _b;                                                                                    \
            c = _c;                                                                                    \
            d = _d;                                                                                    \
            e = _e;                                                                                    \
        }                                                                                              \
    };                                                                                                 \
    template <>                                                                                        \
    Json::Value toJson<func##_s>(const func##_s& obj);                                               \
    }
#define STRUCT_WITH_4MEMBERS(func, a_type, a, b_type, b, c_type, c, d_type, d)                           \
    namespace params2json {                                                                                  \
    struct func##_s {                                                                                    \
        DECLARE_MEMBER(a, a_type)                                                                        \
        DECLARE_MEMBER(b, b_type)                                                                        \
        DECLARE_MEMBER(c, c_type)                                                                        \
        DECLARE_MEMBER(d, d_type)                                                                        \
        func##_s(typename add_const_auto<a_type>::type& _a, typename add_const_auto<b_type>::type& _b,   \
                 typename add_const_auto<c_type>::type& _c, typename add_const_auto<d_type>::type& _d) { \
            a = _a;                                                                                      \
            b = _b;                                                                                      \
            c = _c;                                                                                      \
            d = _d;                                                                                      \
        }                                                                                                \
    };                                                                                                   \
    template <>                                                                                          \
    Json::Value toJson<func##_s>(const func##_s& obj);                                                 \
    }
#define STRUCT_WITH_3MEMBERS(func, a_type, a, b_type, b, c_type, c)                                    \
    namespace params2json {                                                                                \
    struct func##_s {                                                                                  \
        DECLARE_MEMBER(a, a_type)                                                                      \
        DECLARE_MEMBER(b, b_type)                                                                      \
        DECLARE_MEMBER(c, c_type)                                                                      \
        func##_s(typename add_const_auto<a_type>::type& _a, typename add_const_auto<b_type>::type& _b, \
                 typename add_const_auto<c_type>::type& _c) {                                          \
            a = _a;                                                                                    \
            b = _b;                                                                                    \
            c = _c;                                                                                    \
        }                                                                                              \
    };                                                                                                 \
    template <>                                                                                        \
    Json::Value toJson<func##_s>(const func##_s& obj);                                               \
    }
#define STRUCT_WITH_2MEMBERS(func, a_type, a, b_type, b)                                                 \
    namespace params2json {                                                                                  \
    struct func##_s {                                                                                    \
        DECLARE_MEMBER(a, a_type)                                                                        \
        DECLARE_MEMBER(b, b_type)                                                                        \
        func##_s(typename add_const_auto<a_type>::type& _a, typename add_const_auto<b_type>::type& _b) { \
            a = _a;                                                                                      \
            b = _b;                                                                                      \
        }                                                                                                \
    };                                                                                                   \
    template <>                                                                                          \
    Json::Value toJson<func##_s>(const func##_s& obj);                                                 \
    }
#define STRUCT_WITH_1MEMBERS(func, a_type, a)                 \
    namespace params2json {                                       \
    struct func##_s {                                         \
        DECLARE_MEMBER(a, a_type)                             \
        func##_s(typename add_const_auto<a_type>::type& _a) { \
            a = _a;                                           \
        }                                                     \
    };                                                        \
    template <>                                               \
    Json::Value toJson<func##_s>(const func##_s& obj);      \
    }
#define STRUCT_WITH_0MEMBERS(func)                       \
    namespace params2json {                                  \
    struct func##_s {};                                  \
    template <>                                          \
    Json::Value toJson<func##_s>(const func##_s& obj); \
    }

#define IMPL_STRUCT_WITH_5MEMBERS(func, a_type, a, b_type, b, c_type, c, d_type, d, e_type, e) \
    namespace params2json {                                                                        \
    template <>                                                                                \
    Json::Value toJson<func##_s>(const func##_s& obj) {                                      \
        Json::Value value;                                                                   \
        value[obj.a##_name] = toJson(obj.a);                                                   \
        value[obj.b##_name] = toJson(obj.b);                                                   \
        value[obj.c##_name] = toJson(obj.c);                                                   \
        value[obj.d##_name] = toJson(obj.d);                                                   \
        value[obj.e##_name] = toJson(obj.e);                                                   \
        return value;                                                                          \
    }                                                                                          \
    }
#define IMPL_STRUCT_WITH_4MEMBERS(func, a_type, a, b_type, b, c_type, c, d_type, d) \
    namespace params2json {                                                             \
    template <>                                                                     \
    Json::Value toJson<func##_s>(const func##_s& obj) {                           \
        Json::Value value;                                                        \
        value[obj.a##_name] = toJson(obj.a);                                        \
        value[obj.b##_name] = toJson(obj.b);                                        \
        value[obj.c##_name] = toJson(obj.c);                                        \
        value[obj.d##_name] = toJson(obj.d);                                        \
        return value;                                                               \
    }                                                                               \
    }
#define IMPL_STRUCT_WITH_3MEMBERS(func, a_type, a, b_type, b, c_type, c) \
    namespace params2json {                                                  \
    template <>                                                          \
    Json::Value toJson<func##_s>(const func##_s& obj) {                \
        Json::Value value;                                             \
        value[obj.a##_name] = toJson(obj.a);                             \
        value[obj.b##_name] = toJson(obj.b);                             \
        value[obj.c##_name] = toJson(obj.c);                             \
        return value;                                                    \
    }                                                                    \
    }
#define IMPL_STRUCT_WITH_2MEMBERS(func, a_type, a, b_type, b) \
    namespace params2json {                                       \
    template <>                                               \
    Json::Value toJson<func##_s>(const func##_s& obj) {     \
        Json::Value value;                                  \
        value[obj.a##_name] = toJson(obj.a);                  \
        value[obj.b##_name] = toJson(obj.b);                  \
        return value;                                         \
    }                                                         \
    }
#define IMPL_STRUCT_WITH_1MEMBERS(func, a_type, a)        \
    namespace params2json {                                   \
    template <>                                           \
    Json::Value toJson<func##_s>(const func##_s& obj) { \
        Json::Value value;                              \
        value[obj.a##_name] = toJson(obj.a);              \
        return value;                                     \
    }                                                     \
    }
#define IMPL_STRUCT_WITH_0MEMBERS(func)                   \
    namespace params2json {                                   \
    template <>                                           \
    Json::Value toJson<func##_s>(const func##_s& obj) { \
        Json::Value value;                              \
        return value;                                     \
    }                                                     \
    }

namespace params2json {
template <typename T, typename std::enable_if<!std::is_enum<T>::value>::type* = nullptr>
Json::Value toJson(const T& value) {
    return Json::Value(value);
}

template <typename T, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr>
Json::Value toJson(const T& value) {
    return Json::Value(int(value));
}

template <>
Json::Value toJson<long unsigned int>(const long unsigned int& value);

template <>
Json::Value toJson<long int>(const long int& value);

template <>
Json::Value toJson<const char*>(const char* const& value);

template<>
Json::Value toJson<bool>(const bool& value);

template <typename T>
Json::Value toJson(const std::vector<T>& obj) {
    Json::Value value;
    for(int i=0;i<obj.size();i++) {
        value.append(toJson(obj[i]));
    }
    return value; 
}

template <typename T>
std::string make_message(const T& t) {
    std::string str = Json::FastWriter().write(toJson(t));
    // std::string str = toJson(t).toStyledString();
    if (str == "null\n") {
        return "";
    }
    return str;
}
}

#endif