# Params2json
[![badge](https://img.shields.io/badge/license-MIT-blue)](https://github.com/DavidZhang0710/Params2json/blob/main/LICENSE)

一个基于jsoncpp开发的函数入参转json模块，方便进行函数埋点的上报，或者将入参作为二进制数据传递，支持多平台。

## 项目介绍
基于jsoncpp构建，用于函数入参转json格式，方便进行函数埋点的上报或作为二进制数据传递，例如protobuf，并且支持多平台。

由于C++本身的语言特性，没有完整的反射机制，导致其运行时信息有大量遗失，在C++17标准中才开始支持结构体的序列化，并且结构体的诸如成员名的诸多信息在编译时已经被优化而无法访问。

而如果希望在C++项目中引入反射机制实现这些信息的还原，往往需要引入boost等体量较大的第三方库，最终带来过多的包大小增量，本项目提供一种更为简单的静态非侵入时序列化方案，可以在不过多改动项目源代码的基础上实现结构体等众多复杂入参的自定义序列化。

本项目基于较为通用的[open-source-parsers/jsoncpp](https://github.com/open-source-parsers/jsoncpp)，如果需要更换为其他的json库，例如更轻量化、效率更高的[nlohmann/json](https://github.com/nlohmann/json)，也只需要简单的代码重构即可实现。

## 项目需求
c++>=11

jsoncpp>=1.9.4

cmake>=3.12

## 快速开始

1. 下载本仓库

   ```bash
   git clone https://github.com/DavidZhang0710/Params2json.git
   ```

2. 使用指令编译

   ```bash
   cd ./Params2json
   mkdir build
   cd ./build
   cmake ..
   cmake --build .
   ```

   在cmake执行过程中会自动下载编译并链接jsoncpp静态库

3. 
   运行可执行文件

   执行上述指令后会生成Params2json可执行文件，运行即可看到`src\example.cpp`的执行结果

## 使用方法

#### 模块定义方法

```c++
namespace params2json {
    //T类型转json
    template <typename T>
		Json::Value toJson(const T& value);
    //定义与函数相对应的结构体funcname_s，放在头文件（.h）中
    STRUCT_WITH_XMEMBER(funcname, typename_0, paramname_0,...)
    //对于上述结构体toJson的实现，放在实现（.cc）中
    IMPL_STRUCT_WITH_XMEMBER(funcname, typename_0, paramname_0,...)
    //和上述结构体配合，生成入参的json字符串
    template <typename T>
    std::string make_message(const T& t);
}
```



- #### 添加函数宏

  对于函数`void func (typename_0, param_0, typename_1, param_1)`，只需要进行如下的宏定义

  ```c++
  STRUCT_WITH_XMEMBER(func, typename_0, param_0, typename_1, param_1)
  IMPL_STRUCT_WITH_XMEMBER(func, typename_0, param_0, typename_1, param_1)
  ```

  然后就可以使用宏定义所定义的结构体func_s和make_message生成需要的json字符串

  ```c++
  std::string json_str = params2json::make_message(params2json::func_s(param_0, param_1));
  ```

  

- #### 添加自定义序列化函数toJson()

  对于简单类型，已经存在toJson()的定义，也可以通过如下方式进行特化，以输出想要的json格式：

  ```c++
  template <>
  Json::Value toJson<bool>(const bool& value) {
      if (value)  return Json::Value("True");
      return Json::Value("False");
  }
  ```

  对于复杂类型，例如结构体或类，需要手动定义toJson（因为成员名信息在编译时已丢失，非侵入式不得不手动编写）具体如下：

  ```c++
  struct simple {
      int num;
      bool flag;
  };
  
  struct complex {
      int num;
      simple struct_member;
  };
  
  template<>
  Json::Value toJson<simple>(const simple& obj) {
      Json::Value value;
      value["num"] = toJson(obj.num);
      value["flag"] = toJson(obj.flag);
      return value;
  }
  
  template<>
  Json::Value toJson<complex>(const complex& obj) {
      Json::Value value;
      value["num"] = toJson(obj.num);
      value["struct_member"] = toJson(obj.struct_member);
      return value;
  }
  ```

  更多细节可以查看`src\example.cpp`

- #### 添加自定义make_message()

  `make_message()`是基于`Json::StreamWriter`编写的将`Json::Value`对象转换为字符串输出的方法，如果需要更加自定义的方式，可以重载`make_message()`。
  
  也可以通过`toJson(func_s())`的方式直接获取由入参的 `Json::Value`对象，并通过自定义的方式进行处理。

  
