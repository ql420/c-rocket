#include "Matrix.hpp"
#include <vector>
#include <exception>
#include <iostream>
using namespace std;

Matrix::Matrix()
    :m_rowSize(0),m_colSize(0)
{
}



//default matrix
Matrix::Matrix(unsigned int p_rowSize,unsigned int p_colSize, double initial)
    :m_rowSize(p_rowSize),m_colSize(p_colSize)
{
    //check the matrix size
    if(m_rowSize == 0 || m_colSize == 0){
        throw length_error("The size of matrix can't be zero");
    }
    
    m_matrix.resize(m_rowSize);
    //resize the column vector one by one and put in the initial value
    for(unsigned int i = 0; i < m_matrix.size(); i++){
        m_matrix[i].resize(m_colSize,initial);
    }
    
}

//copy constructor
Matrix::Matrix(const Matrix& rhs){
    m_rowSize = rhs.m_rowSize;
    m_colSize = rhs.m_colSize;
    m_matrix = rhs.m_matrix;
}


//destructor
Matrix::~Matrix()
{
}

//initialise matrix after it is declared
void Matrix::ini(unsigned int p_rowSize,unsigned int p_colSize, double initial){
    m_rowSize=p_rowSize;
    m_colSize= p_colSize;
    //check the matrix size
    if(m_rowSize == 0 || m_colSize == 0){
        throw length_error("The size of matrix can't be zero");
    }
    m_matrix.resize(m_rowSize);
    //resize the column vector one by one and put in the initial value
    for(unsigned int i = 0; i < m_matrix.size(); i++){
        m_matrix[i].resize(m_colSize,initial);
    }
}

//add one more coloum to the matrix
void Matrix::addCol(double initial){
    for (unsigned int i = 0; i < m_rowSize; i++){
        m_matrix[i].push_back(initial);
    }
    m_colSize++;
}


Matrix Matrix::operator + (const Matrix& rhs){
    //initialise the result matrix
    //Note: different size matrix addition is not considered here because we know is same size matrix this case
    Matrix v_sum;
    v_sum.ini(m_rowSize,m_colSize,0.0);
    //add each elements one by one
    for(unsigned int i=0; i<m_rowSize; i++){
        for(unsigned int j=0; j<m_colSize; j++){
            //the value in matrix rhs can be found using () because we overload operator()
            v_sum(i,j) = m_matrix[i][j] + rhs(i,j);
        }
    }
    return v_sum;
}

Matrix Matrix::operator + (double p_s){
    //initialise matrix
    Matrix v_sum;
    v_sum.ini(m_rowSize,m_colSize,0.0);
    for(unsigned int i=0; i<m_rowSize; i++){
        for(unsigned int j=0; j<m_colSize; j++){
            //the value in matrix rhs can be found using () because we overload operator()
            v_sum(i,j) = m_matrix[i][j] + p_s;
        }
    }
    return v_sum;
}


Matrix Matrix::operator * (const Matrix& rhs){
    //first check does the dimension match
    if(m_colSize == rhs.getRows()){
        //initialise result matrix
        Matrix v_Mul;
        v_Mul.ini(m_rowSize , rhs.getCols(), 0.0);
        
        for(unsigned int i=0; i < m_rowSize;i++){
            for(unsigned int j=0; j < rhs.getCols() ;j++){
                //a temperory value 
                double temp = 0;
                for(unsigned int k=0; k < m_colSize ;k++){
                    temp += m_matrix[i][k] * rhs(k,j);
                }
                v_Mul(i,j) = temp;
            }
        }
        return v_Mul;
    }
    else{
        throw length_error("Matrix multiplication size doesn't match");
    }
}


Matrix Matrix::operator * (double p_s){
    //initialise result matrix
    Matrix v_Mul;
    v_Mul.ini(m_rowSize,m_colSize,0.0);
    for(unsigned int i =0; i < m_rowSize;i++){
        for(unsigned int j =0; j < m_colSize;j++){
            v_Mul(i,j) = m_matrix[i][j] * p_s;
        }
    }
    return v_Mul;
}

Matrix Matrix::operator / (double p_s){
    //initialise result matrix
    Matrix v_Div;
    v_Div.ini(m_rowSize,m_colSize,0.0);
    for(unsigned int i =0; i < m_rowSize;i++){
        for(unsigned int j =0; j < m_colSize;j++){
            v_Div(i,j) = m_matrix[i][j] / p_s;
        }
    }
    return v_Div;
}

double& Matrix::operator()(const unsigned int pRow, const unsigned int pCol){
    //first check pRow and pCol value
    if(pRow >= m_rowSize || pCol>= m_colSize){
        throw logic_error("The parameter out of matrix size");
    }
    
    return m_matrix[pRow][pCol];
}

double Matrix::operator()(const unsigned int pRow, const unsigned int pCol) const{
    //first check pRow and pCol value
    if(pRow >= m_rowSize || pCol>= m_colSize){
        throw logic_error("The parameter out of const matrix size");
    }
    
    return m_matrix[pRow][pCol];
}

double Matrix::getRows() const{
    return m_rowSize;
}


double Matrix::getCols() const{
    return m_colSize;
}


