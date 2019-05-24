#include "EcosystemCarbonStateType.hpp"
#include "SimulationTimeType.hpp"
SimulationTimeType Time;

void EcosystemCarbonStateType::init(){
    
    B(ifoliage) = 0.45;
    B(iwoody) = 0.55;
    
    K(ifoliage ,ifoliage ) = 0.00176;
    K(iwoody   ,iwoody   ) = 0.000100104;
    K(imetlit  ,imetlit  ) = 0.021468;
    K(istrlit  ,istrlit  ) = 0.000845;
    K(imicsoil ,imicsoil ) = 0.008534;
    K(islowsoil,islowsoil) = 8.976E-5;
    K(ipasssoil,ipasssoil) = 3.09564E-6;
    
    K /= 3600 * 24.;
    
    A(imetlit  , ifoliage ) = 0.7123;
    A(istrlit  , ifoliage ) = 0.2877;
    A(istrlit  , iwoody   ) = 1;
    A(imicsoil , imetlit  ) = 0.45;
    A(imicsoil , istrlit  ) = 0.275;
    A(imicsoil , islowsoil) = 0.42;
    A(imicsoil , ipasssoil) = 0.45;
    A(islowsoil, imicsoil ) = 0.296;
    A(islowsoil, istrlit  ) = 0.275;
    A(ipasssoil, imicsoil ) = 0.004;
    A(ipasssoil, islowsoil) = 0.03;
    
    AK_inv = (A*K).i();
}

void EcosystemCarbonStateType::update_C_state(){
    
#warning(cinput should be read from file)
    if (Time.is_startof_year()) Cpool_out = vec(npools, fill::zeros);
    
    dC_dt = cinput * B + A * K * Cpool;
    Cpool += dC_dt * Time.dt;
    Cpool_out += Cpool;
}

void EcosystemCarbonStateType::diagnostic(){
    
    if(Time.doy == 1){
    ResidenceT_out = 0.;
    CStorageCapacity_out = 0.;
    CStoragePotential_out = 0.;
    }
    
    ResidenceT = -AK_inv * B;
    CStorageCapacity = -ResidenceT * cinput;
    CStoragePotential = -AK_inv * dC_dt;

    ResidenceT_out += sum(ResidenceT);
    CStorageCapacity_out += sum(CStorageCapacity);
    CStoragePotential_out += sum(CStoragePotential);
}

void EcosystemCarbonStateType::matrixSpinUp(){
    
    static mat AK = mat(npools, npools, fill::zeros);
    static vec BI = vec(npools, fill::zeros);
    static int count = 0;
    
    count++;
    
    AK += A * K;
    BI += cinput * B;
        
    if (Time.is_endof_forcing()){
        Cpool = -(AK / count).i() * (BI / count);
        
        AK = mat(npools, npools, fill::zeros);
        BI = vec(npools, fill::zeros);
        count = 0;
    }
}






