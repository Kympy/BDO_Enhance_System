#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <random>
#include "BlackDessert.h"
using namespace std;
#define endl "\n"

random_device rd;
mt19937_64 mersenne(rd());
uniform_real_distribution<double> randPercent(0.0, 100.0);

int main(int argc, char* argv[]){
    // 강화 시스템 생성
    EnhanceSystem* enhanceSys = new EnhanceSystem;
    // 임의의 장비 초기 생성
    Item* sword = new Sword("Devil Sword");
    // 아이템 대입
    enhanceSys->SetItem(&sword);

    delete sword;
    delete enhanceSys;
}

EnhanceSystem::EnhanceSystem(){
    //Print();
}
EnhanceSystem::~EnhanceSystem(){
    cout << endl << "-- Enhance System Shut Down --" << endl << endl;
}
/// @brief 아이템을 강화 시스템에 대입한다.
/// @param item 강화할 아이템
void EnhanceSystem::SetItem(Item** item){
    currentItem = *item;
    Print();
}
/// @brief 아이템을 강화 시스템에서 제거한다.
void EnhanceSystem::RemoveItem(){
    currentItem = nullptr;
}
/// @brief 강화를 실시한다.
void EnhanceSystem::Enhance(){
    // 아이템이 존재하지 않거나, 최대 강화단계 도달 시 종료
    if(currentItem->GetLevel() == 20 || currentItem == nullptr){
        Print();
        return;
    }
    // 0 ~ 100 사이의 double 형 난수를 생성한다
    // 해당 난수가 아이템의 현재 강화 확률 범위 안에 존재하면 강화 성공
    double myPercent = currentItem->GetPercent() + currentItem->GetDelta() * currentItem->GetStack();
    if(randPercent(mersenne) <= myPercent){
        Success();
    }
    else{
        Failed();
    }
    // 결과 갱신
    Print();
}
/// @brief 강화 실패 시 강화 단계 하락
void EnhanceSystem::Failed(){
    currentItem->LevelDown();
}
/// @brief 강화 성공 시 강화 단계 상승
void EnhanceSystem::Success(){
    currentItem->LevelChanged();
}
/// @brief 강화 시스템의 결과 화면 갱신
void EnhanceSystem::Print(){
    // 화면 클리어
    system("CLS");
    cout << "::ENHANCE SYSTEM::" << endl;
    cout << "=========================================" << endl;
    cout << endl;
    cout << "-ITEM INFO-" << endl << endl;
    // 아이템의 정보 출력
    if(currentItem != nullptr){
        cout << "Name : " << currentItem->GetName() << endl;
        cout << "Type : " << currentItem->GetType()<< endl;
        cout << "Level : " << currentItem->GetStringLevel()<< endl;
        cout << "Stack : +" << currentItem->GetStack() << endl; 
        cout << fixed;
        cout.precision(2);
        cout << "Percent : " << currentItem->GetPercent() << " %" << endl;
    }
    else {
        cout << "Name : NULL" << endl;
        cout << "Type : NULL" << endl;
        cout << "Level : 0" << endl;
        cout << "Stack : +0" << endl;
        cout << "Percent : 0.00%" << endl;
    }
    cout << endl;
    // 메뉴 출력
    cout << "=========================================" << endl;
    cout << "1. Enhance  2. Add 10 Stack 3. Create Weapon  4. Create Jewelry" << endl;
    cout << "0. Exit Program" << endl;
    // 메뉴 입력 대기
    ScanInput();
}
/// @brief 매 갱신 마다 선택할 메뉴의 번호를 입력받는다.
void EnhanceSystem::ScanInput(){
    int input;
    cout << "INPUT : ";
    cin >> input;

    switch (input)
    {
    // 강화
    case 1:{
        Enhance();
        break;
    }
    // 10 스택 추가
    case 2:{
        currentItem->AddStack(10);
        Print();
        break;
    }
    // 새로운 장비 아이템 생성
    case 3:{
        string name;
        cout << "Input Item Name : ";
        cin.get();
        getline(cin, name, '\n');
        Item* temp = new Sword(name);
        delete currentItem;
        SetItem(&temp);
    }
    // 새로운 악세사리 아이템 생성
    case 4:{
        string name;
        cout << "Input Item Name : ";
        cin.get();
        getline(cin, name, '\n');
        Item* temp = new Ring(name);
        delete currentItem;
        SetItem(&temp);
    }
    // 프로그램 종료
    case 0:{
        exit(0);
        break;
    }
    // 예외 입력 시 화면 갱신 후 재 입력 대기
    default:
        Print();
        break;
    }
}