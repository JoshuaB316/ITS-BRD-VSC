/**
  * @file calculate.h
  * @author MJ 
  * @date Oct 2025
  */

#ifndef CALCULATE_H
#define CALCULATE_H

/*
 ****************************************************************************************
 *  @brief      This function safely adds two integers and checks for overflow/underflow
 *
 *  @param      a        First integer
 *  @param      b        Second integer
 *  @param      result   Pointer to store the result
 *
 *  @return     int      0 if addition is safe, 1 if overflow/underflow occurs
 ****************************************************************************************/
int safe_add(int a, int b, int *result);

/*
 ****************************************************************************************
 *  @brief      This function adds the top values of the Stack
 *
 *  @return     void 
 ****************************************************************************************/
extern void add();

/*
 ****************************************************************************************
 *  @brief      This function safely subtracts two integers and checks for overflow/underflow
 *
 *  @param      a        First integer
 *  @param      b        Second integer
 *  @param      result   Pointer to store the result
 *
 *  @return     int      0 if subtraction is safe, 1 if overflow/underflow occurs
 ****************************************************************************************/
int safe_substract(int a, int b, int *result);

/*
 ****************************************************************************************
 *  @brief      This function subtracts the top values of the Stack
 *
 *  @return     void 
 ****************************************************************************************/
extern void subtract();

/*
 ****************************************************************************************
 *  @brief      This function safely multiplies two integers and checks for overflow/underflow
 *
 *  @param      a        First integer
 *  @param      b        Second integer
 *  @param      result   Pointer to store the result
 *
 *  @return     int      0 if multiplication is safe, 1 if overflow/underflow occurs
 ****************************************************************************************/
int safe_multiply(int a, int b, int *result);

/*
 ****************************************************************************************
 *  @brief      This function multiplies the top values of the Stack
 *
 *  @return     void 
 ****************************************************************************************/
extern void multiply();

/*
 ****************************************************************************************
 *  @brief      This function safely divides two integers and checks for division by zero and overflow/underflow
 *
 *  @param      a        First integer (dividend)
 *  @param      b        Second integer (divisor)
 *  @param      result   Pointer to store the result
 *
 *  @return     int      0 if division is safe, 1 if division by zero or overflow/underflow occurs
 ****************************************************************************************/
int safe_divide(int a, int b, int *result);

/*
 ****************************************************************************************
 *  @brief      This function divides the top values of the Stack
 *
 *  @return     void 
 ****************************************************************************************/
extern void divide();


#endif 