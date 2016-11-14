/* array.h declares "C style" array operations
 * Name:Mark Davis (mjd85)
 * Date:Feb 18/15
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */
 
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

using namespace std;

void initialize(double *a, int size);

void print(double *a, int size);

double average(double *a, int size);

double sum(double *a, int size);

void read(istream& in, double *a, int size);
