#include <iostream>
#include <iomanip>
#include <type_traits>

using namespace std;

template <typename T>
class AddSpace {
private:
    const T& ref_;
public:
    AddSpace(const T& r): ref_(r) {}

    friend std::ostream& operator<< (std::ostream &os, AddSpace<T> s) {
        return os << s.ref_ << ' ';
    }
};

template <typename... Args>
void print(Args... args) {
    (std::cout << ... << AddSpace(args)) << '\n';
}

struct Int {
    int value_;
    explicit Int(int v = 0): value_(v) {}
    explicit operator int() const { return value_; }

    friend std::ostream& operator << (std::ostream& o, const Int& i) {
        o << i.value_;
        return o;
    }
};

Int operator +(const Int& i, const Int& j) {
    std::cout << "Adding " << i << " " << j << "\n";
    return Int(i.value_ + j.value_);
};


Int operator * (const Int& i, const Int& j) {
    std::cout << "Multiplying " << i << " " << j << "\n";
    return Int(i.value_ * j.value_);
};

template <typename... Args>
auto addInts(Args&&... args) {
    return (Int(0) + ... + args);
}

template <typename... Args>
auto mulInts(Args... args) {
    return (Int(1) * ... * args);
}

int main()
{
    std::cout << addInts(Int{3}, Int{5}, Int{6}) << std::endl;
    print(Int(9), "Minum");
    return 0;
}
