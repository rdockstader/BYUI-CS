// course.h

#ifndef COURSE_H
#define COURSE_H

#include "student.h"
#include <string>

class Course
{
private:
   std::string name;
   int size;
   Student* classList;

public:
   Course(int size);
   Course(const Course & other);
   ~Course();
   Course& operator=(Course const &  other);
   

   std::string getName() const { return name; }
   void setName(std::string name) { this->name = name; }
   
   int getSize() const { return size; }
   void setSize(int size) { this->size = size; }

   Student getStudent(int index) const;
   void setStudent(int index, const Student &);

   void displayList() const;
};




#endif
