//
// Created by Brynn Maleryn on 9/12/24.
//
#include "Dog.hpp"
#include <iostream>
using namespace std;
#ifndef DOG_CPP_
#define DOG_CPP_

Dog::Dog(string n){
    name = n;
    strength = 50;
    x = 0;
    y = 0;
}
Dog::Dog(){
    name = "Fluffy";
    strength = 50;
    x = 0;
    y = 0;
}

bool Dog::changeStrength(int amt) {
    strength += amt;
    printDog();
    if(strength <= 0) {
        die();
        return false;
    }
    return true;
}
void Dog::die() {
    cout << "Your dog died!" << endl;
}
void Dog::printDog() {
    cout << name << endl;
    cout << strength << endl;
}
void Dog::won() {
    cout << "Yay! Your dog made it through the forest!" << endl;
}
void Dog::reset() {
    strength = 50;
    x = 0;
    y = 0;
}
#endif