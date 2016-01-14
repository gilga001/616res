#include <iostream>
#include <cstring>

class A {
public:
  A(int m, int n) : number1(m), number2(n) { }
  int getNumber1() const { return number1; }
private:
  int number1;
  int number2;
};

int main() {
  A a(7);
  std::cout << a.getNumber() << std::endl;
  return 0;
}
