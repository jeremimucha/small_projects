#include <iostream>
#include <string>
#include <vector>
#include <memory>


class Animal
{
public:
    virtual void vocalize() = 0;
};

class NegativeVibe
{
public:
    std::string intelligentComment()
    {
        return "Am I glad I don't live in the Arctic! ";
    }
};

class PositiveVibe
{
public:
    std::string intelligentComment()
    {
        return "I definitely wouldn't mind catching the Aurora Borealis one day! ";
    }
};

template<typename T>
class Compliment : public T
{
public:
    std::string intelligentComment()
    {
        return "That David sure is smart. " + T::intelligentComment();
    }
};

template<typename T>
class Cutoff : public T
{
public:
    std::string intelligentComment()
    {
        return "...";
    }
};

template<typename T>
class Dog : public T, public Animal
{
public:
    void vocalize() { std::cout << "Woof. " + T::intelligentComment(); }
};

template<typename T>
class Cat : public T, public Animal
{
public:
    void vocalize() { std::cout << "Meow. " + T::intelligentComment(); }
};

int main()
{
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back( std::make_unique<Dog<Compliment<PositiveVibe>>>() );
    animals.push_back( std::make_unique< Cat<Cutoff<NegativeVibe>> >() );
    
    for( auto& animal : animals ){
        animal->vocalize(); std::cout << std::endl;
    }

    return 0;
}
