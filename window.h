#ifndef WINDOW_H
#define WINDOW_H
#include "queue.h"
#include "student.h"


class Window{
    private:
        GenQueue<Student> *students;
        GenQueue<int> *waitTimes;
        int totalIdleTime = 0;
    public:
        Window();
        void addStudent(int arrivalTime, int serviceTime);
        void update(int currentTime);
        bool isEmpty();
        int returnTotalIdleTime();
        GenQueue<int> *getWaitTimes();
        int returnTotalNumStudents();
};


#endif