#include <iostream>
#include <iomanip>
#include <fstream>
#include <exception>
#include <vector>
#include <string>
#include <cmath>
#include "Matrix.hpp"
#include "Math.hpp"
using namespace std;


int main()
{
	try{
        
        //input the parameter file to the Math class
        //the rocket paramter file should be written in sequence from first stage to final stage
        Math rocket("parameters.txt");
    
        //create output file
        ofstream vOut("output.txt",ios::out | ios::trunc);
        vOut.precision(5);
    
        //initial condition
        double h = rocket.m_x(0,0);
        double v = rocket.m_x(1,0);
        double m = rocket.m_x(2,0);
        double t = 0;
        vOut << t << " "<< h << " " << v << " " << m << endl;
        
        while(h >= 0){
            rocket.CheckStage();
            t = rocket.RungeKutta4();
            h = rocket.m_x(0,0);
            v = rocket.m_x(1,0);
            m = rocket.m_x(2,0);
            
            if( h >=0 ){
                //output data to the file
               vOut << t << " "<< h << " " << v << " " << m << endl;
                
            }
            else{
               break;//check whether h < 0 before output it to the file
            }
        }
        vOut.close();
	    return 0;
    }
    catch (const length_error& e){
        cout << "An error occured: " << e.what()<< endl;
        return 1;
    }
    catch (const logic_error& e){
        cout << "An error occured: " << e.what()<< endl;
        return 2;
    }
    catch(int Num){
        cout << "Error: " << Num << " File failed to open" << endl;
        return 3;
    }
}
