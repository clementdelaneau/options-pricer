#ifndef ASIANOPTION_H
#define ASIANOPTION_H
#include "Option.h"


class AsianOption: public Option
{
    public:
        AsianOption(double,double,double,double,double,std::string,int,int);
        virtual ~AsianOption();
        double random_path();
        double AsianPayoffCall(double);
        double AsianPayoffPut(double);
        double MonteCarlo_Call();
        double MonteCarlo_Put();

    protected:

    private:
};

#endif // ASIANOPTION_H
