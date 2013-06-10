#ifndef TYPE_MATRIX_4X4_H_INCLUDED
#define TYPE_MATRIX_4X4_H_INCLUDED

#include <glext.h>
#include <types/vectors/type_vector_3d.h>
#include <types/vectors/type_vector_4d.h>

namespace glext 
{
  enum matrix_type {null = 0, identity = 1};
  enum matrix_layout {column = 0, row = 1};

  /*! \class Matrix 4X4 a CG based representation of a matrix which supports
   * both row and column based representations.
   */
  template<typename T, matrix_layout ML = column>
  class matrix_4X4
  {
  private:
    /// The first row or column in (*thiS) matrix
    vector_4d<T> _v0;

    /// The second row or column in (*thiS) matrix
    vector_4d<T> _v1;

    /// The third row or column in (*thiS) matrix
    vector_4d<T> _v2;

    /// The fourth row or column in (*thiS) matrix
    vector_4d<T> _v3;

  public:
    /*! \brief default constructor which constructs the identity matrix or a
     * matrix all initialized to zero based on the matrix type passed in.
     */
    matrix_4X4(matrix_type type = null);

    /*! \brief constructor which takes 4 vectors of type T and assigns them
     * to the member varables v1 - v4
     */
    matrix_4X4(const vector_4d<T> &v0, const vector_4d<T> &v1, 
      const vector_4d<T> &v2, const vector_4d<T> &v3);

    /*! \brief copy constructor
     */
    matrix_4X4(const matrix_4X4 &rhs);

    /*! \brief destructor
     */
    ~matrix_4X4();

    /*! \brief assignment uses copy-swap idiom
     */
    matrix_4X4 &operator=(matrix_4X4 rhs);

    /*! \brief index operator which returns a reference to one of the inner
     * vector_4d<T>s
     */
    vector_4d<T> &operator[](unsigned short index);
    
    /*! \brief index operator which returns a const reference to one of the 
     * inner vector_4d<T>s
     */
    const vector_4d<T> &operator[](unsigned short index) const;

    /*! \brief setter for memeber vector_4d<T> v0 
     */ 
    void vec0(const vector_4d<T> &v0);  

    /*! \brief setter for memeber vector_4d<T> v1 
     */ 
    void vec1(const vector_4d<T> &v1);  

    /*! \brief setter for memeber vector_4d<T> v2 
     */ 
    void vec2(const vector_4d<T> &v2);  

    /*! \brief setter for memeber vector_4d<T> v3 
     */ 
    void vec3(const vector_4d<T> &v3);
    
    /*! \brief getter for memeber vector_4d<T> v0 
     */ 
    vector_4d<T> vec0() const;  

    /*! \brief getter for memeber vector_4d<T> v1 
     */ 
    vector_4d<T> vec1() const;  

    /*! \brief getter for memeber vector_4d<T> v2 
     */ 
    vector_4d<T> vec2() const;  

    /*! \brief getter for memeber vector_4d<T> v3 
     */ 
    vector_4d<T> vec3() const;

    /*! \brief add a matrix from this matrix
     */
    void operator+=(const matrix_4X4 &rhs);

    /*! \brief subtract a matrix from this matrix
     */
    void operator-=(const matrix_4X4 &rhs);

    /*! \brief multiply this matrix by another matrix
     */
    void operator*=(const matrix_4X4 &rhs);
    
    /*! \brief multiply this matrix by another matrix
     */
    void operator*=(const T &rhs);
  };

  template <typename U, matrix_layout ML>
  void swap(matrix_4X4<U, ML> &lhs, matrix_4X4<U, ML> &rhs);
}
#include "type_matrix_4X4.inl"
#endif








