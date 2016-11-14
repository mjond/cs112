/*
 * Vec.h
 *
 *  Created on: Mar 25, 2015
 *      Author: Mark Davis
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <cassert>
using namespace std;

typedef double Item;

class Vec {
public:
	Vec();
		Vec(unsigned size);
		Vec(const Vec& original);
		Vec& operator=(const Vec& original);
		Item getItem(unsigned index) const;
		void setSize(unsigned newSize);
		unsigned getSize() const;
		bool operator==(const Vec& v2);
		void writeTo(ostream& out) const;
		void readFrom(istream& in);
		void setItem(unsigned index, const Item& it);
		virtual ~Vec();
		Item& operator[](unsigned nIndex) const;
		Item& operator[](unsigned nIndex);
		bool operator!=(const Vec& v3);
		void readin(istream& in);
		Vec operator-(const Vec& v3);
		Vec operator+(const Vec& v3);
		Item operator*(const Vec& v3);
		void writeTo(const string& name);
		void readFrom(const string& name);
		void sort(Vec& Vec);
	private:
		unsigned mySize;
		Item* myArray;
		friend class VecTester;
};


#endif /* VEC_H_ */
