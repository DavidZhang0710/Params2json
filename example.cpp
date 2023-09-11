# include "src/params2json.h"
# include <iostream>
struct simple {
    int num;
    bool flag;
};

struct complex {
    int num;
    simple struct_member;
};

Json::Value toJson(simple& obj) {
    Json::Value value;
    value["num"] = toJson(obj.num);
    value["flag"] = toJson(obj.flag);
    return value;
}

Json::Value toJson(complex& obj) {
    Json::Value value;
    value["num"] = toJson(obj.num);
    value["struct_member"] = toJson(obj.struct_member);
    return value;
}

STRUCT_WITH_2MEMBERS(func, int, num, complex, struct_param)
IMPL_STRUCT_WITH_2MEMBERS(func, int, num, complex, struct_param)

void func (int num, complex struct_param) {
    /*
        code
    */
   std::cout<<params2json::make_message(params2json::func_s(num, struct_param));
}

int main () {
    complex ins{1,{0,true}};
    func(2,ins);
}