#include <iostream>
#include <string>
#include <vector>
#include "Option.h"
#include "EuropeanOption.h"
#include "BinLattice.h"
#include "AmericanOption.h"
#include "DigitalOption.h"
#include "AsianOption.h"


using namespace std;

int main()
{
    //initialization of parameters
    double r=0.05;
    double sigma=0.25;
    double K=100;
    double T=2;
    double S=102;
    int N=100;
    int N2=20; //N parameter for the CRR closed-Formula
    int N3=10; //N parameter for the display of the binomial tree
    int ns=100000; //Number of simulated path for Monte Carlo method
    vector<vector<double>> lattice;


//European Option
EuropeanOption e1(S, K, sigma,  T, r, "Call",N,ns);
EuropeanOption e2(S, K, sigma,  T, r, "Put",N,ns);

//BinLattice for American and European Options
BinLattice b1(S, K, sigma,  T, r, "Call",N3,ns,lattice);
BinLattice b2(S, K, sigma,  T, r, "Put",N3,ns,lattice);


// Digital Option
DigitalOption dig1(S, K, sigma,  T, r, "Call",N,ns);
DigitalOption dig2(S, K, sigma,  T, r, "Put",N,ns);

//American Option
AmericanOption am1(S, K, sigma,  T, r, "Call",N,ns);
AmericanOption am2(S, K, sigma,  T, r, "Put",N,ns);


//Asian Option
AsianOption as1(S, K, sigma,  T, r, "Call",N,ns);
AsianOption as2(S, K, sigma,  T, r, "Put",N,ns);


    int choice=0;

bool ok="True";
while(ok="True")
{
cout<<endl<<endl;
cout<<"1. European Option"<<endl;
cout<<"2. Digital Option"<<endl;
cout<<"3. American Option"<<endl;
cout<<"4. Asian Option"<<endl;
cout<<"5. Exit"<<endl;
cout<<"Choose a valid number please: ";
cin>>choice;
cout<<endl;

switch(choice){

case 1:


cout<<"---------------------Parameters----------------------------"<<endl;
cout<<"S= "<<S<<endl;
cout<<"K= "<<K<<endl;
cout<<"sigma= "<<sigma<<endl;
cout<<"T= "<<T<<endl;
cout<<"r= "<<r<<endl;
cout<<"N= "<<N<<endl;
cout<<"ns= "<<ns<<endl;






//Black-Sholes (TD5 exercise 1)

cout<<"------------------------Black-Sholes----------------------------------------------------------------------"<<endl<<endl;


cout<<"Call: "<<e1.Call()<<endl;
cout<<"Delta: "<<e1.delta_call()<<endl;
cout<<"Gamma: "<<e1.gamma_call()<<endl;
cout<<"Theta: "<<e1.theta_call()<<endl;
cout<<"Vega: "<<e1.vega_call()<<endl;
cout<<"Rho: "<<e1.rho_call()<<endl<<endl;

cout<<"Put: "<<e1.Put()<<endl;
cout<<"Delta: "<<e1.delta_put()<<endl;
cout<<"Gamma: "<<e1.gamma_put()<<endl;
cout<<"Theta: "<<e1.theta_put()<<endl;
cout<<"Vega: "<<e1.vega_put()<<endl;
cout<<"Rho: "<<e1.rho_put()<<endl<<endl;

//Crr (TD5 exercise 2)

cout<<"------------------------CRR----------------------------------------------------------------------------------"<<endl<<endl;
cout<<"Call: "<<e1.Call_Crr()<<endl;
cout<<"Put: "<<e2.Put_Crr()<<endl<<endl;


//Crr (TD6 exercise 1)
cout<<"------------------------CRR Closed-Formula--------------------------------------------------------------------"<<endl<<endl;
e1.SetN(N2);
e2.SetN(N2);
cout<<"Call: "<<e1.Crr_closed_formula_price()<<endl;
cout<<"Put: "<<e2.Crr_closed_formula_price()<<endl<<endl;

// Crr binomial tree display (TD6 exercise 3)
cout<<"------------------------Crr binomial tree Display--------------------------------------------------------------------"<<endl<<endl;
e1.SetN(N3);
e2.SetN(N3);

b1.SetN();
b1.Display();
cout<<"Call: "<<e1.Call_Crr()<<endl<<endl<<endl;

b2.SetN();
b2.Display();
cout<<"Put: "<<e2.Put_Crr()<<endl<<endl<<endl;

//TD7 exercise 1
cout<<"----------------Monte Carlo---------------------------------------------------------------------------------------------"<<endl;
e1.SetN(N);
e2.SetN(N);
cout << "Call : " << e1.MonteCarlo_Call() <<endl;
cout << "Put :   " << e2.MonteCarlo_Put() << endl<<endl;


break;

//Digital Option (TD6 exercise 2)
case 2:

        //Digital option
    cout<<"Digital Option :"<<endl;
    cout<<"Call: "<<dig1.Call_dig()<<endl;
    cout<<"Put: "<<dig2.Put_dig()<<endl<<endl;


break;


// American Option
case 3:


cout<<"---------------------Parameters----------------------------"<<endl;
cout<<"S= "<<S<<endl;
cout<<"K= "<<K<<endl;
cout<<"sigma= "<<sigma<<endl;
cout<<"T= "<<T<<endl;
cout<<"r= "<<r<<endl;
cout<<"N= "<<N<<endl<<endl;



//CRR
cout<<"------------------------------------CRR------------------------------------------------"<<endl;
cout<<"Call: "<<am1.Call()<<endl;
cout<<"Put: "<<am2.Put()<<endl<<endl;

//TD 8 exercise 1
cout<<"-----------------------------------Binomial Tree Display for American call and put -------------------"<<endl;
//American call and Put with display of the binomial tree
am1.SetN(N3);
am2.SetN(N3);
b1.SetN();
b1.Display();
cout<<"Call: "<<am1.Call()<<endl;

b2.SetN();
b2.Display();
cout<<"Put: "<<am2.Put()<<endl<<endl;

//TD 8 exercise 2
cout<<"--------------------American Call and Put with CRR+Black-Sholes--------------------------------------"<<endl;
am1.SetN(N);
am2.SetN(N);
cout<<"Call: "<<am1.Call_Bs()<<endl;
cout<<"Put: "<<am2.Put_Bs()<<endl<<endl;


break;

//Asian Option
//TD 7 exercise 2
case 4:
cout<<"--------------------Monte Carlo for Arithmetic Asian Option--------------------------------------"<<endl;
cout<<"Call: "<<as1.MonteCarlo_Call()<<endl;
cout<<"Put: "<<as2.MonteCarlo_Put()<<endl<<endl;
break;

case 5:

    exit(0);

break;

default:

    cout<<"incorrect entry";
    cout<<endl;

break;

}
}
    return 0;
}
