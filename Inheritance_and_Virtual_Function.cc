#include <iostream>
#include <vector>

using namespace std;

class Shape {
public:
Shape () {}
virtual ~Shape () {}
virtual double area() = 0;
};

class Circle : public Shape {
private:
double r;

public:
Circle (const double in): r( in ) {}
~Circle () {}

double area() override {
  return 3.14 * r * r;
}
};

int main() {
  vector<Shape*> shapes;
  shapes.push_back(new Circle(10.0));
  shapes.push_back(new Circle(20.0));

  double total = 0.0;
  for (const auto e : shapes) {
    total += e->area();
    }
  
  cout << total << endl;

  for (auto e : shapes) {
    delete e;
    }

return 0;
}
