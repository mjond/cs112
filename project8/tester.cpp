/* tester.cpp drives the testing of the Queue classes.
 * Joel Adams, for CS 112 at Calvin College.
 * written by: Mark Davis mjd85
 * Date: April 20, 2015
 */

#include "ArrayQueueTester.h"
#include "StackTester.h"
// #include "LinkedQueueTester.h"
 
 int main() {
 	ArrayQueueTester aqt;
 	aqt.runTests();
 	Stack<double> st(4);
// 	st.runTests();
// 	LinkedQueueTester lqt;
// 	lqt.runTests();
}
 
 
