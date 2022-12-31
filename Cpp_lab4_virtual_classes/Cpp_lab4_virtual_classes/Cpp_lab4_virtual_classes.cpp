#include <iostream>

//B
class Products
{
protected:
    std::string type;
    int price;

public:
    Products(std::string type = "", int price = 0)
    {
        this->type = type;
        this->price = price;
    }
    virtual ~Products()
    {
        std::cout << "Base destructor(B)" << std::endl;
    }
    virtual void print() = 0;

};
//P1->B
class supplements : public Products
{
protected:
    int Calories;

public:
    supplements(std::string type = "", int price = 0, int Calories = 0) : Products(type, price)
    {
        this->Calories= Calories;
    }
    virtual ~supplements()
    {
        std::cout << "supplement destructor called(P1)" << std::endl;
    }

    void print() override
    {
        std::cout << "Type: " << this->type << std::endl
            << "Price: " << this->price << std::endl
            << "Calorie: " << this->Calories << std::endl;
    }
};
//P11->P1->B
class Pre : public supplements
{
protected:
    int weight;

public:
    Pre(std::string type = "", int price = 0, int kilocalorie = 0, int weight = 0) : supplements(type, price, kilocalorie)
    {
        this->weight = weight;
    }
    virtual ~Pre()
    {
        std::cout << "PED destructor called(P11)" << std::endl;
    }

    void print() override 
    {
        std::cout << "Type: " << this->type << std::endl
            << "Price: " << this->price << std::endl
            << "Calorie: " << this->Calories << std::endl
            << "Weight: " << this->weight << std::endl;
    }
};
//P2->B
class Weights : public Products
{
protected:
    int mass;

public:
    Weights(std::string type = "", int price = 0, int volt = 0) : Products(type, price)
    {
        this->mass = volt;
    }
    virtual ~Weights()
    {
        std::cout << "Pumping iron destructor called(P2)" << std::endl;
    }

    void print() override
    {
        std::cout << "Type: " << this->type << std::endl
            << "Price: " << this->price << std::endl
            << "Mass: " << this->mass << std::endl;
    }
};

int main()
{
    Products** list = new Products * [3];
    std::string line = "";
    int first_param=0, second_param=0, third_param=0;
    std::cout << "Type the name of supplement, then its price and its calories: ";
    std::cin >> line >> first_param >> second_param;
    std::cout << "The supplement is " << line << " costs " << first_param << " and its energy value is " << second_param << "\n\n";
    list[0] = new supplements(line, first_param, second_param);

    std::cout << "Type the name of preworkout, then its price, calories and mass: ";
    std::cin >> line >> first_param >> second_param >> third_param;
    list[1] = new Pre(line, first_param, second_param, third_param);
    std::cout << "The preworkout is " << line << " costs " << first_param << " its energy value is " << second_param << " and its mass is "<< third_param << "\n\n";
	
    std::cout << "Type the type of the metal, then its price and its mass: ";
	std::cin >> line >> first_param >> second_param;
	std::cout << "The weight type is " << line << " costs " << first_param << " and its mass is " << second_param << "\n\n\n";
    list[2] = new Weights(line, first_param, second_param);

    list[0]->print();
    list[1]->print();
    list[2]->print();
 
    for (int i = 0; i < 3; i++)
    {
        delete list[i];
    }
    delete list;
}