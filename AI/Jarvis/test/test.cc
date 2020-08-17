#include <iostream> 
#include <sstream> 
#include <memory> 
#include <string> 
#include <json/json.h> 
using namespace std;

// 序列化的过程就是将我们的json:Value转化为字符串
int main() { 
	Json::Value root; // 万能对象 填充最多的是key和value 
	Json::StreamWriterBuilder wb; // 构建streamwriter
	std::ostringstream os; // 从序列化之后的流中提取字符串 

	root["name"] = "张三"; 
	root["age"] = 19; 
	root["Lang"] = "c++"; 
	
    // 智能指针, 用wb生成构建streamwriter,指针名字为jw, 指向streamwriter对象
	std::unique_ptr<Json::StreamWriter> jw(wb.newStreamWriter()); 
	jw->write(root, &os); // 通过智能指针将对象序列化到os中
	std::string result = os.str(); // 保存序列化之后的结果
	
	std::cout << result << std::endl; 
	
	return 0; 
}

