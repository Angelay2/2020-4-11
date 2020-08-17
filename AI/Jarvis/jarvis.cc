#include "jarvis.hpp"

// ./jarvis
int main(){
    Jarvis js;

    js.Init();
    js.Run();// 直接让Jarvis跑起来

    return 0;
    //TuLing* tl = new TuLing();
    //string message;
    //while(1){
    //    cout << "我说的# ";
    //    cin >> message;
    //    string result = tl->Chat(message);
    //    cout << "Jarvis# " << result << endl;
    //}
    //return 0;
}
