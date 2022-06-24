#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

float evaluate(char operator, Item operand1, Item operand2) {
   switch (operator){
      case '^':
         return pow(operand1.fData, operand2.fData);
      case '/':
         return operand1.fData / operand2.fData;
      case '*':
         return operand1.fData * operand2.fData;
      case '+':
         return operand1.fData + operand2.fData;
      case '-':
         return operand1.fData - operand2.fData;
      case '%':
         return fmod(operand1.fData, operand2.fData);
   }
}

int isOperator(char operator){
   char operators[] = {'^', '/', '*', '+', '-', '%'};
   int i;
   for (i =0; i < 6; i++){
      if (operator == operators[i])
         return 1;
   }
   return 0;
}

int isOperand(char* operand){
   if (strlen(operand) == 0) {
      return 0;
   }
   if (strlen(operand) == 1 && operand[0] == '-') return 0;
   int foundDecimalPoint = 0;
   int i;
   for (i = 0; i < strlen(operand); i++){
      if (operand[i] == '.' && i > 0){ // cant start with decimal point
         if (operand[i-1] == '-'){  //cant start with decimal point right after the negative sign
            return 0;
         }
         if (foundDecimalPoint){ //can't have 2 decimal points
            return 0;
         }
         foundDecimalPoint = 1;
         continue;
      }

      if (operand[i] == '-' && i == 0){  //negative sign can only be at the very beginning
         continue;
      }

      if (isdigit(operand[i])){
         continue;
      }

      return 0;
   }
   return 1;
}

float operandToFloat(char* operand){
   if (!isOperand(operand)){
      printf("Error in operandToFloat: invalid operand!");
      exit(-1);
   }

   return atof(operand);
}
