#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define debug printf("d\n")

double f1(double x)
{
    return log(x);
}

double f2(double x)
{
    return -2 * x + 14;
}

double f3(double x)
{
    return 1 / (2-x)  + 6;
}

double d_f1(double x)
{
    return 1 / x;
}

double d_f2(double x)
{
    return -2;
}

double d_f3(double x)
{
    return 1 / ((2-x)*(2-x));
}

double F(double (*f)(double), double (*g)(double), double x)
{
    return f(x) - g(x);
}

double root(double (*f)(double), double (*g)(double), double a, double b, double eps, double (*df)(double), double (*dg)(double))
{
    double c;
    double middle = (a + b) / 2;
    int lower = F(f, g, middle) < (F(f, g, a) +  F(f, g, b)) / 2;
    int monotone = F(f, g, a) < 0;
    if(lower == monotone)
    {
        c = b - F(f, g, b) / F(df, dg, b);
        while(F(f, g, c) * F(f, g, c - eps) > 0)
            c = c - F(f, g, c) / F(df, dg, c);
    }
    else
    {
        c = a - F(f, g, a) / F(df, dg, a);
        while(F(f, g, c) * F(f, g, c + eps) > 0)
            c = c - F(f, g, c) / F(df, dg, c);
    }

    return c;
}


double integral(double (*f)(double), double a, double b, double eps)
{
    double n = 10, I, I2, h;
    double p = 1.0/3;

    I = 0.5*f(a);
    h = (b-a) / n;
    for(int i = 1; i < n; i++)
        I += f(a + i*h);
    I += 0.5*f(b);
    I2 = I;
    do
    {
        I = I2;
        n*=2;
        h /= 2;
        for(int i = 1; i < n; i += 2)
            I2 += f(a + i*h);
    } while(p*fabs(2*h*I - h*I2) > eps);
    return h*I2;

}



int main(void)
{
    double eps1 = 0.0001;
    double eps2 = 0.0001;

    double f1_c_f2 = root(f1, f2, 6, 7, eps1, d_f1, d_f2); // c is cross
    double f1_c_f3 = root(f1, f3, 2.1, 3, eps1, d_f1, d_f3);
    double f2_c_f3 = root(f2, f3, 4, 5, eps1, d_f2, d_f3);

    double i1 = integral(f1, f1_c_f3, f1_c_f2, eps2);
    double i2 = integral(f2, f2_c_f3, f1_c_f2, eps2);
    double i3 = integral(f3, f1_c_f3, f2_c_f3, eps2);

    printf("%f\n%f %f %f\n", i2 + i3 - i1, f1_c_f2, f1_c_f3, f2_c_f3);
    return 0;
}
