#ifndef BINLATTICE_H
#define BINLATTICE_H
#include <vector>
#include "EuropeanOption.h"

class BinLattice: public Option
{
    public:
        BinLattice(double,double,double,double,double,std::string,int,int,std::vector<std::vector<double>>);
        virtual ~BinLattice();
        void SetN();
        void SetNode(int,int);
        double GetNode(int,int);
        void Display();
        std::string espace(int);



    private:

        std::vector<std::vector<double>> lattice;

};

#endif // BINLATTICE_H
