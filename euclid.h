//#pragma once
#ifndef EUCLID_H
#define EUCLID_H

int euclid_recursive(int a, int b);

int euclid(int a, int b);

int euclid_binary(int a, int b);

int euclid_extended(int a, int b, int *x, int *y);

int linear_diophantine(int *a, int *x, int n, int b);

int mul_inv(int a, int m);

int lcm(const int *a, int n);

int mod(long long int x, long long int m);

#endif