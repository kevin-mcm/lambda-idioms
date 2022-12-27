#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>
#include <variant>

using namespace std;

/*
IIFE (Immediately Invoked Functions Expressions)
*/
class Person {
    public:
        Person(string name, int age) :
        name(name), age(age) {};
        void print() const {
            cout << "name: " << name << ", age: " << age << endl;
        }
    private:
        string name;
        int age;
};
void iife() {
    bool build = true;
    const Person person = [&] {
        if (build) return Person("pepe", 20);
        return Person("Lucia", 18);
    }();
    person.print();
}
/*
Call-once
*/
struct X {
    X() {
        static auto _ = [] {
            cout << "called once" << endl;
            return 0;
        }();
    }
};
void call_once() {
    X x1;
    X x2;
    X x3;
}
/*
Generic lambdas
*/
map<int, string> httpErrors = {
    {400, "Bad Request"},
    {401, "Unauthorised"},
    {403, "Forbidden"},
    {404, "Not Found"}
};

void generics_lambdas() {
    for_each(httpErrors.begin(), httpErrors.end(), [] (const auto& item) {
        cout << item.first << " - " << item.second << endl;
    });

    vector<string> v;
    auto f = [&v] (auto && item) {
        v.push_back(forward<decltype(item)>(item));
    };
    f("hello");
    for_each(v.begin(), v.end(), [](const auto& item) {
        cout << item << endl;
    });

    auto twice = [] (auto&&fp) {
        return [=] {
            fp();
            fp();
        };
    };
    auto print_fp = twice([] {
        cout << "hi" << endl;
    });
    print_fp();
}
/*
Variable template lambda
*/
using ms = std::chrono::milliseconds;
using us = std::chrono::microseconds;
using ns = std::chrono::nanoseconds;

struct Time {
    variant<ms, ns> time;
    Time(variant<ms,ns> time) : 
    time(time) {};
    auto convert(const auto& converter) {
        return visit(converter, time);
    }
};
template<typename T>
constexpr auto duration_cast = [] (auto d) {
    return std::chrono::duration_cast<T>(d);
};

void variable_template() {
    Time t(ns(3000));
    cout << t.convert(duration_cast<us>).count() << endl;
}
/*
Init capture optimisation
*/
const vector<string> vs = {"apple", "orange", "foobar", "lemon"};
static const string prefix = "foo";

void capture_optimisation() {
    auto result = find_if(vs.begin(), vs.end(), [str = prefix + "bar"] (const string& s) {
        return s == str;
    });
    if (result != vs.end())
        cout << prefix << "-something found" << endl;
}
/* C++23
Overload set
template<typename... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};

void overload_set() {
    overload ov = {
        [] (int i) {
            cout << "int thingy" << endl;
        },
        [] (float f) {
            cout << "float thingy" << endl;
        }
    };
    variant<int, float> v = 42;
    visit(ov, v);
}
*/
/*
Recursive lambda
*/
void recursive_lambda() {
    function<int(int)> fac1 = [&] (int n) {
        if (n == 0) return 1;
        return n * fac1(n-1);
    };
    cout << fac1(5) << endl;
    auto fac2 = [] (auto&& self, int n) {
        if (n == 0) return 1;
        return n * self(self, n - 1);
    };
    cout << fac2(fac2, 5) << endl;
    /* C++23
    auto fac3 = [] (this auto&& self, int n) {
        if (n == 0) return 1;
        return n * self(n - 1);
    };
    cout << fac3(5) << endl;
    */
}
/* C++23
Tree Traversal

struct Leaf {};
struct Node;
using Tree = variant<Leaf, Node*>;
struct Node {
    Tree left, right;
};
template<typename... Ts>
struct overload1 : Ts... {
    using Ts::operator()...;
};
int countLeaves(const Tree& tree) {
    return visit(overload1 {
        [] (const Leaf&) -> int {
            return 1;
        },
        [] (this const auto& self, const Node* node) -> int {
            return visit(self, node->left) + visit(self, node->right);
        }
    }, tree);
}
void tree_traversal() {
    Node* node = new Node();
    node->left = Leaf();
    node->right = Leaf();
    int res = countLeaves(node);
    cout << res << endl;
}
*/
/*
Main
*/
int main(int, char**) {
    iife();
    call_once();
    generics_lambdas();
    variable_template();
    capture_optimisation();
    recursive_lambda();
    return 0;
}
