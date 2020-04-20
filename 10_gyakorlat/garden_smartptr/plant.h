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
    static std::shared_ptr<Potato> instance();

private:
    Potato() : IndustrialCrop(4) {}
    static std::shared_ptr<Potato> inst;
};

class Pea : public IndustrialCrop {
public:
    static std::shared_ptr<Pea> instance();

private:
    Pea() : IndustrialCrop(3) {}
    static std::shared_ptr<Pea> inst;
};

class Paprika : public IndustrialCrop {
public:
    static std::shared_ptr<Paprika> instance();

private:
    Paprika() : IndustrialCrop(2) {}
    static std::shared_ptr<Paprika> inst;
};

///Flowers
class Rose : public Flower {
public:
    static std::shared_ptr<Rose> instance();

private:
    Rose() : Flower(2) {}
    static std::shared_ptr<Rose> inst;
};

class Carnation : public Flower {
public:
    static std::shared_ptr<Carnation> instance();

private:
    Carnation() : Flower(2) {}
    static std::shared_ptr<Carnation> inst;
};

class Tulip : public Flower {
public:
    static std::shared_ptr<Tulip> instance();

private:
    Tulip() : Flower(2) {}
    static std::shared_ptr<Tulip> inst;
};
#endif
