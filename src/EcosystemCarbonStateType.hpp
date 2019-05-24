/**
 * @date    Created on: 21/may/2019
 * @author  Manfredo di Porcia
 *
 * @class EcosystemCarbonStateType
 * @brief
 *
 * This is the main class of the TECO model. It holds all physical variables and methods.
 *
 */

#ifndef EcosystemCarbonStateType_hpp
#define EcosystemCarbonStateType_hpp

#define npools 7 /**<Total number of carbon pools */
#define sec_in_y (365 * 24 * 3600.) /**< Number of second in one year */

#include "armadillo"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace arma;
using namespace std;

class EcosystemCarbonStateType{
    
private:
    const int ifoliage  = 0; /**< leaf pool index */
    const int iwoody    = 1; /**< wood pool index */
    const int imetlit   = 2; /**< pool index */
    const int istrlit   = 3; /**< pool index */
    const int imicsoil  = 4; /**< pool index */
    const int islowsoil = 5; /**< pool index */
    const int ipasssoil = 6; /**< pool index */
    
    vec dC_dt; /**< Carbon variation */
    vec B; /**< Allocation vector */
    mat K; /**< Turnover matrix */
    mat A; /**< Transfer matrix */
    mat AK_inv; /**< Inverse of AK */
    
    vec ResidenceT; /**< Carbon residence time */
    vec CStorageCapacity; /**< Carbon storage capacity */
    vec CStoragePotential; /**< Carbon storage potential */
    

public:

    vec Cpool;  /**< Carbon pool */
    vec Cpool_out; /**< Carbon pool for output */
    
    double ResidenceT_out = 0.; /**< Carbon residence time for output */
    double CStorageCapacity_out = 0.; /**< Carbon storage capacity for output */
    double CStoragePotential_out = 0.; /**< Carbon storage potential for output */

    double cinput = 2.245E-5; /**< Carbon input */

    
    EcosystemCarbonStateType()
    {
        
        B = vec(npools, fill::zeros);
        dC_dt = vec(npools, fill::zeros);
        Cpool = vec(npools, fill::zeros);
        Cpool_out = vec(npools, fill::zeros);
        A = mat(npools,npools,fill::eye) * -1;
        K = mat(npools,npools,fill::zeros);
        AK_inv = mat(npools,npools,fill::zeros);
        ResidenceT = vec(npools,fill::zeros);
        CStorageCapacity = vec(npools,fill::zeros);
        CStoragePotential = vec(npools,fill::zeros);
    }
    
    /** Initialize carbon state pools and matrices */
    void init();
    /** Main TECO step to update carbon pools */
    void update_C_state();
    /** Diagnostic */
    void diagnostic();
    /** Semi-analytical spinup (?) */
    void matrixSpinUp();
    
};

#endif /* EcosystemCarbonStateType_hpp */
