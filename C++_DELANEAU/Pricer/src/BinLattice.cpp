#include "BinLattice.h"
#include "EuropeanOption.h"
#include "Option.h"
#include <iostream>
#include <vector>
#include<cmath>
#include <sstream>


BinLattice::BinLattice(double S,double K,double sigma, double T,double r, std::string payoffType,int N,int ns,std::vector<std::vector<double>> _lattice)
:Option(S,K,sigma,T,r,payoffType,N,ns),lattice(_lattice)
{}

BinLattice::~BinLattice()
{
    //dtor
}


void BinLattice::SetN()
{
    for(int i=0;i<=GetN();i++)
    {
        lattice.push_back(std::vector<double>(i+1));
    }
}



double BinLattice::GetNode(int i,int n)
{
    return Stock(i,n);
}




std::string BinLattice::espace(int n)
{
    int j=0;
    std::string s="";

        for(int h=0;h<=-n+GetN();h++)
        {s=s+"     ";}

    return s;
}




void BinLattice::Display()
{
    std::cout<<"----------"<<GetPayoffType()<<"----------------"<<std::endl;
    for(int n=0;n<=GetN();n++)
    {
        std::cout<<"n="<<n<<espace(n);
        for(int i=0;i<=n;i++)
        {
            lattice[n][i]=GetNode(i,n);
            std::cout<<round(lattice[n][i]*100)/100<<"    ";
        }
        std::cout<<std::endl;
        std::cout<<"  "<<espace(n)<<std::endl;

    }
}

