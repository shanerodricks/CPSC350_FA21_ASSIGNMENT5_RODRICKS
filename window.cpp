#include "window.h"
#include "queue.h"

Window::Window(){
    students = new GenQueue<Student>();
    waitTimes = new GenQueue<int>();
}

void Window::addStudent(int arrivalTime, int serviceTime){
    Student student(arrivalTime, serviceTime);
    students->insert(student);
}


void Window::update(int currentTime){
    if(students->isEmpty()){
        totalIdleTime++;
    }
    else{
        Student student = students->peek();
        //checks if current student is done
        if(student.startTime + student.serviceTime == currentTime){
            //if done, remove the student
            students->remove();
            if(!students->isEmpty()){
                //check for next student
                Student nextStudent = students->peek();
                //check if its time for next student to start
                int waitTime = currentTime - nextStudent.startTime;
                if(waitTime > 0){
                    cout << "inserting: " << waitTime << endl;
                    
                    waitTimes->insert(waitTime);
                }
            }
        }
    }
}

bool Window::isEmpty(){
    
    return students->isEmpty();
}

int Window::returnTotalIdleTime(){
    return totalIdleTime;
}
        
GenQueue<int>* Window::getWaitTimes(){
    return waitTimes;
}

int Window::returnTotalNumStudents(){
    return waitTimes->getSize();
}