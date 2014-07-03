#ifndef LINEAR_ALGEBRA_H_
#define LINEAR_ALGEBRA_H_

#include "include.h"

#define __std_template template<typename T>

namespace linear_algebra {
/********************************************************************************/
	__std_template 
	class Vector {
		public:
			Vector( ) { };
			Vector( int x, int y ) { };
			virtual ~Vector( ) { };
			virtual int getDimension( )=0;
			virtual void printSelf( )=0;
	};

	__std_template
	class Vector2 : public Vector<T> {
		public:
			Vector2( );
			Vector2( T x, T y );
			virtual ~Vector2( );
			virtual T operator[](int i);
			virtual void operator()(T i) { std::cout << " " << i; };
			virtual Vector2<T>* operator+( Vector2& u );
			virtual Vector2<T>* operator*( Vector2& u );
			virtual Vector2<T>* operator*( T scalar );
			virtual int getDimension( );
			virtual void printSelf( );
		protected:
			int iDimension;
			T* tVector;
			std::vector<T>* vVector;
	};

	__std_template
	Vector2<T>::Vector2( ) {
		iDimension=2;
	}

	__std_template
	Vector2<T>::Vector2( T x, T y ) {
		iDimension=2;
		tVector=new T[2];
		vVector=new std::vector<T>();
		vVector->push_back( x );
		vVector->push_back( y );
		tVector[0]=x;
		tVector[1]=y;
	}
		
	__std_template
	Vector2<T>::~Vector2( ) {
		delete [] tVector;
		delete vVector;
	}

	__std_template
	T Vector2<T>::operator[]( int i ) {
		return tVector[i];
	}

	__std_template
	Vector2<T>* Vector2<T>::operator+( Vector2& u ) {
		return new Vector2( tVector[0]+u[0], tVector[1]+u[1] );
	}

	__std_template
	Vector2<T>* Vector2<T>::operator*( Vector2& u ) {
		return new Vector2( tVector[0]*u[0], tVector[1]*u[1] );
	}

	__std_template
	Vector2<T>* Vector2<T>::operator*( T scalar ) {
		return new Vector2( tVector[0]*scalar, tVector[1]*scalar );
	}

	__std_template
	int Vector2<T>::getDimension( ) {
		return iDimension;
	}

	__std_template
	void Vector2<T>::printSelf( ) {
		typename std::vector<T>::iterator i=vVector->begin( );
		std::reverse( vVector->begin( ), vVector->end( ) );
		int count = 0;
		std::cout << "<";
		while( i < vVector->end( ) ) {
			T out = *(i);
			std::cout << out << (i==vVector->end( )-1 ? "" : ", ");
			i++;
		}
		std::cout << ">" << std::endl;
	}

/********************************************************************************/

	/*	Abstract Matrix Class	*/
	__std_template 
	class Matrix {
	        public:
        	        Matrix( ) { };
			virtual ~Matrix() { };
	                virtual int getRows( )=0;
	                virtual int getCols( )=0;
	                virtual T* getMatrix( )=0;
	};
	
	/*	Less Abstract Matrix Type	*/
	__std_template
	class MatrixNxN : public Matrix<T> {
		public:
			MatrixNxN( );
			virtual ~MatrixNxN( );
			virtual void printSelf( );
			virtual int getRows( );
			virtual int getCols( );
			virtual T* getMatrix( );
			virtual std::vector<T> *getVectorMatrix( );
		private:
			int iRows;
			int iCols;
			T *tMatrix;
			std::vector<T> *vMatrix;
	};
	
	__std_template
	MatrixNxN<T>::MatrixNxN( ) {

	}

	__std_template
	MatrixNxN<T>::~MatrixNxN( ) {

	}
	
	__std_template
	MatrixNxN<T>* operator+( const MatrixNxN<T>& M ) {
		return new MatrixNxN<T>( );
	}	

	__std_template 
	void MatrixNxN<T>::printSelf( ) {

	}

	__std_template 
	int MatrixNxN<T>::getRows( ) {
		return iRows;
	}

	__std_template 
	int MatrixNxN<T>::getCols( ) {
		return iCols;
	}

	__std_template 
	T* MatrixNxN<T>::getMatrix( ) {
		return tMatrix;
	}

	__std_template 
	std::vector<T>* MatrixNxN<T>::getVectorMatrix( ) {
		return vMatrix;
	}

/********************************************************************************/
}

#endif	/* LINEAR_ALGEBRA_H__ */
