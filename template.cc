template <class T>
class Item {
private:
    T data;

public:
  Item () : data( T() ) { }
  Item (const T& t) : data(t) { }

  Item& operator =(const Item& i) {
    data = i.data;
    return *this;
  }

  friend Item operator +(const Item& i1, const Item& i2) {
    return Item(i1.data + i2.data);
  }
};
