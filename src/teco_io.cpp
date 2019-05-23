#include "teco_io.hpp"
#include "SimulationTimeType.hpp"

void write_header (ofstream& myfile){
    
    myfile << "#Year\t" << "Doy\t" << "Cinput(gC/s)\t" << "Foliage(gC/m2)\t" << "Woody(gC/m2)\t" << "Met_litter(gC/m2)\t" << "Str_litter(gC/m2)\t" << "Fast_soil(gC/m2)\t" << "Slow_soil(gC/m2)\t" << "Pass_soil(gC/m2)\t" << "Residence time(yr)\t" << "Capacity(gC/m2)\t" << "Potential(gC/m2)\t" << endl;
    
}

void write_c_state (ofstream& outfile, EcosystemCarbonStateType& my_state){
    
    outfile << Time.thisYear << "\t" << Time.doy << "\t" << my_state.cinput << "\t";
    for (const auto &e : my_state.Cpool_out) outfile << e / 365. << "\t";
    outfile << my_state.ResidenceT_out / 365 / sec_in_y << "\t" << my_state.CStorageCapacity_out / 365. << "\t" << my_state.CStoragePotential_out / 365.  << endl;
}

void read_inputF (ifstream& infile) { }
