#include <iostream> 
#include <sstream> 
#include <memory> 
#include <string> 
#include <json/json.h> 
using namespace std;

// 解析字符串 反序列化,
int main(){
    string str = "{\"Age\" : 26,\"Lang\" : \"c++\",\"Name\" : \"zhangsan\"}"; // 原始字符串
    cout << str << std::endl; 

    JSONCPP_STRING errs; // 如果出错了, 就填上对应的错误信息
    Json::Value root; 
    Json::CharReaderBuilder rb;
    std::unique_ptr<Json::CharReader> const jsonReader(rb.newCharReader());// 构建charReader对象
    bool res = jsonReader->parse(str.data(), str.data()+str.size(), &root, &errs);// 解析
    // 如果res返回值为false或者errs为不为空(则证明有错误原因),则证明解析是有问题的,
    if(!res || !errs.empty()){
        cout << "jsoncpp parse error" << endl;
        return 1;
    }
    // 提取内容
    cout << root["Age"].asInt() << endl; // 当成整形
    cout << root["Lang"].asString() << endl; // 当成字符串
    cout << root["Name"].asString() << endl;// 当字符串打印

}
