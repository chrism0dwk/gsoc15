/*******************************************************
 * Name: gsocTest.cpp                                  *
 * Created: 9th March 2015                             *
 * Author: Chris Jewell <chrism0dwk@gmail.com>         *
 * Copyright: Chris Jewell 2015                        *
 * Purpose: Unit testing of class hierarchy GSOC InFER *
 *           project 2015, test 2.                     *
 *******************************************************/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <exception>
#include <sstream>
#include <string>

/*******************************************************
 * Header file Pdf.hpp is expected to contain base     *
 * class Pdf, with derived classes Normal and Gamma.   *
 * The pdf(x) method returns the pdf of the            *
 * distribution evaluated at x.  A std::domain_error() *
 * exception shoud be returned if x is not in the      *
 * support of the distribution.                        *
 *                                                     *
 * It is expected that the Gamma distribution uses the *
 * parameterisation                                    *
 *                                                     *
 * f(x|a,b) = {1 \over \Gamma(a)} b^a x^{a-1} e^{-xb}  *
 *******************************************************/
#include "Pdf.hpp"

// Test variates
#define VARLEN 10
const double x[] = {0.10, 0.31, 0.52, 0.73, 0.94, 1.16, 1.37, 1.58, 1.79, 2.00};
const double fNorm[] = {0.0874, 0.3503, 0.8603, 1.2941, 1.1926, 0.6473, 0.2187, 0.0453, 0.0057, 0.0004};
const double fGamma[] = {0.3067, 1.7031, 1.4981, 0.7725, 0.3074, 0.0994, 0.0305, 0.0087, 0.0024, 0.0006};

struct BadTest : std::exception
{
  BadTest(const double x, const double err) _NOEXCEPT
  {
    std::stringstream s;
    s << "Bad Test on x=" << x << " with error " << err << std::endl;
    msg_ = s.str();
  }
  ~BadTest() _NOEXCEPT {};
  const char* what() const _NOEXCEPT
  {
    return msg_.c_str();
  }
  std::string msg_;
};

void
runTest(Pdf* f, const double* ans)
{
  for(int i=0; i<VARLEN; ++i)
    {
      double err = f->pdf(x[i]) - ans[i];
      if(fabs(err) > 5.0e-5) throw BadTest(x[i], err);
    }
}


int main(int argc, char* argv[])
{
  // Generic base class pointers
  // to instances of distributions.
  // Tests constructors.
  Pdf* norm = new Normal(0.8,0.3);
  Pdf* gamma = new Gamma(4.0,8.0);

  // Test normal
  try {
    std::cout << "Testing Normal distribution..." << std::flush;
    runTest(norm, fNorm);
    std::cout << "PASSED" << std::endl;
  }
  catch (BadTest& e)
    {
      std::cout << "FAILED: " << std::flush;
      std::cerr << "Normal distribution: " << e.what() << std::endl;
    }
  catch (std::range_error& e)
    {
      std::cout << "FAILED: " << std::flush;
      std::cerr << e.what() << std::endl;
    }
  catch (std::exception& e)
    {
      std::cout << "FAILED: " << std::flush;
      std::cerr << "Unknown exception: " << e.what() << std::endl;
    }


  // Test Gamma distribution 
  try {
    std::cout << "Testing Gamma distribution..." << std::flush;
    runTest(gamma, fGamma);
    
    // Test range error
    bool isDomainError = false;
    try {
      gamma->pdf(-1.5);
    }
    catch (std::domain_error& e)
      {
	isDomainError = true;
      }
    if(isDomainError)
      std::cout << "PASSED" << std::endl;
    else throw std::domain_error("Invalid value accepted by Gamma distribution");
  }
  catch (BadTest& e)
    {
      std::cout << "FAILED: " << std::flush;
      std::cerr << "Gamma distribution: " << e.what() << std::endl;
    }
  catch (std::domain_error& e)
    {
      std::cout << "FAILED: " << std::flush;
      std::cerr << e.what() << std::endl;
    }
  catch (std::exception& e)
    {
      std::cout << "FAILED: " << std::flush;
      std::cerr << "Unknown exception: " << e.what() << std::endl;
    }



  return EXIT_SUCCESS;
}

