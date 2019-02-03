#ifndef OPTION_H
#define OPTION_H
#include <string>

class Option
{
    public:
        Option(double,double,double,double,double,std::string,int,int);
        virtual ~Option();
        std::string GetPayoffType();
        int GetN();
        double GetS();
        double GetK();
        double GetSigma();
        double GetT();
        double GetR();
        int GetNs();
        void SetN(int);
    double d1();
    double d2();
    double u();
    double d();
    double q();
        double Stock(int,int);
        double PayoffType();
        //virtual double Payoff(int)=0;   //permet de mettre la classe Option en classe abstraite


    private:
        double S;
        double K;
        double sigma;
        double T;
        double r;
        std::string payoffType;
        int N;
        int ns;
};

#endif // OPTION_H
