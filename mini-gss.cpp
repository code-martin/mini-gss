#include <cmath>
#include <iostream>

double golden_section(double (*f)(double), double a, double b, int max_iter = 16, double tol = 0.00001) 
{
    const double phi = 1/((1+sqrt(5))/2);

    double m[4] = { a, b, b-(b-a)*phi, a+(b-a)*phi };
    double r[2] = { f(m[2]), f(m[3]) };

    for(int i=0;i<max_iter && fabs(r[0]-r[1]) > tol;i++) 
    {
        int P = (r[0] < r[1]);
        
        m[P] = m[2+P]; 
        m[2+P] = m[3-P];
        m[3-P] = m[P] - (m[P]-m[1-P])*phi;

        r[P] = r[1-P];
        r[1-P] = f(m[3-P]);

        printf("I:%3d [%+.2f,%+.2f=>%+.6f]\n",i, m[0],m[1], f((m[0]+m[1])/2));
    }
    return (m[0] + m[1]) / 2;
}

double f(double x) { return (x+2) * (x+2); }

int main() 
{
    double min = golden_section(f, -4, 4);
    std::cout << "Minimum in [-4, 4]: " << min << std::endl;
}
