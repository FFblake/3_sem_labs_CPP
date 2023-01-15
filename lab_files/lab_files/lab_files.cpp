#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Organization
{    
public:
    Organization() {
        _org_name = " ";
        _members = 0;
        _owner_name = " ";
    }
    Organization(std::string name, int members, std::string owner) :_org_name(name), _members(members), _owner_name(owner) {};
    ~Organization() {};

    std::string get_name() { return _org_name; }
    void set_name(std::string name) { this->_org_name = name; }

    int get_members() { return _members; }
    void set_members(int count) { this->_members = count; }

    std::string get_owner() { return _owner_name; }
    void set_owner(std::string owner) { this->_owner_name = owner; }

    friend std::ostream& operator<<(std::ostream& os, Organization& Org)
    {
        os << Org._org_name << " " << Org._members << " " << Org._owner_name << std::endl;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Organization& Org)
    {
        is >> Org._org_name >> Org._members >> Org._owner_name;
        return is;
    }

    void see_org();

private:
    std::string _org_name;
    int _members;
    std::string _owner_name;
};

void write_into_txt_file()
{
    std::string name, owner;
    int amount;
    std::ofstream file("Text_File.txt", std::ios::app);
    if (file.is_open())
    {
        std::cout << "Enter name of organization: ";
        std::getline(std::cin, name);
        std::cout << "Enter amount of members: ";
        std::cin >> amount;
        rewind(stdin);
        std::cout << "Enter owner name: ";
        std::getline(std::cin, owner);
        Organization org(name, amount, owner);
        file << org;
        file.close();
    }
}

void delete_from_txt()
{
    std::ifstream file("Text_File.txt");
    std::vector<Organization> new_file;
    Organization org;
    std::string tmp_name;
    std::cout << "Enter name of organization u want to delete: ";
    std::getline(std::cin, tmp_name);

    if (file.is_open())
    {
        while (file >> org)
        {
            if (tmp_name == org.get_name())
                continue;
            else
            {
                new_file.push_back(org);
            }
        }
        file.close();
    }


    std::ofstream file1("Text_File.txt");
    if (file1.is_open())
    {
        for (int j = 0; j < new_file.size(); j++)
        {
            file1 << new_file[j];
        }
    }
}

void Organization::see_org()
{
    std::cout << "The name of org: " << _org_name << std::endl
        << "The amount of members: " << _members << std::endl
        << "The name of owner: " << _owner_name << std::endl;
}

void see_txt_file()
{
    std::ifstream file("Text_File.txt");
    Organization org;
    int num = 0;
    if (file.is_open())
    {
        while (file >> org)
        {
            std::cout << num << " str" << std::endl;
            org.see_org();
            num++;
        }
    }
}

void from_file()
{
    std::ifstream file("Text_File.txt");
    if (file.is_open())
    {
        std::cout << file.rdbuf();
    }
}
void write_into_bin_file()
{
    std::string name, owner;
    size_t size_name, size_owner;
    int amount;
    std::ofstream file("Binary_File.bin", std::ios::binary | std::ios::app);
    if (file.is_open())
    {
        std::cout << "Enter name of organization: ";
        std::getline(std::cin, name);
        std::cout << "Enter amount of members: ";
        std::cin >> amount;
        rewind(stdin);
        std::cout << "Enter owner name: ";
        std::getline(std::cin, owner);
        size_name = name.size();
        size_owner = owner.size();
        file.write((char*)&size_name, sizeof(size_name));
        file.write(name.c_str(), size_name);
        file.write((char*)&amount, sizeof(amount));
        file.write((char*)&size_owner, sizeof(size_owner));
        file.write(owner.c_str(), size_owner);
        file.close();
    }
}

void read_from_bin()
{

    std::string name, owner;
    size_t size_name, size_owner;
    int amount;
    int check = 0;
    std::ifstream file("Binary_File.bin", std::ios::binary | std::ios::in);
    if (file.is_open())
    {
        Organization org;
        while (!file.eof())
        {
            if (file.eof())
                break;
            try
            {
                file.read((char*)&size_name, sizeof(size_name));
                char* buf = new char[size_name + 1];

                buf[size_name] = 0;

                file.read(buf, size_name);
                std::cout << buf;
                system("pause");
                name = buf;

                org.set_name(name);

                delete[] buf;


                file.read((char*)&amount, sizeof(amount));
                org.set_members(amount);

                file.read((char*)&size_owner, sizeof(size_owner));
                char* buf_1 = new char[size_owner + 1];
                buf_1[size_owner] = 0;
                file.read(buf_1, size_owner);
                owner = buf_1;

                org.set_owner(owner);

                delete[] buf_1;
            }
            catch (const std::exception& ex)
            {
                std::cout << ex.what();
            }
            org.see_org();
        }
        file.close();
    }
}

void search_by_name()
{
    std::ifstream file("Text_File.txt");
    std::vector<Organization> search_vect;
    Organization org;
    std::string tmp_name;
    std::cout << "Enter name of organization u want to delete: ";
    std::getline(std::cin, tmp_name);

    if (file.is_open())
    {
        while (file >> org)
        {
            if (tmp_name == org.get_name())

                search_vect.push_back(org);
            else
            {
                continue;
            }
        }
        file.close();
    }

    std::cout << "We find next organizations" << std::endl;
    for (int j = 0; j < search_vect.size(); j++)
        search_vect[j].see_org();
}

int Menu()
{
    int choice;
    system("Cls");
    std::cout << "Choose what you wnat:" << std::endl
        << "1. Write into txt file" << std::endl
        << "2. Delete from txt file" << std::endl
        << "3. Show txt file " << std::endl
        << "4. Search by name" << std::endl
        << "5. Write into bin file" << std::endl
        << "6. Show bin file" << std::endl
        << "7. Exit" << std::endl
        << "Enter: ";
    std::cin >> choice;
    rewind(stdin);
    return choice;
}
int main()
{


    while (1)
    {
        system("pause");
        switch (Menu())
        {
        case 1:
        {
            write_into_txt_file();
            break;
        }
        case 2:
        {
            delete_from_txt();
            break;
        }
        case 3:
        {
            see_txt_file();
            system("pause");
            break;
        }
        case 4:
        {
            search_by_name();
            system("pause");
            break;
        }
        case 5:
        {
            write_into_bin_file();
            break;
        }
        case 6:
        {
            read_from_bin();
            system("pause");
            break;
        }
        case 7:
        {
            return 0;
            break;
        }
        }
    }
    return 0;
}