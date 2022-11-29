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


    EnhanceSystem* enhanceSys = new EnhanceSystem;

    Item* sword = new Sword("Devil Sword");
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
void EnhanceSystem::SetItem(Item** item){
    currentItem = *item;
    Print();
}
void EnhanceSystem::RemoveItem(){
    currentItem = nullptr;
}
void EnhanceSystem::Enhance(){
    if(currentItem == nullptr) return;
    if(currentItem->GetLevel() == 20){
        Print();
        return;
    }

    double myPercent = currentItem->GetPercent() + currentItem->GetDelta() * currentItem->GetStack();
    if(randPercent(mersenne) <= myPercent){
        Success();
    }
    else{
        Failed();
    }
    Print();
}
void EnhanceSystem::Failed(){
    currentItem->LevelDown();
}
void EnhanceSystem::Success(){
    currentItem->LevelChanged();
}
void EnhanceSystem::Print(){
    system("CLS");
    cout << "::ENHANCE SYSTEM::" << endl;
    cout << "=========================================" << endl;
    cout << endl;
    cout << "-ITEM INFO-" << endl << endl;

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
    cout << "=========================================" << endl;
    cout << "1. Enhance  2. Add 10 Stack 3. Create Weapon  4. Create Jewelry" << endl;
    cout << "0. Exit Program" << endl;
    ScanInput();
}
void EnhanceSystem::ScanInput(){
    int input;
    cout << "INPUT : ";
    cin >> input;

    switch (input)
    {
    case 1:{
        Enhance();
        break;
    }
    case 2:{
        currentItem->AddStack(10);
        Print();
        break;
    }
    case 3:{
        string name;
        cout << "Input Item Name : ";
        cin.get();
        getline(cin, name, '\n');
        Item* temp = new Sword(name);
        delete currentItem;
        SetItem(&temp);
    }
    case 4:{
        string name;
        cout << "Input Item Name : ";
        cin.get();
        getline(cin, name, '\n');
        Item* temp = new Ring(name);
        delete currentItem;
        SetItem(&temp);
    }
    case 0:{
        exit(0);
        break;
    }
    default:
        Print();
        break;
    }
}