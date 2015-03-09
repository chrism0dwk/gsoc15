/****************************************************************************
 * Name: Pdf.hpp                                                            *
 * Created: 9th March 2015                                                  *
 * Author: Chris Jewell <chrism0dwk@gmail.com>                              *
 * Copyright: Chris Jewell 2015                                             *
 * Purpose: Pure virtual base class Pdf for returning probability           *
 *           distribution functions of random variables.                    *
 *                                                                          *
 * This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by    *
 *  the Free Software Foundation, either version 3 of the License, or       *
 *  (at your option) any later version.                                     *
 *                                                                          *
 *  This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ****************************************************************************/

class Pdf {
public:
  virtual double pdf(const double x) const = 0;
  virtual ~Pdf() { }
};
