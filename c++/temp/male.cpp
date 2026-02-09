#include <iostream>
using namespace std;
class Drink {
public:
    // 虚函数，用于制作饮品
    virtual void make()=0;
};

// 茶类，继承自饮品基类
class Tea : public Drink {
public:
    // 重写基类的make函数
    void make() override {
        cout << "制作茶饮品" << endl;
    }
};

// 咖啡类，继承自饮品基类
class Coffee : public Drink {
public:
    // 重写基类的make函数
    void make() override {
        cout << "制作咖啡饮品" << endl;
    }
};
void order(Drink* drink){
    drink.make();
}
int main() {
    Tea milktea;
    Coffee Latte;
    order(milktea);
    order(Latte);
    return 0;
}