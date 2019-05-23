/**
 * @file    SimulationTimeType.hpp
 * @date    Created on: 21/may/2019
 * @author  Manfredo di Porcia
 *
 * @class SimulationTimeType
 * @brief
 *
 * This class holds all the time related variables.
 *
 */

#ifndef SimulationTimeType_hpp
#define SimulationTimeType_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class SimulationTimeType{
    
private:
    
    int nyr_forc; /**< Number of years of forcing */
    
    chrono::system_clock::time_point start_time; /**< Main loop start time */
    chrono::system_clock::time_point end_time; /**< Main loop end time */
    
    /** Is it the end of the year */
    inline bool is_endof_year() {return this->doy == 365;};
    
public:

    double dt = 86400.; /**< integration time */

    int startYear; /**< First year of simulation */
    int endYr; /**< Last year of simulation */

    int thisYear; /**< Current year */
    int doy; /**< Curent day od the year */
    
    chrono::system_clock::time_point sim_time; /**< Main loop duration */

    /** Simulation start. */
    void start();
    
    /** Simulation end and print execution time.
     * @return true if simulation year is greater than last allowed year.
     */
    bool is_end();

    /** Advance one time step. */
    void tick_time();
    
    /** init
     * @param startyr First year
     * @param endyr Last year
     * @param nyr_forc Number of years of forcing
     */
    void init(int startyr, int endyr, int nyr_forc);
    
    /** Is it time to print Carbon output */
    inline bool printC() {return doy == 365;}
    
    /** Is it time to rrun diagnostic */
    inline bool diagnostic() {return thisYear % 1 == 0;}

    /** Is it start of the year */
    inline bool is_startof_year() {return this->doy == 1;}
    
    /** Is it the end of the external forcing */
    inline bool is_endof_forcing(){ return this->is_endof_year() && this->thisYear % this->nyr_forc == 0;}
};

extern SimulationTimeType Time;


#endif /* SimulationTimeType_hpp */
