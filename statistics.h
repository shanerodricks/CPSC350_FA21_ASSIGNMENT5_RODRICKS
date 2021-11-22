#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics{
    public:
        double totalWaitTime;
        int medianWaitTime;
        int longestWaitTime;
        int waitOverTenMins;
        double meanIdleTime;
        int longestIdleTime;
        int idleOverFiveMins;
        int numStudents;
};

#endif