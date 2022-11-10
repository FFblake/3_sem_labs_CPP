#include <iostream>
#include <time.h>
class Tasks
{
private:
    int id;
    std::string name;
    int result;

public:
    
    static int count;
    Tasks(std::string name = "", int result = 0)
    {
        this->id = count;
        this->name = name;
        this->result = result;
        count++;
    }
   
    ~Tasks()
    {
        std::cout << "Destructor call" << std::endl;
    }
   
    void display()
    {
        std::cout << "Id: " << id << std::endl
            << "Name: " << name << std::endl
            << "Result: " << result << std::endl
            << std::endl;
    }

    friend class Controller;
};

class Controller
{
public:
    void setResultprc(Tasks& task, int prc)
    {
        task.result = prc;
    }
};

int Tasks::count = 1;

int main()
{   
    std::string arr[] = {"Slava", "Gleb", "Danik", "Vlad", "Nina"};
    Controller controller;
    srand(time(NULL));

    Tasks task1;
    Tasks task2("Ivan", 39);
    std::cout << "Original percentage" << std::endl;
    task1.display();
    task2.display();

    controller.setResultprc(task1, 80);
    controller.setResultprc(task2, 69);
    std::cout << "Updated percentage" << std::endl;
    task1.display();
    task2.display();

    Tasks* tasklist = new Tasks[5];
    std::cout << "Original percentage" << std::endl;
    for (int i = 0; i < 5; i++)
    {
        tasklist[i] = Tasks(arr[i], 0);
        tasklist[i].display();
    }
    std::cout << "Updated percentage" << std::endl;
    for (int i = 0; i < 5; i++)
    {
        controller.setResultprc(tasklist[i], rand() % 100);
        tasklist[i].display();
    }

    delete[] tasklist;
}
