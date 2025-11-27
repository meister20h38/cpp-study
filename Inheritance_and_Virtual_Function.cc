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
