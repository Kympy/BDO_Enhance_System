#ifndef __Enhance__H__
#define __Enhance__H__
#include <iostream>
#include <string>
#include <map>
using namespace std;
// 아이템의 타입 -> 장비, 악세사리
enum class ItemType{
    Equipment, Jewelry
};
// 아이템의 타입에 대응되는 문자열
const map<ItemType, string> typeName{
    { ItemType::Equipment, "Equipment" },
    { ItemType::Jewelry, "Jewelry"}
};
// 아이템 최상위 클래스
class Item{
protected:
    // 아이템의 이름
    string name;
    // 아이템의 타입
    ItemType myType;
    // 현재 강화 단계
    int level;
    // 현재 쌓인 스택
    int stack;
    // 현재 강화 성공률
    double percent;
    // 현재 스택 당 강화 성공률 증가량
    double delta;
    // 현재 Level을 기반으로 강화 성공률 계산
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
    /// @brief 강화 성공 시 레벨 변경
    virtual void LevelChanged(){
        level += 1;
        stack = 0;
    }
    /// @brief 강화 실패 시 스택 변경
    virtual void LevelDown(){
        stack += 1;
    }
    int GetLevel(){
        return level;
    }
    /// @brief 현재 강화 단계에 대응되는 문자열 출력
    /// @return 강화 단계 문자 표시
    string GetStringLevel(){
        // 15 단계 까지는 숫자로 표시
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
    virtual void Failed(){ }
    /// @brief 임의로 스택을 추가시킴
    /// @param value 추가할 스택 수치
    void AddStack(int value){
        stack += value;
        percent += delta * value;
    }
};
// 아이템 클래스를 상속 받는 장비 클래스
class Equipment : public Item{
public:
    Equipment(){
        myType = ItemType::Equipment;
    }
    // 장비 아이템의 단계 별 확률 데이터
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
// 장비 클래스를 상속 받는 검 클래스
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
// 아이템 클래스를 상속 받는 악세사리 클래스
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
// 악세사리 클래스를 상속 받는 반지 클래스
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
// 강화 시스템 클래스
class EnhanceSystem{
private:
    // 현재 강화 시스템에 활성화 된 아이템
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