#ifndef __Enhance__H__
#define __Enhance__H__
#include <iostream>
#include <string>
#include <map>
using namespace std;

enum class ItemType{
    Equipment, Jewelry
};

const map<ItemType, string> typeName{
    { ItemType::Equipment, "Equipment" },
    { ItemType::Jewelry, "Jewelry"}
};

class Item{
protected:
    string name;
    ItemType myType;
    int level;
    int stack;
    double percent;
    double delta;
    virtual void Calculate() { }
public:
    Item(){
        cout << "New Item Created\n";
    }
    ~Item(){
        cout << "Item Deleted : " << name << "\n";
    }
    string GetName(){
        return name;
    }
    string GetType(){
        return typeName.at(myType);
    }
    int GetStack(){
        return stack;
    }
    virtual void LevelChanged(){
        level += 1;
        stack = 0;
    }
    virtual void LevelDown(){
        stack += 1;
    }
    int GetLevel(){
        return level;
    }
    string GetStringLevel(){
        if(level < 16){
            return to_string(level);
        }
        switch (level)
        {
        case 16:{
            return "I";
        }
        case 17:{
            return "II";
        }
        case 18:{
            return "III";
        }
        case 19:{
            return "IV";
        }
        case 20:{
            return "V";
        }
        default:
            return "NULL";
        }
    }
    double GetPercent(){
        return percent;
    }
    double GetDelta(){
        return delta;
    }
    virtual void Failed(){

    }
    void AddStack(int value){
        stack += value;
        percent += delta * value;
    }
};

class Equipment : public Item{
public:
    Equipment(){
        myType = ItemType::Equipment;
    }
    virtual void Calculate(){
        switch(level){
            case 14:{
                percent = 2.00;
                delta = 0.20;
                break;
            }
            case 15:{
                percent = 11.76;
                delta = 1.18;
                break;
            }
            case 16:{
                percent = 7.69;
                delta = 0.77;
                break;
            }
            case 17:{
                percent = 6.25;
                delta = 0.63;
                break;
            }
            case 18:{
                percent = 2.00;
                delta = 0.20;
                break;
            }
            case 19:{
                percent = 0.30;
                delta = 0.03;
                break;
            }
        }
    }
    virtual void LevelChanged(){
        Item::LevelChanged();
        Calculate();
    }
    virtual void LevelDown(){
        Item::LevelDown();
        if(level >= 15){
            level -= 1;
            Calculate();
        }
        percent += delta * stack;
    }
};

class Sword : public Equipment{
public:
    Sword(string name){
        this->name = name;
        this->level = 14;
        this->stack = 0;
        this->percent = 2.00;
        this->delta = 0.20;
    }
    ~Sword();
};

class Jewelry : public Item{
public :
    Jewelry(){
        myType = ItemType::Jewelry;
    }
    virtual void Calculate(){
        switch(level){
            case 15:{
                percent = 25.00;
                delta = 2.50;
                break;
            }
            case 16:{
                percent = 10.00;
                delta = 1.00;
                break;
            }
            case 17:{
                percent = 7.50;
                delta = 1.25;
                break;
            }
            case 18:{
                percent = 2.50;
                delta = 0.25;
                break;
            }
            case 19:{
                percent = 0.50;
                delta = 0.05;
                break;
            }
        }
    }
    virtual void LevelChanged(){
        Item::LevelChanged();
        Calculate();
    }
    virtual void LevelDown(){
        stack += 1;
        if(level >= 16){
            level = 15;
            Calculate();
        }
        percent += delta * stack;
    }
};

class Ring : public Jewelry{
public:
    Ring(string name){
        this->name = name;
        this->level = 15;
        this->stack = 0;
        this->percent = 25.00;
        this->delta = 2.50;
    }
    ~Ring();
};

class EnhanceSystem{
private:
    Item* currentItem;
public:
    EnhanceSystem();
    ~EnhanceSystem();
    void SetItem(Item** item);
    void RemoveItem();
    void Enhance();
    void Failed();
    void Success();
    void Print();
    void ScanInput();
};
#endif