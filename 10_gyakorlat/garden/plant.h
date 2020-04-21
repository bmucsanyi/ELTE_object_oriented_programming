#ifndef PLANT_H
#define PLANT_H

#include <iostream>
#include <memory>

class Plant {
public:
    virtual ~Plant() {};
    unsigned int getRipeningTime() const { return ripeningTime; }
    bool isIndustrialCrop;

protected:
    Plant(unsigned int rt, bool l) : isIndustrialCrop(l), ripeningTime(rt) {}
    unsigned int ripeningTime;
};

class IndustrialCrop : public Plant {
public:
    virtual ~IndustrialCrop() {};

protected:
    IndustrialCrop(unsigned int rt) : Plant(rt, true) {}
};

class Flower : public Plant {
public:
    virtual ~Flower() {};

protected:
    Flower(unsigned int rt) : Plant(rt, false) {}
};

///Industrial crops
class Potato : public IndustrialCrop {
public:
    static Potato* instance();
    static void destroy();

private:
    Potato() : IndustrialCrop(4) {}
    static Potato* inst;
};

class Pea : public IndustrialCrop {
public:
    static Pea* instance();
    static void destroy();

private:
    Pea() : IndustrialCrop(3) {}
    static Pea* inst;
};

class Paprika : public IndustrialCrop {
public:
    static Paprika* instance();
    static void destroy();

private:
    Paprika() : IndustrialCrop(2) {}
    static Paprika* inst;
};

///Flowers
class Rose : public Flower {
public:
    static Rose* instance();
    static void destroy();

private:
    Rose() : Flower(2) {}
    static Rose* inst;
};

class Carnation : public Flower {
public:
    static Carnation* instance();
    static void destroy();

private:
    Carnation() : Flower(2) {}
    static Carnation* inst;
};

class Tulip : public Flower {
public:
    static Tulip* instance();
    static void destroy();

private:
    Tulip() : Flower(2) {}
    static Tulip* inst;
};
#endif

/** Example program
  * #include <iostream>
  * #include <string>
  * 
  * class Dummy
  * {
  * public:
  *     static void foo() { std::cout << "foo" << std::endl; }   
  * };
  * 
  * int main()
  * {
  * Dummy dumDum = Dummy();
  * dumDum.foo();
  * Dummy::foo();
  * }
  */ 