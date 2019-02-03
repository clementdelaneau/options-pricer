#include "Option.h"
#define _USE_MATH_DEFINES  //to use Pi as M_PI
#include <math.h>
#include <vector>
#include "EuropeanOption.h"

EuropeanOption::EuropeanOption(double S,double K,double sigma, double T,double r, std::string payoffType,int N,int ns):Option( S, K, sigma,  T, r, payoffType,N,ns)
{

}

EuropeanOption::~EuropeanOption()
{
    //dtor
}



//**************************************************************Mathematical functions*************************************************************
unsigned long long int EuropeanOption::fact(int n)
{
    if(n<0)
    {
        return -1;
    }
    else
    {
        if(n==0)
        {
            return 1;
        }
        else

        {
            return n*fact(n-1);
        }
    }
}

//****************************** Black-Sholes methods*************************************************************************************

//probability density function of the normal centered reduced law
double EuropeanOption::f(double x)
{
    return exp(-(x*x)/2)/sqrt(2*M_PI);
}

//distribution function of the normal centered reduced law
double EuropeanOption::norm(const double& x) {
    double k = 1.0/(1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

    if (x >= 0.0) {
        return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
    } else {
        return 1.0 - norm(-x);
    }
}


double EuropeanOption::d1()
{
    return ((log(GetS()/GetK()) + (GetR()+(1/2)*pow(GetSigma(),2))*(GetT()))/(GetSigma()*sqrt(GetT())));
}


double EuropeanOption::d2()
{
    return (d1()-GetSigma()*sqrt(GetT()));
}

double EuropeanOption::Call()
{
    double res=0;
    double a=GetS()*norm(d1());
    double b=GetK()*exp(-GetR()*GetT())*norm(d2());
    res=a-b;
    return res;
}

double EuropeanOption::Put()
{

    return (GetK()*exp(-GetR()*GetT())*norm(-d2())-GetS()*norm(-d1()));
}




//************************************CRR methods*************************************************************

double EuropeanOption::Payoff(int i){
double Str=Stock(i,GetN());
double res=0;
if(GetPayoffType()=="Call")
{
    res=std::max(0.0,Str-GetK());
}
else
{
    res=std::max(0.0,GetK()-Str);
}
return res;
}


double EuropeanOption::Call_Crr(){
    std::vector<double> Si(GetN()+1); //we create a vector to contain option values of the different nodes
    for(int i=0;i<=GetN();i++)
    {
        Si[i]=std::max(0.0,GetS()*pow(u(),2*i-GetN())-GetK());   //enable us to access the option value at final step N

    }
    for(int j=GetN()-1;j>=0;j--)      //we go back from the N-1 step to the first step
    {
        for(int i=0;i<=j;i++)  // for each step j of the tree we calculate the price at each node i
        {
            Si[i]=(q()*Si[i+1]+(1-q())*Si[i])*(exp(-GetR()*(GetT()/GetN())));
        }
    }
    return Si[0]; //the value of the first node is the value of the option
}


double EuropeanOption::Put_Crr()
{
        std::vector<double> Si(GetN()+1);
    for(int i=0;i<=GetN();i++)
    {
        Si[i]=std::max(0.0,GetK()-GetS()*pow(u(),2*i-GetN()));

    }
    for(int j=GetN()-1;j>=0;j--)
    {
        for(int i=0;i<=j;i++)
        {
            Si[i]=(q()*Si[i+1]+(1-q())*Si[i])*(exp(-GetR()*(GetT()/GetN())));
        }
    }
    return Si[0];
}


//CRR closed-formula pricing method
double EuropeanOption::Crr_closed_formula_price(){
    double res=0;

     for(int i=0;i<=GetN();i++)
     {

       res+=((long double)fact(GetN())/((long double)fact(i)*(long double)fact(GetN()-i)))*pow(q(),i)*pow(1-q(),GetN()-i)*Payoff(i);
     }
     double res2=exp(-GetT()/GetN())*res;
     return res2;
}

//******************************* Monte Carlo Methods**********************************************************

//Box-Muller random number generator
double EuropeanOption:: random_path() {
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


double EuropeanOption::MonteCarlo_Call()
{
  double S_t=GetS()*exp(GetT()*(GetR()-0.5*GetSigma()*GetSigma()));
  double S_wiener=0;
  double payoff_sum=0;

  for (int i=0;i<GetNs();i++) {
    S_wiener=S_t*exp(sqrt(GetSigma()*GetSigma()*GetT())*random_path());
    payoff_sum+=std::max(S_wiener-GetK(),0.0);
  }

  return (payoff_sum/static_cast<double>(GetNs()))*exp(-GetR()*GetT());
}


double EuropeanOption::MonteCarlo_Put() {
  double S_t=GetS()*exp(GetT()*(GetR()-0.5*GetSigma()*GetSigma()));
  double S_wiener=0;
  double payoff_sum=0;

  for (int i=0;i<GetNs();i++) {
    S_wiener=S_t*exp(sqrt(GetSigma()*GetSigma()*GetT())*random_path());
    payoff_sum+=std::max(GetK()-S_wiener,0.0);
  }

  return (payoff_sum/static_cast<double>(GetNs()))*exp(-GetR()*GetT());
}



//*********************************Greeks for european calls and puts


// European call Delta
double EuropeanOption::delta_call() {
  return norm(d1());
}

// European call Gamma
double EuropeanOption::gamma_call() {
  return f(d1())/(GetS()*GetSigma()*sqrt(GetT()));
}

// European call Vega
double EuropeanOption::vega_call() {
  return GetS()*f(d1())*sqrt(GetT());
}

// European call Theta
double EuropeanOption::theta_call() {
  return -(GetS()*f(d1())*GetSigma())/(2*sqrt(GetT())) - GetR()*GetK()*exp(-GetR()*GetT())*norm(d2());
}

// European call Rho
double EuropeanOption::rho_call() {
  return GetK()*GetT()*exp(-GetR()*GetT())*norm(d2());
}

// European put Delta
double EuropeanOption::delta_put() {
  return delta_call() - 1;
}

// European  put Gamma
double EuropeanOption::gamma_put() {
  return gamma_call();
}

// European put Vega
double EuropeanOption::vega_put() {
  return vega_call();
}

// European put Theta
double EuropeanOption::theta_put() {
  return -(GetS()*f(d1())*GetSigma())/(2*sqrt(GetT())) + GetR()*GetK()*exp(-GetR()*GetT())*norm(-d2());
}

// European put Rho
double EuropeanOption::rho_put() {
  return -GetT()*GetK()*exp(-GetR()*GetT())*norm(-d2());
}









