#ifndef EUROPEANOPTION_H
#define EUROPEANOPTION_H
#include "Option.h"
#include <string>
class EuropeanOption: public Option
{
    public:
        EuropeanOption(double,double,double,double,double,std::string,int,int);
        EuropeanOption();
        virtual ~EuropeanOption();



    unsigned long long int fact(int);

    double norm(const double&);
    double f(double);
    double d1();
    double d2();
    double random_path();
    double MonteCarlo_Call();
    double MonteCarlo_Put();
    double Payoff(int);
    double Call();
    double Put();
    double Call_Crr();
    double Put_Crr();
    double Crr_closed_formula_price();

    double delta_call();
    double gamma_call();
    double theta_call();
    double rho_call();
    double vega_call();
    double delta_put();
    double gamma_put();
    double theta_put();
    double rho_put();
    double vega_put();


    private:

};

#endif // EUROPEANOPTION_H
