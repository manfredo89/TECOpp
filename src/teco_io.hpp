/**
 * @date    Created on: 21/may/2019
 * @author  Manfredo di Porcia
 *
 * @brief This is the I/O functions for the TECO model.
 * @todo Build the function to read the input. For now input is embedded in the code.
 *
 */

#ifndef teco_io_hpp
#define teco_io_hpp

#include <fstream>
#include "EcosystemCarbonStateType.hpp"
using namespace std;

void read_inputF (ifstream&);
void write_header (ofstream&);
void write_c_state (ofstream&, EcosystemCarbonStateType&);
#endif /* teco_io_hpp */
