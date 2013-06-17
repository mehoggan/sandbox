/*
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COLORRGB_H_INCLUDED
#define COLORRGB_H_INCLUDED

#include <glext.h>
#include <math/clamp.h>

namespace glext 
{
  /*! \class Color 3D class abstract class to rerpesnt a rgb or bgr color
   * 3D space.
   *  \brief This class defines a rgb or bgr color
   */
  template <typename T>
  class color_rgb
  {
  private:
    /// The first element in the ordered pair
    T _r;
    
    /// The second element in the ordered pair
    T _g;

    /// The third element in the ordered pair
    T _b;
  
  public:
    /*! \brief default constructor sets both elements using default constructor
     */  
    color_rgb();

    /*! \brief constructor sets both elements to the paramaters provided
     */  
    color_rgb(const T &r, const T &g, const T &b);

    /*! \brief copy constructor
     */  
    color_rgb(const color_rgb &rhs);

    /*! \brief destructor 
     */
    ~color_rgb();

    /*! \brief assignment uses copy-swap idiom 
     */ 
    color_rgb &operator=(color_rgb rhs);

    /*! \brief setter for r element
     */ 
    void r(const T &r);

    /*! \brief setter for g element
     */
    void g(const T &g);
    
    /*! \brief setter for b element
     */
    void b(const T &b);

    /*! \brief setter for both r and g and b element
     */
    void r_and_g_and_b(const T &r, const T &g, const T &b);

    /*! \brief getter for r element returns a reference to r of type T
     */
    T& rref();

    /*! \brief getter for g element returns a reference to g of type T
     */
    T& gref();
    
    /*! \brief getter for b element returns a reference to b of type T
     */
    T& bref();

    /*! \brief getter for r element returns a copy of r of type T
     */
    T r() const;

    /*! \brief getter for g element returns a copy of g of type T
     */
    T g() const;
    
    /*! \brief getter for b element returns a copy of b of type T
     */
    T b() const;

    /*! \brief to keep consistant with other storage patterns 
     */
    void to_bgr();
  };
}
#include "type_color_rgb.inl"
#endif
