#include "student.h"

Student::Student(int startTime, int serviceTime){
    this->startTime = startTime;
    this->serviceTime = serviceTime;
}

Student::Student(){
    startTime = 0;
    serviceTime = 0;
}