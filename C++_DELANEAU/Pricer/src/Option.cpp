#include "Option.h"
#include <cmath>

using namespace std;
Option::Option(double S,double K,double sigma, double T,double r, string payoffType,int N,int ns)
{
    this->S=S;
    this->K=K;
    this->sigma=sigma;
    this->T=T;
    this->r=r;
    this->payoffType=payoffType;
    this->N=N;
    this->ns=ns;
}

Option::~Option()
{
    //dtor
}


void Option::SetN(int n)
{
    N=n;
}
//*********************************Geters*************************************************************
int Option::GetN()
{
    return N;
}

std::string Option::GetPayoffType()
{
    return payoffType;
}

double Option::GetS()
{
    return S;
}

double Option::GetK()
{
    return K;
}


double Option::GetSigma()
{
    return sigma;
}

double Option::GetT()
{
    return T;
}

double Option::GetR()
{
    return r;
}


int Option::GetNs()
{
    return ns;
}


//*******************************************************Black-Sholes methods****************************************************
// We use Stock function in BinLattice class. That's why we put Black-Sholes methods used in Stock function here, the superclass Option.
double Option::u()
{
    double u;
    u=exp(GetSigma()*sqrt(GetT()/GetN()));
    return u;
}

double Option::d()
{
    double d;
    d=exp(-GetSigma()*sqrt(GetT()/GetN()));
    return d;
}

double Option::q()
{
    double risk_neutral;
    risk_neutral=(exp(GetR()*(GetT()/GetN()))-d())/(u()-d());
    return risk_neutral;
}



double Option::Stock(int i,int n ){
      return GetS()*pow(u(),i)*pow(d(),n-i);
}

