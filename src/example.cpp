# include "params2json.h"
# include "define.h"
# include <iostream>

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