#ifndef CALCULATING2_HEADER_H_INCLUDED
#define CALCULATING2_HEADER_H_INCLUDED

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <limits.h>
using namespace std;

char* Read();
//int Postfixx(char* s, char *&st, int &n);
int Postfix(char* s, char *&st, int &n);
double Chislo(char* s);
double Schet(double x, double y, char c);
double Computing(char* s, int n);

#endif // CALCULATING2_HEADER_H_INCLUDED
