#ifndef MATH_HPP
#define MATH_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "Matrix.hpp"
using namespace std;

class Math
{
private:
    //initialise parameters
    //matrix which store environmental parameter
    //pho,g,CD,v0,h0
    Matrix m_EP;
    //Matrix which store rocket parameter in every coloumn
    //m0, mR, A, dmf, ue, dt
    Matrix m_RP;
    //rocket equation dx = M(x)x + B
    //initialise Matrix M(x)
    Matrix m_M;
    //initialise Matrix B
    Matrix m_B;
    //fuel consumed at this stage of rocket
    double m_fc;
    //s represent which stage the rocket is at
    unsigned int s;


public:
    //x = [h v m]'
    Matrix m_x;
    double m_t;
    
    
    Math();
    Math(const Math& rhs);
    ~Math();
    
    //initialise the class with initial conditions in the parameter file
    Math(string filename);
    
    //function that check rocket stage
    void CheckStage();
    
    //an equation computes the 4th Runge Kutta
    //the return value is the time
    double& RungeKutta4();
    
    
    //function that compute the value of dx, under different x and t 
    Matrix f(Matrix v_x,double v_t);
    
    

};

#endif // MATH_HPP
