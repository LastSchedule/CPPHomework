//#include <iostream>
//#include <sstream>
//using namespace std;
//
//class T
//{
//public:
//    explicit T(int n = 10) : _n(n) {
//        cout << "Constructor" << endl;
//    }
//    operator string() {
//        cout << "type convert" << endl;
//        stringstream sstr;
//        sstr << _n;
//        return sstr.str();
//    }
//
//    int _n;
//};
//
//void doSomething(T t)
//{
//    cout << "Default value is " << t._n << endl;
//}
//
//int main()
//{
//    T t;
//    string str(t);// 将 T 类型隐式转换为 string
//    cout << str << endl;
//    return 0;
//}
