#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
//bool scheduleHelper(size_t day, size_t worker, DailySchedule& sched, const AvailabilityMatrix& avail, vector<int>& shiftsWorked, const size_t maxShifts, const size_t dailyNeed);
bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsWorked, size_t day, size_t pos);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t n = avail.size();
    if (n == 0){
      return false;
    }

    size_t k = avail[0].size();
    sched.assign(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shiftsWorked(k,0);
    //return scheduleHelper(0, 0, sched, avail, shiftsWorked, maxShifts, dailyNeed);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, 0, 0);


}


bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsWorked, size_t day, size_t pos)
{
    if(day == avail.size()){
      return true;
    }
    if(pos == dailyNeed){
      return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, day+1, 0);
    }

    for(size_t worker = 0; worker < avail[0].size(); worker++){
        if(avail[day][worker] && shiftsWorked[worker] < maxShifts){
            bool workedAlr = false;
            for(size_t i = 0; i < pos; i++){
                if(sched[day][i] == worker){
                    workedAlr = true;
                    break;
                }
            }
            if (workedAlr == false){
              sched[day][pos] = worker;
              shiftsWorked[worker]++;
              if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, day, pos+1)){
                return true;
              }
              shiftsWorked[worker]--;
            }
        }
    }

    return false;
}


/*
bool scheduleHelper(size_t day, size_t worker, DailySchedule& sched, const AvailabilityMatrix& avail, vector<int>& shiftsWorked, const size_t maxShifts, const size_t dailyNeed){
    if (day == sched.size()){
        return true; 
    }
    else{
      size_t amountWorkers = avail.size();
      for (size_t i = 0; i < amountWorkers; i++){
        if (avail[day][worker]== false){}
        else{
          if (shiftsWorked[i]< maxShifts){
            bool WorkedAlr = false; 
            for (size_t j = 0; j<worker; j++){
              if(sched[day][j]== i){
                WorkedAlr =true;
                break;
              }
            }
            if (WorkedAlr == false){
              sched[day][worker] = i;
              shiftsWorked[i]++;

              bool valid;
              if (worker+1 < dailyNeed){
                valid = scheduleHelper(day,worker+1,sched,avail,shiftsWorked, maxShifts, dailyNeed);
              }
              else{
                valid = scheduleHelper(day,0,sched,avail,shiftsWorked, maxShifts, dailyNeed);
                
              }
              if (valid == true){
                return true; 
              }

              sched[day][worker] = INVALID_ID;
              shiftsWorked[i]--;
            }
          } 
        }
      }
      return false;
      
        //PREV USED PORTION
        for (size_t i = 0; i < avail[0].size(); i++ ){
            if (avail[day][i] == 1){
                sched[day][i] = 1;
                shiftsWorked[i]++;
                if (RecMet(dailyNeed, maxShifts, shiftsWorked, day, workers)){
                    return scheduleHelper(day+1, unfilledMatrix, avail, shiftsWorked );
                }
                else{
                    unfilledMatrix[day][i] = 0;
                    shiftsWorked[i]--;
                }
            }
        }
        return false;
        //PREV USED PORTION
    //}
//}


// PREV USED PORTION W SECOND HELPER
  for (size_t i = 0; i < avail[0].size(); i++ ){
    if (avail[day][i] == 1){
      sched[day][i] = 1;
      shiftsWorked[i]++;
      if (RecMet(dailyNeed, maxShifts, shiftsWorked, day, workers)){
        return scheduleHelper(day+1, unfilledMatrix, avail, shiftsWorked );
      }
      else{
        unfilledMatrix[day][i] = 0;
        shiftsWorked[i]--;
          }
        }
      }
    return false;
  }
*/
    


