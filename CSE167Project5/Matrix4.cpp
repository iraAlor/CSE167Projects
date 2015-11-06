#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"

Matrix4::Matrix4()
{
    std::memset(m, 0, sizeof(m));
}

Matrix4::Matrix4(
                 float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33 )
{
    this->set(m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23,
              m30, m31, m32, m33);
}

void Matrix4::set(float m00, float m01, float m02, float m03,
                  float m10, float m11, float m12, float m13,
                  float m20, float m21, float m22, float m23,
                  float m30, float m31, float m32, float m33)
{
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}
void Matrix4::set(int col,int row,float val){
    m[col][row] = val;
}

float Matrix4::get(int column, int element)
{
    return m[column][element];
}

Matrix4& Matrix4::operator=(Matrix4 a)
{
    std::memcpy(m, a.m, sizeof(m));
    return *this;
}

float* Matrix4::ptr()
{
    return &m[0][0];
}

void Matrix4::identity()
{
    static const float ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    std::memcpy(m, ident, sizeof(m));
}

Matrix4 Matrix4::multiply(Matrix4 a)
{
    Matrix4 b;
    
    //Implement a more performant Matrix * Matrix multiplication
    
    //The current implementation below is not very efficient:
    //It allocates an additional 8 vectors on the stack and calls their constructors
    //It also calls off to additional functions (which create even more vectors!)
    //Which results in a lot of time being wasted on memory operations
    //This is bad, really bad, ultra bad D:
    
    //Hint: Loops!
    //Hint for the ambitious: SIMD!
    
    float r[4];
    for(int i = 0;i<4;i++){
        for(int k = 0;k<4;k++){
            r[k] = m[k][i];
        }
        for(int j = 0; j<4;j++){
            float val = 0.0;
            for(int l=0;l<4;l++){
                val+= r[l]*a.m[j][l];
            }
            b.m[j][i] = val;
        }
    }

    return b;
}

Matrix4 Matrix4::operator * (Matrix4 a)
{
    return multiply(a);
}

Vector4 Matrix4::multiply(Vector4 a)
{
    Vector4 b;
    for(int i =0;i<4;i++){
        float val = 0.0;
        for(int j = 0;j<4;j++){
            val  += a[j]*m[j][i];
        }
        b[i] = val;
    }
    
    return b;
}

Vector4 Matrix4::operator * (Vector4 a)
{
    return multiply(a);
}

Vector3 Matrix4::multiply(Vector3 a)
{
    Vector3 b;
    
    for(int i =0;i<3;i++){
        float val = 0.0;
        for(int j = 0;j<3;j++){
            val  += a[j]*m[j][i];
        }
        b[i] = val;
    }
    
    
    return b;
}

Vector3 Matrix4::operator * (Vector3 a)
{
    return multiply(a);
}

Matrix4 Matrix4::makeRotateX(float angle)
{
    identity();
    
    //Configure this matrix to be a rotation about the X-Axis by 'angle' radians
    m[1][1]= m[2][2] = cos(angle);
    m[1][2] = sin(angle);
    m[2][1] = -sin(angle);
    
    
    return *this;
}

Matrix4 Matrix4::makeRotateY(float angle)
{
    identity();
    
	m[0][0] = cos(angle);
	m[0][2] = -sin(angle);
	m[2][0] = sin(angle);
	m[2][2] = cos(angle);
    
    return *this;
}

Matrix4 Matrix4::makeRotateZ(float angle)
{
    identity();
    
    //Configure this matrix to be a rotation about the Z-Axis by 'angle' radians
    m[0][0] = m[1][1] = cos(angle);
    m[0][1] = sin(angle);
    m[1][0] = -sin(angle);
    
    return *this;
}

Matrix4 Matrix4::makeRotateArbitrary(Vector3 a, float angle)
{
  
    //Configure this matrix to be a rotation about the 'a' axis by 'angle' radians
    a = a.normalize();
    
    identity();
    
    
    float x = a[0];
    float y = a[1];
    float z = a[2];
    float x2 = x*x;
    float y2 = y*y;
    float z2 = z*z;
    float L = x2 + y2 + z2;
    
    
    m[0][0] = (x2 + (y2 + z2) * cos(angle)) / L;
    m[0][1] = (x * y * (1 - cos(angle)) + z * sqrt(L) * sin(angle)) / L;
    m[0][2] = (x * z * (1 - cos(angle)) - y * sqrt(L) * sin(angle)) / L;
    
    m[1][0] = (x * y * (1 - cos(angle)) - z * sqrt(L) * sin(angle)) / L;
    m[1][1] = (y2 + (x2 + z2) * cos(angle)) / L;
    m[1][2] = (y * z * (1 - cos(angle)) + x * sqrt(L) * sin(angle)) / L;
    
    m[2][0] = (x * z * (1 - cos(angle)) + y * sqrt(L) * sin(angle)) / L;
    m[2][1] = (y * z * (1 - cos(angle)) - x * sqrt(L) * sin(angle)) / L;
    m[2][2] = (z2 + (x2 + y2) * cos(angle)) / L;
    
    return *this;
    
    
}

Matrix4 Matrix4::makeScale(float s)
{
    return makeScale(s, s, s);
}

Matrix4 Matrix4::makeScale(float sx, float sy, float sz)
{
    identity();
    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = sz;
    //Configure this matrix to be a sclaing by sx, sy, sz

    return *this;
}

Matrix4 Matrix4::makeTranslate(float x, float y, float z)
{
    identity();
    
    //Configure this matrix to be a translation by vector 'a'
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
    
    return *this;
}

Matrix4 Matrix4::makeTranslate(Vector3 a)
{
    return makeTranslate(a[0], a[1], a[2]);
}

Matrix4 Matrix4::transpose(void)
{
    Matrix4 b;
    for(int x = 0; x < 4; ++x)
    {
        for(int y = 0; y < 4; ++y)
        {
            b.m[y][x] = m[x][y];
        }
    }
    return b;
}

//Hint: Try basing this on code by cool people on the internet
//In this class it is okay to use code from the internet
//So long as you fully understand the code and can clearly explain it if asked to
//http://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform
Matrix4 Matrix4::inverse(void)
{
    Matrix4 b;
    
    //Not required
    //Calculate the inverse of this matrix
    
    return b;
}

Matrix4 Matrix4::rigidInverse(void)
{
    Matrix4 b;
    
    //Project 2
    //Calculate the inverse of this matrix with the assumption that it is a rigid transformation
    //This will be useful when implementing cameras!
    Matrix4 tran;
    tran.makeTranslate(-m[3][0],-m[3][1],-m[3][2]);
   // tran.print("tran");
    //print("why");
    Matrix4 rot =  this->transpose();
    for(int i = 0;i<4;i++){
        rot.set(i,3,0);
        rot.set(3,i,0);
    }
    rot.set(3,3,1);
   // rot.print("rot");
    
    Matrix4 inv  = rot*tran;
  //  inv.print("");
    return inv;
}


Matrix4 Matrix4::makePerspectiveProjection(float fov, float width, float height, float near, float far)
{
    identity();
    
    //Project 3
    //Make this matrix a perspectice project matrix using fov, width, height, near and far
    //See the lecture slides for details
    
    return *this;
}

Matrix4 Matrix4::makeViewport(float xmin, float xmax, float ymin, float ymax)
{
    identity();
    
    //Project 3
    //Make this matrix a viewport matrix using xmin, xmax, ymin, and ymax
    //See the lecture slides for details
    
    return *this;
}
void Matrix4::printCol(int col){
    
    Vector3(m[col][0],m[col][1],m[col][2]).print("");
}
void Matrix4::print(std::string comment)
{
    //Width constants and variables
    static const int pointWidth = 1;
    static const int precisionWidth = 4;
    int integerWidth = 1;
    
    //Determine the necessary width to the left of the decimal point
    float* elementPtr = (float*)m;
    float maxValue = fabsf(*(elementPtr++));
    while(elementPtr++ < ((float*)m+16)) if(fabsf(*elementPtr) > maxValue) maxValue = fabsf(*elementPtr);
    while(maxValue >= 10.0) { ++integerWidth; maxValue /= 10.0; }
    
    //Sum up the widths to determine the cell width needed
    int cellWidth = integerWidth + pointWidth + precisionWidth;
    
    //Set the stream parameters for fixed number of digits after the decimal point
    //and a set number of precision digits
    std::cout << std::fixed;
    std::cout << std::setprecision(precisionWidth);
    
    //Print the comment
    std::cout << comment << std::endl;
    
    //Loop through the matrix elements, format each, and print them to screen
    float cellValue;
    for(int element = 0; element < 4; element++)
    {
        std::cout << std::setw(1) << (element == 0 ? "[" : " ");
        for(int vector = 0; vector < 4; vector++)
        {
            cellValue =  m[vector][element];
            std::cout << std::setw(cellWidth + (cellValue >= 0.0 ? 1 : 0)) << cellValue;
            std::cout << std::setw(0) << (vector < 3 ? " " : "");
        }
        std::cout << std::setw(1) << (element == 3 ? "]" : " ") << std::endl;
    }
}
