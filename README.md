# Params2json
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
- #### 添加函数宏

  ```c++
  
  ```

  

- #### 添加自定义序列化函数toJson()

  ```
  
  ```

  

- #### 添加自定义make_message()

  ```
  
  ```

  
