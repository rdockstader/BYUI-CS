//
//  wholeNumber.h
//  week07
//
//  Created by Chris Carrick on 6/4/18.
//  Copyright © 2018 Chris Carrick. All rights reserved.
//

#ifndef wholeNumber_h
#define wholeNumber_h
#include <iostream>
#include <iomanip>
#include "list.h"
//#include <list>  // for testing
#include <stack>
#include <vector>
#include <cassert>
#include <sstream>
#include <cstdlib>

namespace custom
{
/******************************************************************************
* WHOLENUMBER()
******************************************************************************/
class WholeNumber
{
   public:
      WholeNumber () { digits.push_back(0); };
      WholeNumber (unsigned int num);
      WholeNumber (const WholeNumber & rhs) throw (const char *);
   
      void display();
      int  size   () { return static_cast<int> (digits.size()); };
      WholeNumber & operator () (unsigned int num);
      WholeNumber & operator += (WholeNumber rhs) throw (const char *); // Done
      WholeNumber & operator -  (WholeNumber rhs) throw (const char *); // Done
      WholeNumber & operator *  (WholeNumber rhs) throw (const char *); // Done
      WholeNumber & operator =  (WholeNumber & rhs) throw (const char *); // Done
   
      // Insertion/Extraction Operator
      friend std::ostream & operator << (std::ostream & out, WholeNumber & t); // Done
      friend std::istream & operator >> (std::istream & in,  WholeNumber & t); // Done
   
   private:
      custom::list<int> digits;
};


};

#endif /* wholeNumber_h */
