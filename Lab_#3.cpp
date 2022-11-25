#include <iostream>
// Base
class Product
{
protected:
    int price;
    std::string name;

public:
    Product(std::string name = "", int price = 0)
    {
        this->name = name;
        this->price = price;
    }
    ~Product()
    {
        std::cout << "Base destructed" << std::endl;
    }
    void display()
    {
        std::cout << "Name: " << name << std::endl
            << "Price: " << price << std::endl;
    }
};
// P1->B
class Mechanical : virtual protected Product
{
protected:
    int wearproof;

public:
    Mechanical(std::string name = "", int price = 0, int wearproof = 0) : Product(name, price)
    {
        this->wearproof = wearproof;
    }
    ~Mechanical()
    {
        std::cout << "Destructed mechanical part" << std::endl;
    }
    void display()
    {
        Product::display();
        std::cout << "Wearproof: " << wearproof << std::endl;
    }
};
// P11->P1->B
class Drive : protected Mechanical
{
protected:
    int max_rpm;

public:
    Drive(std::string name = "", int price = 0, int wearproof = 0, int max_rpm = 0) : Product(name, price), Mechanical(name, price, wearproof)
    {
        this->max_rpm = max_rpm;
    }
    ~Drive()
    {
        std::cout << "Destructed drive" << std::endl;
    }
    void display()
    {
        Mechanical::display();
        std::cout << "Max rpm: " << max_rpm << std::endl;
    }
};
//P2->B
class Electric : virtual protected Product
{
protected:
    int life_span;

public:
    Electric(std::string name = "", int price = 0, int life_span = 0) : Product(name, price)
    {
        this->life_span = life_span;
    }
    ~Electric()
    {
        std::cout << "Destructed Electronics" << std::endl;
    }
    void display()
    {
        Product::display();
        std::cout << "Life span: " << life_span << std::endl;
    }
};
//P21->P2->B
class Papers : protected Electric
{
protected:
    int warranty;

public:
    Papers(std::string name = "", int price = 0, int life_span = 0, int warranty = 0) : Product(name, price), Electric(name, price, life_span)
    {
        this->warranty = warranty;
    }
    ~Papers()
    {
        std::cout << "Destructed papers" << std::endl;
    }
    void display()
    {
        Electric::display();
        std::cout << "Months of warranty: " << warranty << std::endl;
    }
};
//P21<-P3->P11
class Laptop : protected Drive, protected Papers
{
private:
    int capacity;

public:
    Laptop(std::string name = "", int price = 0, int wearproof = 0, int max_rpm = 0, int life_span = 0, int warranty = 0, int capacity = 0) : Product(name, price), Drive(name, price, wearproof, max_rpm), Papers(name, price, life_span, warranty)
    {
        this->capacity = capacity;
    }
    void display()
    {
        std::cout << "Name: " << name << std::endl
            << "Price: " << price << std::endl
            << "Wearproof: " << wearproof << std::endl
            << "Max rpm: " << max_rpm << std::endl
            << "Years of lifespan: " << life_span << std::endl
            << "Months of warranty: " << warranty << std::endl
            << "Capacity: " << capacity << std::endl;
    }
};

int main()
{
     //Drive drive("Drive ID", 1, 2, 3);
     //drive.display();
     //std::cout << std::endl;
     //Papers board("warranty ID", 2, 5, 7);
     //board.display();
     //std::cout << std::endl;


     Laptop Laptop("TUF Gamimg F15 FX506", 2799, 10, 4, 8, 24, 512);
     Laptop.display();
}
