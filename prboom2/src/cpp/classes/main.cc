#include <iostream>
#include <stdio.h>
#include <string>
#include <fmt/core.h>

class Base
{
  private:
    int data2;

  protected:
    int data;

  public:
    Base() = default;
};

class Derived : Base
{
  public:
    Derived() = default;
    void doThings()
    {
        std::cout << data << "\n";
    }
};

class SmartString final : public std::string
{
  public:
    SmartString() = default;
    SmartString(const char* c) : std::string(c) {}

    void print()
    {
        fmt::print("Hello! I am a string and my value is '{:.04}'...\n", 3.14);
    }
};

int main()
{
    SmartString string = "test string";
    string.print();
}
