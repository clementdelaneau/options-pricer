#include <vector>
#include <string>
#ifndef AMERICANOPTION_H
#define AMERICANOPTION_H
#include "Option.h"


class AmericanOption: public Option
{
    public:
        AmericanOption(double,double,double,double,double,std::string,int,int);
        virtual ~AmericanOption();
        std::string GetType();
        double u_Bs();
        double d_Bs();
        double q_Bs();
        double Stock(int,int);
        double Call();
        double Put();
        double Call_Bs();
        double Put_Bs();
        double PayoffType();

    protected:

    private:

};

#endif // AMERICANOPTION_H

