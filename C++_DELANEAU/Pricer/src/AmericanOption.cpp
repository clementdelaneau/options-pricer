#include "AmericanOption.h"
#include "Option.h"
#include <string>
#include <math.h>
#include <algorithm>  //for max function
#include <vector>

AmericanOption::AmericanOption(double S,double K,double sigma, double T,double r, std::string payoffType,int N,int ns):Option( S, K, sigma,  T, r, payoffType,N,ns)
{

}

AmericanOption::~AmericanOption()
{
    //dtor
}




//******************************************CRR display binomial tree************************************************************************


double AmericanOption::Call(){
    std::vector<double> Si(GetN()+1);
    for(int i=0;i<=GetN();i++)
    {
        Si[i]=std::max(0.0,GetS()*pow(u(),2*i-GetN())-GetK());

    }
    for(int j=GetN()-1;j>=0;j--)
    {
        for(int i=0;i<=j;i++)
        {
            Si[i]=(q()*Si[i+1]+(1-q())*Si[i])*(exp(-GetR()*(GetT()/GetN())));

                if(Si[i]<GetS()*pow(u(),2*i-j)-GetK())
                {
                    Si[i]=GetS()*pow(u(),2*i-j)-GetK();
                }

        }
    }
    return Si[0];
}

double AmericanOption::Put()
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


                if(Si[i]<GetK()-GetS()*pow(u(),2*i-j))
                {
                    Si[i]=GetK()-GetS()*pow(u(),2*i-j);
                }

        }
    }
    return Si[0];
}

//*********************************Last Pricing method: Binomial + Black-Sholes*****************************************************************

double AmericanOption::u_Bs()
{
    double u;
    u=exp((GetR()+(pow(GetSigma(),2))/2)*(GetT()/GetN())+GetSigma()*sqrt(GetT()/GetN()));
    return u;
}

double AmericanOption::d_Bs()
{
    double d;
    d=exp((GetR()+(pow(GetSigma(),2))/2)*(GetT()/GetN())-GetSigma()*sqrt(GetT()/GetN()));
    return d;
}

double AmericanOption::q_Bs()
{
    double risk_neutral;
    risk_neutral=(exp(GetR()*(GetT()/GetN()))-d_Bs())/(u_Bs()-d_Bs());
    return risk_neutral;
}

double AmericanOption::Call_Bs(){
    std::vector<double> Si(GetN()+1);
    for(int i=0;i<=GetN();i++)
    {
        Si[i]=std::max(0.0,GetS()*pow(u_Bs(),i)*pow(d_Bs(),GetN()-i)-GetK());

    }
    for(int j=GetN()-1;j>=0;j--)
    {
        for(int i=0;i<=j;i++)
        {
            Si[i]=(q_Bs()*Si[i+1]+(1-q_Bs())*Si[i])*(exp(-GetR()*(GetT()/GetN())));

                if(Si[i]<GetS()*pow(u_Bs(),i)*pow(d_Bs(),j-i)-GetK())
                {
                    Si[i]=GetS()*pow(u_Bs(),i)*pow(d_Bs(),j-i)-GetK();
                }
        }
    }
    return Si[0];
}

double AmericanOption::Put_Bs()
{
        std::vector<double> Si(GetN()+1);
    for(int i=0;i<=GetN();i++)
    {
        Si[i]=std::max(0.0,GetK()-GetS()*pow(u_Bs(),i)*pow(d_Bs(),GetN()-i));

    }
    for(int j=GetN()-1;j>=0;j--)
    {
        for(int i=0;i<=j;i++)
        {
            Si[i]=(q_Bs()*Si[i+1]+(1-q_Bs())*Si[i])*(exp(-GetR()*(GetT()/GetN())));

                if(Si[i]<GetK()-GetS()*pow(u_Bs(),i)*pow(d_Bs(),j-i))
                {
                    Si[i]=GetK()-GetS()*pow(u_Bs(),i)*pow(d_Bs(),j-i);
                }
        }
    }
    return Si[0];
}

