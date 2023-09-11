#include "params2json.h"

namespace params2json {
template <>
Json::Value toJson<bool>(const bool& value) {
    if (value)  return Json::Value("True");
    return Json::Value("False");
}

template <>
Json::Value toJson<long unsigned int>(const long unsigned int& value) {
    return Json::Value(Json::UInt64(value));
}

template <>
Json::Value toJson<long int>(const long int& value) {
    return Json::Value(Json::Int64(value));
}

template <>
Json::Value toJson<const char*>(const char* const& value) {
    std::string value_ensured = value ? value : "";
    return Json::Value(value_ensured);
}
}