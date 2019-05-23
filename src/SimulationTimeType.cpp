#include "SimulationTimeType.hpp"

void SimulationTimeType::init(int startyr, int endyr, int nyr_forc){
    
    this->thisYear = this->startYear = startyr;
    this->doy = 1;
    this->endYr = endyr;
    this->nyr_forc = nyr_forc;
    
}

void SimulationTimeType::tick_time(){
    
    this->doy++;

    if (this->doy > 365){
        cout << "Year " << this->thisYear << endl;
        this->thisYear++;
        this->doy = 1;
    }
}

void SimulationTimeType::start(){
    this->thisYear = 1;
    this->doy = 1;
    this->start_time = chrono::system_clock::now();
}

bool SimulationTimeType::is_end(){
    
    if (this->thisYear < this->endYr) return false;
    else
    {
        this->end_time = chrono::system_clock::now();
        chrono::duration<double> sim_time = this->end_time - this->start_time;
        cout << "Simulation completed. \nMain loop took " << sim_time.count() << " s\n" << endl;
        return true;
    }
}

