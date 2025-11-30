/**
  * @file errorhaendler.h
  * @author MJ 
  * @date Oct 2025
  */

#ifndef ERRORHAENDLER_H
#define ERRORHAENDLER_H

#define StackOverflow -1
#define StackUnderflow -2
#define IntOverflow -3
#define IntUnderflow -4
#define DivideByZero -5
#define UnexpectedToken -6
#define UnknownToken -7
#define EmptyStack -8
#define NotEnoughElements -9

/**
 * @brief displays errormessage based on the error
 * 
 * @param errNum predefined integer values
 * @return void
 */
void displayError(int errNum)

#endif