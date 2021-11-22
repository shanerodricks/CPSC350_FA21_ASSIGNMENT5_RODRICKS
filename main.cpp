#include "queue.h"
#include "window.h"
#include "student.h"
#include <fstream>
#include <iostream>
using namespace std;
bool isDone(Window windows[], int numWindows, GenQueue<Student> &events);
void getStats(Window windows[], int numWindows);
void swap(int *x, int *y);
void sort(int array[], int length);

int main(int argc, char **argv){
    int numWindows;
    ifstream inputFile("input.txt");
    if(!inputFile.is_open()){
        cout << "Could not open the file." << "input.txt" << endl;
        exit(1);
    }
    inputFile >> numWindows;
    Window* windows = new Window[numWindows];
    for(int i = 0; i < numWindows; ++i){
        Window window;
        windows[i] = window;
    }
    GenQueue<Student> events;
    int nextTime;
    int numStudents;
    int serviceTime;
    int currentTime = 0;
    bool done = false;
    while(inputFile >> nextTime >> numStudents){
        for(int i = 0; i < numStudents; ++i){
            inputFile >> serviceTime;
            Student student(nextTime, serviceTime);
            
            events.insert(student);
        }
    }
    while(!done){
        currentTime++;
        for(int i = 0; i < numWindows; ++i){
            
            windows[i].update(currentTime);
        }
        if(!events.isEmpty()){
            
            Student student = events.peek();
            
            while(student.startTime == currentTime){
                
                events.remove();
                bool addStudent = false;
                for(int i = 0; i < numWindows; ++i){
                    if(windows[i].isEmpty()){
                        
                        windows[i].addStudent(student.startTime, student.serviceTime);
                        addStudent = true;
                        break;
                    }
                }
                if(addStudent == false){
                    windows[0].addStudent(student.startTime, student.serviceTime);
                }
                if(events.isEmpty()){
                    break;
                }
                student = events.peek();
            } 
        }
        
        done = isDone(windows, numWindows, events);
        
    }
    getStats(windows, numWindows);
}

void getStats(Window windows[], int numWindows){
    double meanWaitTime = 0;
    int medianWaitTime = 0;
    int longestWaitTime = 0;
    int waitOverTenMins = 0;
    double meanIdleTime = 0;
    int longestIdleTime = 0;
    int idleOverFiveMins = 0;
    int totalIdleTime = 0;
    int totalWaitTime = 0;
    int numStudents = 0;
    
    //figure out total number of students
    //get numStudents from each window, add them up
    for(int i = 0; i < numWindows; ++i){
        numStudents = numStudents + windows[i].returnTotalNumStudents();
    }

    //create array of ints using numStudents
    int *waitTimes = new int[numStudents];

    //loop through all windows getting waitTimes from each
    //add them to the array
    int index = 0;
    for(int i = 0; i < numWindows; ++i){
        GenQueue<int>* waitTimesQueue = windows[i].getWaitTimes();
        while(!waitTimesQueue->isEmpty()){
            int waitTime = waitTimesQueue->remove();
            waitTimes[index] = waitTime;
            index++;
        }
    }

    //sort the array
    sort(waitTimes, numStudents);

    //calculate mean wait time by adding up all the waitTimes / numStudents
    for(int i = 0; i < numStudents; ++i){
        totalWaitTime+=waitTimes[i];
    }
    if(totalWaitTime != 0){
        meanWaitTime = double(totalWaitTime) / double(numStudents);
    }
    
    //median wait time is middle of sorted array
    if(totalWaitTime != 0){
        medianWaitTime = waitTimes[numStudents/2];
        longestWaitTime = waitTimes[numStudents - 1]; 
    }

    //to calculate wait over ten mins, go through array and find elements over 10 mins
    for(int i = 0; i < numStudents; ++i){
        if(waitTimes[i] > 10){
            waitOverTenMins++;
        }
    }
    //meanIdle is adding up all idle times from each window / numWindows
    for(int i = 0; i < numWindows; ++i){
        totalIdleTime+=windows[i].returnTotalIdleTime();
    }
    if(totalIdleTime!=0){
        meanIdleTime = double(totalIdleTime) / double(numWindows);
    }
    
    //longestIdleTime get idleTime from each window and compute max
    longestIdleTime = windows[0].returnTotalIdleTime();
    for(int i = 0; i < numWindows; ++i){
        if(windows[i].returnTotalIdleTime() > longestIdleTime){
            longestIdleTime = windows[i].returnTotalIdleTime();
        }
    }

    //idleover5mins is same as wait over ten mins
    for(int i = 0; i < numWindows; ++i){
        if(windows[i].returnTotalIdleTime() > 5){
            idleOverFiveMins++;
        }
    } 

    cout << "Mean Wait Time: " << meanWaitTime << endl;
    cout << "Median Wait Time: " << medianWaitTime << endl;
    cout << "Longest Wait Time: " << longestWaitTime << endl;
    cout << "Wait Over 10 Minutes: " << waitOverTenMins << endl;
    cout << "Mean Idle Time: " << meanIdleTime << endl;
    cout << "Longest Idle Time: " << longestIdleTime << endl;
    cout << "Idle Time Over 5 Minutes: " << idleOverFiveMins << endl;
}

void sort(int array[], int length){
    int minimumIndex;
    for(int i = 0; i < length-1; ++i){
        minimumIndex = i;
        for(int j = i + 1; j < length; ++j){
            if(array[j] < array[minimumIndex]){
                minimumIndex = j;
            }
        }
        swap(&array[minimumIndex], &array[i]);
    }
}

void swap(int *x, int *y){
    int temporary = *x;
    *x = *y;
    *y = temporary;
}

bool isDone(Window windows[], int numWindows, GenQueue<Student> &events){
    for(int i = 0; i < numWindows; ++i){
        if(windows[i].isEmpty() == false){
            return false;
        }
    }
    if(!events.isEmpty()){
        return false;
    }
    return true;
}