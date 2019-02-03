#ifndef DIGITALOPTION_H
#define DIGITALOPTION_H
#include "Option.h"

class DigitalOption: public Option
{
    public:
        DigitalOption(double,double,double,double,double,std::string,int,int);
        virtual ~DigitalOption();
        double Call_dig();
        double Put_dig();

    protected:

    private:

};

#endif // DIGITALOPTION_H
