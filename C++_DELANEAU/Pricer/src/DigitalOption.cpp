#include "DigitalOption.h"
#include "Option.h"
#include <algorithm>  //for max function
#include <string>
#include <cmath>
#include <vector>

DigitalOption::DigitalOption(double S,double K,double sigma,double T,double r,std::string payoffType,int N,int ns)
:Option(S,K,sigma,T,r,payoffType,N,ns)
{}

DigitalOption::~DigitalOption()
{
    //dtor
}





double DigitalOption::Call_dig(){
    std::vector<double> Si(GetN()+1);
    for(int i=0;i<=GetN();i++)
    {
        Si[i]=std::max(0.0,GetS()*pow(u(),2*i-GetN())-GetK());
        if(Si[i]>0)
        {
            Si[i]=1;
        }
        else
        {
            Si[i]=0;
        }

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


double DigitalOption::Put_dig()
{
        std::vector<double> Si(GetN()+1);
    for(int i=0;i<=GetN();i++)
    {
        Si[i]=std::max(0.0,GetK()-GetS()*pow(u(),2*i-GetN()));
                if(Si[i]>0)
        {
            Si[i]=1;
        }
        else
        {
            Si[i]=0;
        }

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
