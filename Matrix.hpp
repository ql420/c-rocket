#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
using namespace std;

class Matrix
{
private:
    unsigned int m_rowSize;
    unsigned int m_colSize;
    //matrix is a vector inside a vector
    vector< vector<double> > m_matrix;
    
public:
    Matrix();//default constructor
    Matrix(const Matrix& rhs);//copy constructor
    Matrix(unsigned int p_rowSize,unsigned int p_colSize, double initial);//default constructor
    ~Matrix();//destructor
    
    //initialise matrix
    void ini(unsigned int p_rowSize,unsigned int p_colSize, double initial);
    //increase column size of matrix by one
    void addCol(double initial);
    
    //Matrix operation
    //for this case only + , * and /  is needed
    Matrix operator + (const Matrix& rhs);
    //scalar addition
    Matrix operator + (double p_s);
    Matrix operator * (const Matrix& rhs);
    //scalar mutiplication needed
    Matrix operator * (double p_s);
    //scalar division needed
    Matrix operator / (double p_s);
    
    //Simplify the programme
    //used to fill value in matrix
    double& operator()(const unsigned int pRow, const unsigned int pCol);
    //used to get value
    double operator()(const unsigned int pRow, const unsigned int pCol) const;
    
    
    //get row and coloum size
    double getRows() const;
    double getCols() const;
    
    

};

#endif // MATRIX_HPP
