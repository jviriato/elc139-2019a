#include <algorithm>
#include <iostream>
#include <string>
#include <omp.h>
#include <stdlib.h>

//Uso: Schedule::STATIC
namespace Schedule
{
enum
{
   STATIC,
   DYNAMIC,
   GUIDED,
   RUNTIME,
   AUTO
};
}

class SharedArray
{
 private:
   char *array;
   int index;
   int size;

 public:
   SharedArray(int n) : size(n), index(0)
   {
      array = new char[size];
      std::fill(array, array + size, '-');
   }
   void addChar(char c)
   {
#pragma omp critical
      {
         array[index] = c;
         spendSomeTime();
         index++;
      }
   }
   void addCharSemCritical(char c)
   {
      array[index] = c;
      spendSomeTime();
      index++;
   }
   int countOccurrences(char c)
   {
      return std::count(array, array + size, c);
   }
   std::string toString()
   {
      return std::string(array, size);
   }

 private:
   void spendSomeTime()
   {
      for (int i = 0; i < 10000; i++)
      {
         for (int j = 0; j < 100; j++)
         {
            // These loops shouldn't be removed by the compiler
         }
      }
   }
};

class ArrayFiller
{
 private:
   static const int nThreads = 4;
   static const int nTimes = 20;
   SharedArray *array;

 public:
   ArrayFiller()
   {
      array = new SharedArray(nTimes);
   }
   void fillArrayWithStuff(int schedule_case, int chunk, bool mutex)
   {
      switch (schedule_case)
      {
      case Schedule::STATIC:
         if (!chunk)
         {
            std::cout << "Caso 1: Static schedule sem chunks" << std::endl;
            if (mutex)
#pragma omp parallel for schedule(static) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addChar('A' + omp_get_thread_num());
               }
            else
#pragma omp parallel for schedule(static) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addCharSemCritical('A' + omp_get_thread_num());
               }
         }
         else
         {
            std::cout << "Caso 2: Static schedule com chunks" << std::endl;
            if (mutex)
#pragma omp parallel for schedule(static, chunk) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addChar('A' + omp_get_thread_num());
               }
            else
#pragma omp parallel for schedule(static, chunk) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addCharSemCritical('A' + omp_get_thread_num());
               }
         }
         break;
      case Schedule::DYNAMIC:
         if (!chunk)
         {
            std::cout << "Caso 3: Dynamic schedule sem chunks" << std::endl;
            if (mutex)
#pragma omp parallel for schedule(dynamic) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addChar('A' + omp_get_thread_num());
               }
            else
#pragma omp parallel for schedule(dynamic) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addCharSemCritical('A' + omp_get_thread_num());
               }
         }
         else
         {
            std::cout << "Caso 4: Dynamic schedule com chunks" << std::endl;
            if (mutex)
#pragma omp parallel for schedule(dynamic, chunk) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addChar('A' + omp_get_thread_num());
               }
            else
#pragma omp parallel for schedule(dynamic, chunk) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addCharSemCritical('A' + omp_get_thread_num());
               }
         }

         break;
      case Schedule::GUIDED:
         if (!chunk)
         {
            std::cout << "Caso 5: Guided schedule sem chunks" << std::endl;
            if (mutex)
#pragma omp parallel for schedule(guided) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addChar('A' + omp_get_thread_num());
               }
            else
#pragma omp parallel for schedule(guided) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addCharSemCritical('A' + omp_get_thread_num());
               }
         }
         else
         {
            std::cout << "Caso 6: Guided schedule com chunks" << std::endl;
            if (mutex)
#pragma omp parallel for schedule(guided, chunk) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addChar('A' + omp_get_thread_num());
               }
            else
#pragma omp parallel for schedule(guided, chunk) num_threads(nThreads)
               for (int i = 0; i < nTimes; ++i)
               {
                  array->addCharSemCritical('A' + omp_get_thread_num());
               }
         }
         break;
      case Schedule::RUNTIME:
         std::cout << "Caso 7: Runtime schedule" << std::endl;
         if (mutex)
#pragma omp parallel for schedule(runtime) num_threads(nThreads)
            for (int i = 0; i < nTimes; ++i)
            {
               array->addChar('A' + omp_get_thread_num());
            }
         else
#pragma omp parallel for schedule(runtime) num_threads(nThreads)
            for (int i = 0; i < nTimes; ++i)
            {
               array->addCharSemCritical('A' + omp_get_thread_num());
            }
         break;
      case Schedule::AUTO:
         std::cout << "Caso 8: Auto schedule" << std::endl;
         if (mutex)
#pragma omp parallel for schedule(auto) num_threads(nThreads)
            for (int i = 0; i < nTimes; ++i)
            {
               array->addChar('A' + omp_get_thread_num());
            }
         else
#pragma omp parallel for schedule(auto) num_threads(nThreads)
            for (int i = 0; i < nTimes; ++i)
            {
               array->addCharSemCritical('A' + omp_get_thread_num());
            }
         break;
      default:
         break;
      }
   }
   void printStats()
   {
      std::cout << array->toString() << std::endl;
      for (int i = 0; i < nThreads; ++i)
         std::cout << (char)('A' + i) << "="
                   << array->countOccurrences('A' + i) << " ";
      std::cout << std::endl;
   }
};

int main()
{
   bool uses_mutex = true;
   std::cout << "Aplicações com mutex: " << std::endl
             << std::endl;
   ArrayFiller m1;
   m1.fillArrayWithStuff(Schedule::STATIC, 0, uses_mutex);
   m1.printStats();
   ArrayFiller m2;
   m2.fillArrayWithStuff(Schedule::STATIC, 5, uses_mutex);
   m2.printStats();
   ArrayFiller m3;
   m3.fillArrayWithStuff(Schedule::DYNAMIC, 0, uses_mutex);
   m3.printStats();
   ArrayFiller m4;
   m4.fillArrayWithStuff(Schedule::DYNAMIC, 5, uses_mutex);
   m4.printStats();
   ArrayFiller m5;
   m5.fillArrayWithStuff(Schedule::GUIDED, 0, uses_mutex);
   m5.printStats();
   ArrayFiller m6;
   m6.fillArrayWithStuff(Schedule::GUIDED, 5, uses_mutex);
   m6.printStats();
   ArrayFiller m7;
   m7.fillArrayWithStuff(Schedule::RUNTIME, 0, uses_mutex);
   m7.printStats();
   ArrayFiller m8;
   m6.fillArrayWithStuff(Schedule::AUTO, 0, uses_mutex);
   m6.printStats();

   std::cout << std::endl
             << "Aplicações sem mutex: " << std::endl
             << std::endl;

   ArrayFiller mwrong1;
   mwrong1.fillArrayWithStuff(Schedule::STATIC, 0, !uses_mutex);
   mwrong1.printStats();
   ArrayFiller mwrong2;
   mwrong2.fillArrayWithStuff(Schedule::STATIC, 5, !uses_mutex);
   mwrong2.printStats();
   ArrayFiller mwrong3;
   mwrong3.fillArrayWithStuff(Schedule::DYNAMIC, 0, !uses_mutex);
   mwrong3.printStats();
   ArrayFiller mwrong4;
   mwrong4.fillArrayWithStuff(Schedule::DYNAMIC, 5, !uses_mutex);
   mwrong4.printStats();
   ArrayFiller mwrong5;
   mwrong5.fillArrayWithStuff(Schedule::GUIDED, 0, !uses_mutex);
   mwrong5.printStats();
   ArrayFiller mwrong6;
   mwrong6.fillArrayWithStuff(Schedule::GUIDED, 5, !uses_mutex);
   mwrong6.printStats();
   ArrayFiller mwrong7;
   mwrong7.fillArrayWithStuff(Schedule::RUNTIME, 0, !uses_mutex);
   mwrong7.printStats();
   ArrayFiller mwrong8;
   mwrong6.fillArrayWithStuff(Schedule::AUTO, 0, !uses_mutex);
   mwrong6.printStats();
}
