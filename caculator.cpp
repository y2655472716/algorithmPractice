#include <iostream>
#include <random>

enum Caculate{
    ADD,
    MINUS,
    MUL,
    DIV
};

int add(int a, int b){
    int ans = a;
    while(b != 0){
        ans = a ^ b;
        b = (a & b) << 1;
        a = ans;
    }

    return ans;
}

int neg(int n){
    return add((~n), 1); 
}

int minus(int a, int b){
    return add(a, neg(b));
}

int mul(int a, int b){
    unsigned t = static_cast<unsigned>(b);
    int ans{};
    while(t != 0){
        if((t & 1) != 0){
            ans = add(ans, a);
        }
        a <<= 1;
        t >>= 1;
    }
    return ans;
}

int Div(int a, int b){
    int x = a < 0 ? neg(a) : a;
    int y = b < 0 ? neg(b) : b;
    int ans{};
    for(int i = 30;i >= 0;i = minus(i, 1)){
        if((x >> i) >= y){
            ans |= (1 << i);
            x = minus(x, y << i);
        }
    }

    return a < 0 ^ b < 0 ? neg(ans) : ans;
}

int divide(int a, int b){
    if(a == INT_MIN && b == INT_MIN)return 1;
    if(a != INT_MIN && b != INT_MIN)return Div(a, b);
    if(b == INT_MIN)return 0;
    if(b == neg(1))return INT_MAX;
    
    int t = b < 0 ? minus(a, b) : add(a, b);
    int ans = Div(t, b);
    return b < 0 ? add(ans, 1) : minus(ans, 1);
}

int caculate(int a, int b, int (*p)(int, int)){
    return p(a, b);
}

void check(int p(int, int), Caculate c){
    std::random_device rd;

    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> uidt(-20000, 20000);

    int time = 50000;
    while(time-- > 0){
        int a = uidt(mt);
        int b = uidt(mt);
        int res{};
        switch (c)
        {
        case ADD:
            res = a + b;
            break;
        case MINUS:
            res = a - b;
            break;
        case MUL:
            res = a * b;
            break;
        case DIV:
            if(b == 0)continue;
            res = a / b;
            break;
        }
        if(res != caculate(a, b, p)){
            std::cout << "错误" << std::endl;
            return;
        }
    }
    std::cout << "正确" << std::endl;
}

int main(){
    check(divide, DIV);
}