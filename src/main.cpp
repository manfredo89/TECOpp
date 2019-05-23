/**
 * @date    Created on: 21/may/2019
 * @author  Manfredo di Porcia <manfredodiporcia@gmail.com>
 *
 * @brief Main file for TECO simulation
 *
 * @mainpage TECO++ Main page
 * @section Brief
 *
 * TECO++ is a C++ translation of the Fortran TECO model. \n
 * TECO is a Carbon transfer model introduced by Y. Luo and J. Reynolds (1999). \n
 * Please cite original reference when using this algorithm. \n
 * https://esajournals.onlinelibrary.wiley.com/doi/10.1890/0012-9658%281999%29080%5B1568%3AVOEFCE%5D2.0.CO%3B2
 *
 * \n
 *
 * The equation describing the carbon transfer is the matrix representation of \n\n
 * \f$ \frac{dX(t)}{dt} = BI(t) - A \xi KX(t) \f$
 *
 * \n
 *
 * To compile link with Armadillo libraries (http://arma.sourceforge.net/) \n\n
 *
 * Test run for 10000 years with different compilers: \n
 * TECO++ (icpc -fast)     -> 9.112 s \n
 * TECO++ (clang++ -Ofast) -> 8.689 s \n
 * TECO   (ifort -fast)    -> 6.107 s \n
 *
 */

#include <iostream>
#include "EcosystemCarbonStateType.hpp"
#include "teco_io.hpp"
#include "SimulationTimeType.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    try {
        if(argc != 1) throw (string("Usage is ") + argv[0] + string(" input file"));
                
        /* Open output file */
        ofstream myfile;
        myfile.open("output.txt");
        if(!myfile.good()) throw(string("Could not open output file "));
        write_header(myfile);
        
        /* Instantiate cabon state class */
        EcosystemCarbonStateType cs_ecosys;
        
        /* Time variables */
        int startyr = 1;
        int endyr = 1000;
        int nyr_forc = 10;
        bool is_SASU_spinup = true;
        bool is_diagnostic = true;
        
        /* Initialize time class */
        Time.init(startyr, endyr, nyr_forc);
        
        /* Initialize carbon state */
        cs_ecosys.init();
                
        for (Time.start(); !Time.is_end(); Time.tick_time()){
            
            /* Update carbon */
            cs_ecosys.update_C_state();
            
            /* Write output */
            if (Time.printC()) write_c_state(myfile, cs_ecosys);
            
            /* Compute diagnostic variables */
            if (is_diagnostic) cs_ecosys.diagnostic();
            
            /* Perform semi-analytical spin-up */
            if(is_SASU_spinup) cs_ecosys.matrixSpinUp();
        }
        myfile.close();
    }
    
    catch (string &e){
        cout << e << endl;
        return 1;
    }
    
    return 0;
}
