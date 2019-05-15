#include <stdio.h>
#include <math.h>
#include <string.h>

extern double f1(double);
extern double f2(double);
extern double f3(double);
extern double d_f1(double);
extern double d_f2(double);
extern double d_f3(double);
int iterations = 1;


double zero(double x)
{
    return 0;
}

double t1(double x)
{
    return x*x*x*x - 16;
}
double dt1(double x)
{
    return 4*x*x*x;
}

double t2(double x)
{
    return sin(x);
}

double dt2(double x)
{
    return cos(x);
}
double F(double (*f)(double), double (*g)(double), double x)
{
    return f(x) - g(x);
}

double root(double (*f)(double), double (*g)(double), double a, double b, double eps, double (*df)(double), double (*dg)(double))
{
    int way = (F(f, g, (a + b) / 2) < (F(f, g, a) +  F(f, g, b)) / 2) == (F(f, g, a) < 0) ? -1 : 1;
    double c = (way == -1) ? (b - F(f, g, b) / F(df, dg, b)) : (a - F(f, g, a) / F(df, dg, a));
    while(F(f, g, c) * F(f, g, c + way * eps) > 0)
    {
        c = c - F(f, g, c) / F(df, dg, c);
        iterations++;
    }
    return c;
}

double integral(double (*f)(double), double a, double b, double eps)
{
    double n = 10, I = 0.5*f(a), I2;
    double h = (b-a) / n;

    for(int i = 1; i < n; i++)  I += f(a + i*h);
    I += 0.5*f(b);
    I2 = I;
    do
    {
        I = I2;
        n*=2;
        h /= 2;
        for(int i = 1; i < n; i += 2)  I2 += f(a + i*h);
    } while(1.0/3 *fabs(2*h*I - h*I2) > eps);
    return h*I2;
}

int main(int argc, char **argv)
{
    double eps1 = 0.001;
    double eps2 = 0.001;
    int iter1, iter2, iter3;
    iterations = 1;
    double f1_c_f2 = root(f1, f2, 6, 7, eps1, d_f1, d_f2); // c is cross
    iter1 = iterations;
    iterations = 1;
    double f1_c_f3 = root(f1, f3, 2.1, 3, eps1, d_f1, d_f3);
    iter2 = iterations;
    iterations = 1;
    double f2_c_f3 = root(f2, f3, 4, 5, eps1, d_f2, d_f3);
    iter3 = iterations;

    double i1 = integral(f1, f1_c_f3, f1_c_f2, eps2);
    double i2 = integral(f2, f2_c_f3, f1_c_f2, eps2);
    double i3 = integral(f3, f1_c_f3, f2_c_f3, eps2);
    printf("%f\n", i2 + i3 - i1);
    for(int i = 1; i <argc; i++)
    {
        if(strcmp(argv[i], "-s") == 0) printf("f1 == f2 => x == %f\nf1 == f3 => x == %f\nf3 == f2 => x == %f\n ", f1_c_f2, f1_c_f3, f2_c_f3);
        else if(strcmp(argv[i], "-i") == 0) printf("f1 == f2 -- %d\nf1 == f2 -- %d\nf1 == f2 -- %d\n", iter1, iter2, iter3);
        else if(strcmp(argv[i], "-t=t1") == 0)
        {
            printf("test: x^4 - 16 = 0 => x = %f\
                   \nintegral(f) = %f\
                   \nfrom 0.0 to 3.0\n", root(t1, zero, 0.0, 3.0, eps1, dt1, zero),
                        integral(t1, 0.0, 3.0, eps2));
        }
        else if(strcmp(argv[i], "-t=t2") == 0)
        {
            printf("test: sin(x) = 0 => x = %f\
                   \nintegral(f) = %f\
                   \nfrom 0.1 to 3.2\n", root(t2, zero, 0.1, 3.2, eps1, dt2, zero),
                        integral(t2, 0.1, 3.2, eps2));
        }
        else if(strcmp(argv[i], "-help") == 0) printf("-help - shows this list\n-s - square\n-i - iterations\n-t=t1/t2 - test functions\n", f1_c_f2, f1_c_f2, f2_c_f3);
        else printf("Wrong command name. Try -help for supported commands\n");
    }

    return 0;
}
