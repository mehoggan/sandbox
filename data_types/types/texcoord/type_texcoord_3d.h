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

#ifndef TEXCOORD3D_H_INCLUDED
#define TEXCOORD3D_H_INCLUDED

#include <glext.h>
#include <math/sqrt.h>

#include <cassert>

namespace glext 
{
  /*! \class Point 3D class geometry based
   *  \brief This class defines a 3D vector
   */
  template <typename T>
  class texcoord_3d
  {
  private:
    /// The first element in the ordered pair
    T _s;
    
    /// The second element in the ordered pair
    T _t;
 
    /// The third element in the ordered pair
    T _r;

  public:
    /*! \brief default constructor sets three elements using default constructor
     */  
    texcoord_3d();

    /*! \brief constructor sets three elements to the paramaters provided
     */  
    texcoord_3d(const T &s, const T &t, const T &r);

    /*! \brief copy constructor
     */  
    texcoord_3d(const texcoord_3d &rhs);

    /*! \brief destructor 
     */
    ~texcoord_3d();

    /*! \brief assignment uses copy-swap idiom 
     */ 
    texcoord_3d &operator=(texcoord_3d rhs);

    /*! \brief index operator wich allows you to change internal data
     */
    T &operator[] (unsigned short index);

    /*! \brief index operator wich allows you to change internal data
     */
    const T &operator[] (unsigned short index) const;

    /*! \brief setter for s element
     */ 
    void s(const T &s);

    /*! \brief setter for t element
     */
    void t(const T &t);

    /*! \brief setter for r element
     */
    void r(const T &r);

    /*! \brief setter for three elements s and t and r
     */
    void s_and_t_and_r(const T &s, const T &t, const T &r);

    /*! \brief getter for s element returns a reference to s of type T
     */
    T& sref();

    /*! \brief getter for t element returns a reference to t of type T
     */
    T& tref();

    /*! \brief getter for r element returns a reference to r of type T
     */
    T& rref();

    /*! \brief getter for s element returns a copy of s of type T
     */
    T s() const;

    /*! \brief getter for t element returns a copy of t of type T
     */
    T t() const;

    /*! \brief getter for r element returns a copy of r of type T
     */
    T r() const;
  };
}
#include "type_texcoord_3d.inl"
#endif
