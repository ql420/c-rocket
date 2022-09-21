#include "Math.hpp"
#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <cmath>
using namespace std;

Math::Math()
:m_t(0.0),m_fc(0.0),s(0)
{
}

Math::Math(const Math& rhs){
    m_x = rhs.m_x;
    m_t = rhs.m_t;
    m_fc = rhs.m_fc;
    s = rhs.s;
    m_M = rhs.m_M;
    m_B = rhs.m_B;
    m_EP = rhs.m_EP;
    m_RP = rhs.m_RP;
}

Math::Math(string filename)
:m_t(0.0),m_fc(0.0),s(0)
{
    ifstream vMyFile(filename);
    string vTemp;
    string vTemp1;
    //initialise temperary input variable for a line of rocket parameter
    string vLine;
    //initialise temperary input variable for a single value
    string vIn;
    string vLine1;
    string vIn1;
    if(vMyFile.good()){
        //get the first line which is environmental parameter
        getline(vMyFile,vLine);
        stringstream vTemp(vLine);
        //initialise the matrix with size 5,1
        m_EP.ini(5,1,0.0);
        for (unsigned int i=0; i<m_EP.getRows() ; i++){
            //extract space seperated values
            getline(vTemp,vIn,' ');
            m_EP(i,0) = stod(vIn);
        }
        
        //initialise rocket parameter matrix with size 6*1
        //each column store the data for each rocket stage
        m_RP.ini(6,1,0.0);
        //first rocket stage
        getline(vMyFile,vLine1);
        stringstream vTemp1(vLine1);
        for (unsigned int j=0; j<m_RP.getRows() ; j++){
            getline(vTemp1,vIn1,' ');
            m_RP(j,0) = stod(vIn1);
        }
        //more rocket stages
        unsigned int i=1;
        while(getline(vMyFile,vLine1)){
            m_RP.addCol(0.0);
            stringstream vTemp1(vLine1);
            for (unsigned int j=0; j<m_RP.getRows() ; j++){
                getline(vTemp1,vIn1,' ');
                m_RP(j,i) = stod(vIn1);
            }
            i++;
        }
        vMyFile.close();
    }
    else{
        throw(404);
    }
    
    //initialise matrices
    m_M.ini(3,3,0.0);
    m_B.ini(3,1,0.0);
    m_x.ini(3,1,0.0);
    
    
    //initialise value of x with initial condition
    m_x(0,0) = m_EP(4,0);
    m_x(1,0) = m_EP(3,0);
    
    //total mass
    double m_mt=0;
    for (unsigned int i = 0; i < m_RP.getCols();i++){
        m_mt += m_RP(0,i);
    }
    m_x(2,0) = m_mt;
    
    //assigning value to B
    m_B(1,0) = -m_EP(1,0);
    m_B(2,0) = -m_RP(3,0);
    
    
    //assigning value to M, except M(2,2) which will be done in f 
    m_M(0,1) = 1;
    
    
}

void Math::CheckStage(){
    //compare fuel consumed to fuel mass of the stage
    //m_RP(0,s)-m_RP(1,s) is m0-mR
    if (m_fc >= m_RP(0,s)-m_RP(1,s)){
        //check is s the last stage, need to -1 because s start from 0
        if (s < m_RP.getCols()-1){
            //delete the rocket mass of the stage depleted
            m_x(2,0) = m_x(2,0) - m_RP(1,s);
            //refresh stage number
            s++;
        }
        //s is the last stage
        else if(s == m_RP.getCols()-1){
            //change dmf to 0
            m_RP(3,s) = 0.0;
            //change ue to 0
            m_RP(4,s)=0.0;
        }
        else{
            throw logic_error("s value can't be more than the number of stages");
        }
        //set fuel consumed back to 0
        m_fc = 0;
        //refresh B matrix with new dmf value
        m_B(2,0) = -m_RP(3,s);
    }
}


double& Math::RungeKutta4(){
    Matrix k1(3,1,0.0);
    Matrix k2(3,1,0.0);
    Matrix k3(3,1,0.0);
    Matrix k4(3,1,0.0);
    
    //m_RP(5,s) is dt
    k1 = f(m_x,m_t)*m_RP(5,s);
    k2 = f(m_x+k1*0.5,m_t+0.5*m_RP(5,s))*m_RP(5,s);
    k3 = f(m_x+k2*0.5,m_t+0.5*m_RP(5,s))*m_RP(5,s);
    k4 = f(m_x+k3,m_t+m_RP(5,s))*m_RP(5,s);
    
    //refresh x matrix
    m_x = m_x+ k1/6.0 + (k2+k3)/3.0 + k4/6.0;
    //refresh fuel consumed
    m_fc += m_RP(3,s)*m_RP(5,s);
    //refresh time 
    m_t += m_RP(5,s);
    return m_t;
}


//f = M(x)x + B
Matrix Math::f(Matrix v_x,double v_t){
    //assign new value to M(1,1) which is the only one change with x
    //M(1,1) = -0.5 *pho *abs(v)*CD*A/m + dmf*ue/(abs(v_x(1,0))*v_x(2,0));
    m_M(1,1) = -0.5*m_EP(0,0)*abs(v_x(1,0))*m_EP(2,0)*m_RP(2,s)/v_x(2,0) + m_RP(3,s)*m_RP(4,s)/(abs(v_x(1,0))*v_x(2,0));
    return m_M * v_x + m_B;
}




Math::~Math()
{
}

