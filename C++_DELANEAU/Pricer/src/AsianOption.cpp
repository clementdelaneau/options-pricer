#include "AsianOption.h"
#include "Option.h"
#include <algorithm>
#include <string>
#include <cmath>

AsianOption::AsianOption(double S,double K,double sigma, double T,double r, std::string payoffType,int N,int ns):Option( S, K, sigma,  T, r, payoffType,N,ns)
{
    //ctor
}

AsianOption::~AsianOption()
{
    //dtor
}


double AsianOption:: random_path() {
  double x=0;
  double y=0;
  double euclid_dist=0;

  do {
    x=2*rand()/static_cast<double>(RAND_MAX)-1;
    y =2*rand()/static_cast<double>(RAND_MAX)-1;
    euclid_dist=x*x+y*y;
  } while(euclid_dist>=1);

  return x*sqrt(-2*log(euclid_dist)/euclid_dist);
}

double AsianOption::AsianPayoffCall(double S)
{

    double payoff=0;
    for(int i=0;i<=GetN();i++)
    {
        payoff+=std::max(S-GetK(),0.0);
    }
    return payoff/(GetN()+1);
}


double AsianOption::AsianPayoffPut(double S)
{

    double payoff=0;
    for(int i=0;i<=GetN();i++)
    {
        payoff+=std::max(GetK()-S,0.0);
    }
    return payoff/GetN()+1;
}

double AsianOption::MonteCarlo_Call()
{
  double S_t=GetS()*exp(GetT()*(GetR()-0.5*GetSigma()*GetSigma()));
  double S_wiener=0;
  double payoff_sum=0;

  for (int i=0;i<GetNs();i++) {
    S_wiener=S_t*exp(sqrt(GetSigma()*GetSigma()*GetT())*random_path());
    payoff_sum+=AsianPayoffCall(S_wiener);
  }

  return (payoff_sum/static_cast<double>(GetNs()))*exp(-GetR()*GetT());
}


double AsianOption::MonteCarlo_Put() {
  double S_t=GetS()*exp(GetT()*(GetR()-0.5*GetSigma()*GetSigma()));
  double S_wiener=0;
  double payoff_sum=0;

  for (int i=0;i<GetNs();i++) {
    S_wiener=S_t*exp(sqrt(GetSigma()*GetSigma()*GetT())*random_path());
    payoff_sum+=AsianPayoffPut(S_wiener);
  }

  return (payoff_sum/static_cast<double>(GetNs()))*exp(-GetR()*GetT());
}

