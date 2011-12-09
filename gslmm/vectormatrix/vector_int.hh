//
// $Id: vector_skel.hh,v 1.24 2006-05-11 00:39:39 cholm Exp $ 
//  
// WARNING: automatically generated by make-header.sh
//          options: @skel@, int .  
//          Do not edit this file.
//
//  gslmm::vector_int
//  Copyright (C) 2002 Christian Holm Christensen <cholm@nbi.dk> 
//
//  This library is free software; you can redistribute it and/or 
//  modify it under the terms of the GNU Lesser General Public License 
//  as published by the Free Software Foundation; either version 2.1 
//  of the License, or (at your option) any later version. 
//
//  This library is distributed in the hope that it will be useful, 
//  but WITHOUT ANY WARRANTY; without even the implied warranty of 
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
//  Lesser General Public License for more details. 
// 
//  You should have received a copy of the GNU Lesser General Public 
//  License along with this library; if not, write to the Free 
//  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
//  02111-1307 USA 
//
#ifndef GSLMM_vector_int
#define GSLMM_vector_int
#line 29 "vector_skel.hh"
#ifndef GSLMM_util
# include <gslmm/gslmm-util.hh>
#endif
#ifndef GSLMM_vector_base
# include <gslmm/vectormatrix/vector_base.hh>
#endif
#ifndef __GSL_VECTOR_H__
# include <gsl/gsl_vector.h>
#endif
#ifndef GSLMM_vectormatrix_matrix_base
# include <gslmm/vectormatrix/matrix_base.hh>
#endif
#if 0
# ifndef GSLMM_
#  include <gslmm/compleks/.hh>
# endif
#endif
#ifndef GSLMM_math_type_trait
# include <gslmm/math/type_trait.hh>
#endif

/** @file   vector_int.hh
    @author Christian Holm
    @date   Mon Sep 16 04:41:27 2002
    @brief  Vector specialisation for @c int . */

namespace gslmm 
{
  class permutation;

  /** @brief Vector @c int  specialisation. 
      @ingroup vector 
      @param int   The POD of the specialisation. 
      @c L  is The short-hand type of the specialisation. 
  */ 
  template<>
  class vector<int  >
  {
  public:
    /** Size type. */
    typedef size_t size_type;
    /** Iterator (or indexer) type.  */
    typedef size_t iterator;
    /** Type of data */
    typedef int  value_type;
    /** Low level data type  */
    typedef gsl_vector_int data_type;
    /** Low level view type  */
    typedef gsl_vector_int_view view_type;
    /** A constant view */
    typedef _gsl_vector_int_const_view const_view_type;
    /** Trait type */
    typedef type_trait<value_type> trait_type;
    /** reference type */
    typedef trait_type::reference_type reference_type;
    /** Elementary type */
    typedef trait_type::elementary_type element_type;
    /** Type of return value */
    typedef vector_return<value_type> return_type;
    /** Type of passed return type */
    typedef std::auto_ptr<return_type> oper_type;
    
    /** @{ 
	@name Constructors */
    /** Constructor 
	@param m Matrix-vector product to assign from */
    vector(oper_type m);
    /**  constructor */
    vector(const view_type& v) : _vector(0) { from_view(v); }
    /**  Constructor */
    vector(const_view_type  v) : _vector(0) { from_view(v); }
    /** Default Constructor.*/
    // vector();
    /** Normal Constructor.
	@param n size of the vector. 
	@param zero if true, zero the vector. */ 
    vector(size_type n, bool zero=true);
    /** Copy constructor. 
	If the passed vector is a view (i.e., doesn't own it's data),
	and @a really is false (default), a new view (or reference) is
	created.  If the passed vector @a w is a view, and @a really
	is true, then a new vector (owns it data) is made regardless. 
	@note This is important in the abscence of Return Value
	Optimisation (RVO) or even Named Return Value Optimisation
	(NRVO) as it otherwise would be impossible to make views. 
	@param w Vecor to copy. 
	@param really If true, make a new vector, even if @a w is a
	view on another object (like a vector, matrix, or array).  */
    vector(const vector<value_type>& w, bool really=false);
    /** Subvector constructor. 
	@param w Vector to reference.
	@param offset where to start the view. 
	@param n elements in the view. 
	@param stride Stride in the view. */
    vector(const vector<value_type>& w, iterator  offset,
	   size_type n, iterator  stride=1);
    /** Array constructor. 
	@param data the array to use.
	@param n elements in the view. 
	@param stride Stride in the view. */
    vector(element_type* data, size_type n, iterator  stride=1);
    /** Destructor. 
	In case this is vector is a view of another vector or matrix,
	then this member function does not free the memory associated
	with the object. */ 
    virtual ~vector();
    /** @} */

    /** @{
	@name Information */
    /** Get the size (number of elements) of this vector. 
	@return the size of this vector. */
    iterator size() const { return _vector->size; }
    /** Get the stride of this vector. 
	@return the stride of this vector. */
    size_type stride() const { return _vector->stride; }
    /** Set the stride of the vector. 
	@param s the new stride. */ 
    size_type stride(size_type s) { return _vector->stride = s; }
    /** Get the internal data of this vector. 
	@return internal data array. */
    element_type* data() const { return _vector->data; }
    /** Test if this vector owns the memory associated. 
	@return true if the vector is owner, false otherwise. */ 
    bool is_owner() const { return _vector->owner == 1 ? true : false; }
    /** @} */

    /** @{
	@name Access elements */
    /** Access element. 
	Access the @f$ i^{\mbox{th}}@f$ element of the vector. 
	@param i element to access.
	@return @f$ v_i@f$ */
    reference_type operator[](iterator  i);
    /**  Access element - constant version.  
	 Access the @f$ i^{\mbox{th}}@f$ element of the vector. 
	 @param i element to access.
	 @return @f$ v_i@f$ */
    const reference_type operator[](iterator  i) const;
    /** Access address of element 
	@param i the element to get. 
	@return address of the @f$ i^{\mbox{th}}@f$ element or raise
	error if out of bounds and return 0. */ 
    value_type* element(iterator  i);
    /** Access address of element - constant version.  
	@param i the element to get. 
	@return address of the @f$ i^{\mbox{th}}@f$ element or raise
	error if out of bounds and return 0. */ 
    const value_type* element(iterator  i) const;
    /** @} */

    /** @{
	@name Iterations */
    /** Return the index of the first element (always 0). 
	This is just to be able to do iteration on the vector in an
	STL like fashion: 
	@code 
	gslmm::vector<int> v(10); 
	for (gslmm::vector<int>::iterator i = v.begin(); i != v.end(); i++)
	  v[i] = i + 10;
	@endcode 
	@return index of first element. */ 
    iterator begin() const { return 0; }
    /** Returns the least not valid index of the vector (size()). 
	This is for STL-like iterations.  See also the begin member
	function.  Note, that the iterator returned is not a valid
	index into the vector.  That is, 
	@code 
	gslmm::vector<int> v(10); 
	v[v.end()] = 10; 
	@endcode 
	will give you a segmentation violation (SIGSEGV - access to
	invalid memory). 
	@return the least not-valid index of the vector. */ 
    iterator end() const { return size(); }
    /** @} */

    /** @{
	@name Manipulators */
    /** Reset all elements to zero  */
    void zero();
    /** Set all elements to one number. 
	@param x the value to set all elements to. */
    void set(value_type x);
    /* Make a basis vector.
       only the @f$ i^{\mbox{th}}@f$ is 1, rest of the elements are
       zero.  
       @param i the component to be 1. */ 
    void basis(iterator  i);
    /** @} */

    /** @{
	@name Views */
    /** Get a subvector (or view) of this vector. 
	@param offset where to start the view. 
	@param n elements in the view. 
	@param stride Stride of the view. 
	@return the subvector. */ 
    vector<value_type> operator()(iterator  offset, 
				  size_type n,
				  iterator  stride=1);

    /** Get a subvector (or view) of this vector - const version.
	@param offset where to start the view. 
	@param n elements in the view. 
	@param stride Stride of the view. 
	@return the subvector. */ 
    const vector<value_type> operator()(iterator  offset, 
					size_type n,
					iterator  stride=1) const;
    /** @} */

    /** @{
	@name Changing order */
    /** Swap elements of this vector with another vector. 
	@param w to swap elements with. 
	@return 0 on success, error code otherwise.  */
    int swap(vector<value_type>& w);
    /** Swap elements in the vector. 
	@param i first elemenet, which will be at @f$ j^{\mbox{th}}@f$
	position after operation. 
	@param j second elemenet, which will be at @f$ j^{\mbox{th}}@f$
	position after operation. 
	@return 0 on success, error code otherwise.  */
    int swap(iterator  i, iterator  j);
    /** Reverse the elements of the vector. 
	@return 0 on success, error code otherwise.  */
    int reverse();
    /** @} */

    /** @{
	@name Assignment operators */
    /** Assignment from another vector. 
	@param w the vector to assign from. 
	@return reference to object. */ 
    vector<value_type>& 
    operator=(const vector<value_type>& w);
    /** Assignment from another vector. 
	@param m the matrix-vector product to assign from. 
	@return reference to object. */ 
    vector<value_type>& 
    operator=(oper_type m);
    /** Add another vector to this vector. 
	@f$ v_i = v_i + w_i @f$
	@param w vector to add to this. 
	@return reference to the object */
    vector<value_type>& 
    operator+=(const vector<value_type>& w);
    /** Subtract another vector to this vector. 
	@f$ v_i = v_i - w_i @f$
	@param w vector to subtract from this. 
	@return reference to the object.  */
    vector<value_type>& 
    operator-=(const vector<value_type>& w);
    /** Multiply another vector elemen by element to this vector.  
	@f$ v_i = v_i \cdot w_i @f$
	@param w vector to multiply with. 
	@return reference to the object.  */
    vector<value_type>& 
    operator*=(const vector<value_type>& w);
    /** Divide another vector element by element to this vector. 
	@f$ v_i = v_i / w_i @f$
	@param w vector to divide with to this. 
	@return reference to the object.  */
    vector<value_type>& 
    operator/=(const vector<value_type>& w);
    /** Add a constant to each element.
	@f$ v_i = a + v_i @f$
	@param a constant to add to elements. 	
	@return reference to the object.  */
    vector<value_type>& operator+=(const value_type a);
    /** Subtract a constant from each element.
	@f$ v_i = a - v_i @f$
	@param a constant to add to elements. 	
	@return reference to the object.  */
    vector<value_type>& operator-=(const value_type a);
    /** Multiply each element by a constant. 
	@f$ v_i =  v_i \cdot a@f$
	@param a constant to divide with. 	
	@return reference to the object.  */
    vector<value_type>& operator*=(const value_type a);
    /** Divide each element by a constant. 
	@f$ v_i =  v_i / a@f$
	@param a constant to divide with. 	
	@return reference to the object.  */
    vector<value_type>& operator/=(const value_type a);
    /** @} */

    /** @{
	@name Properties */
    /** Inner product of this and other vector. 
	@param w the vector to from product with. 
	@return @f$ \sum_i^n v_i\cdot w_i@f$. */ 
    value_type inner_product(const vector<value_type>& w) const;
    /* matrix<value_type,element_type> 
       outer_product(const vector<value_type>& other) const;*/
    /** Get the length of this vector. 
	@return @f$ \sqrt{\sum_i^n v_i^2}@f$. */ 
    value_type length() const;
    /** Test if vector is null vector. 
	@return true if all elements are zero, false otherwise. */
    bool  is_null() const;
    /** @} */

#if 0
    /** @{
	@name Real and imagiinary parts */
    /** Get a sub-vector (or view) of the real value of the complex
	numbers. 
	@return sub-vector of real values. */
    vector<element_type> real() ;
    /** Get a sub-vector (or view) of the real value of the complex
	numbers. 
	@return sub-vector of real values. */
    const vector<element_type> real() const;
    /** Get a sub-vector (or view) of the imaginary value of the complex
	numbers. 
	@return sub-vector of imaginary values. */
    vector<element_type>  imag() ;
    /** Get a sub-vector (or view) of the imaginary value of the complex
	numbers. 
	@return sub-vector of imaginary values. */
    const vector<element_type> imag() const; 
    /** @} */
#endif

#if 0
#else 
    /** @{
	@name Minimum and maximum elements */
    /** Find the largest element in the vector. 
	@return value of largest element in the vector. */
    value_type min() const;
    /** Find the largest element in the vector. 
	@return value of largest element in the vector. */
    value_type max() const;
    /** Find value of least and largest element in the vector. 
	@param min Value of least element. 
	@param max Value of largest element. */
    void minmax(value_type& min, value_type& max) const;
    /** Find the index of the least element of the vector. 
	@return index of the least element. */
    iterator min_index() const;
    /** Find the index of the largest element of the vector. 
	@return index of the largest element. */
    iterator max_index() const;
    /** Find the index of the least and largest element of the vector. 
	@param min Index of least element. 
	@param max Index of largest element. */
    void minmax_index(iterator& min, iterator& max) const; 
    /** @} */
#endif
    /** The data  */
    data_type* _vector;
  protected:
    /** Permutation is a friend */
    friend class permutation;
    /** Matrix is a friend */
    friend class matrix<value_type>;
    /** Distribution is a friend */
    friend class distribution<vector<value_type> >;
    /** Default ctor */
    vector() : _vector(0) {}
    /** Initalise from an externally created view  */
    void from_view(const view_type& v);
    /** Initalise from an externally created view  */
    void from_view(const_view_type& v);
  public:
  };
}

#ifndef GSLMM_vectormatrix_matrix_int
# include <gslmm/vectormatrix/matrix_int.hh>
#endif

namespace gslmm
{
  //__________________________________________________________________
  inline 
  vector<int >::vector(oper_type m)
    : _vector(0)    
  {
    assert(m.get());
    if (!m.get()) GSL_ERROR_VOID("NULL return passed", GSL_EINVAL);
    _vector = gsl_vector_int_calloc(m->size());
    m->operator()(*this);
    // delete m;
    // m = 0;
  }

  //__________________________________________________________________
  inline 
  vector<int >::vector(size_type n, bool zero)
    : _vector(0)    
  {
    if (zero) _vector = gsl_vector_int_calloc(n);
    else      _vector = gsl_vector_int_alloc(n);
  }

  //__________________________________________________________________
  inline 
  vector<int >::vector(const vector<value_type>& w, bool really)
    : _vector(0)    
  {
    // We do this check, 'cause if the object to copy is merely a
    // reference, then we don't want to allocate memory - which
    // essentially would make a new vector.  In stead, what we want is
    // to create another reference.  This is especially important if
    // the compiler doesn't do RVO (or even NRVO)
    if (w.is_owner() || really) {
      _vector = gsl_vector_int_alloc(w.size()); 
      *this   = w;
    }
    else {
      view_type v = gsl_vector_int_subvector(w._vector,0,w.size());
      from_view(v);
    }
  }

  //__________________________________________________________________
  inline 
  vector<int >::vector(const vector<value_type>& w,
			 iterator  offset,
			 size_type n,
			 iterator  stride)
    : _vector(0)    
  {
    view_type v;
    if (stride <= 1) 
      v = gsl_vector_int_subvector(w._vector, offset, n);
    else 
      v = gsl_vector_int_subvector_with_stride(w._vector, offset, stride, n);
    from_view(v);
  }

  //__________________________________________________________________
  inline 
  vector<int >::vector(element_type* a, size_type n, iterator  stride)
    : _vector(0)    
  {
    view_type v;
    if (stride <= 1)
      v = gsl_vector_int_view_array(a, n);
    else
      v = gsl_vector_int_view_array_with_stride(a,stride,n);
    from_view(v);
  }


  //__________________________________________________________________
  inline 
  vector<int >::~vector()
  {
    gsl_vector_int_free(_vector);
  }

  //__________________________________________________________________
  inline void 
  vector<int >::from_view(const view_type& v) 
  {
    _vector = static_cast<data_type*>(malloc(sizeof(data_type)));
    _vector->size   = v.vector.size;
    _vector->stride = v.vector.stride;
    _vector->data   = v.vector.data;
    _vector->block  = v.vector.block;
    _vector->owner  = v.vector.owner;
  }
  //__________________________________________________________________
  inline void 
  vector<int >::from_view(const_view_type& v) 
  {
    _vector = static_cast<data_type*>(malloc(sizeof(data_type)));
    _vector->size   = v.vector.size;
    _vector->stride = v.vector.stride;
    _vector->data   = v.vector.data;
    _vector->block  = v.vector.block;
    _vector->owner  = v.vector.owner;
  }
  
  //__________________________________________________________________
  inline const vector<int >::reference_type 
  vector<int >::operator[](iterator  i) 
    const
  {
#if 0
    return reference_type(gsl_vector_int_const_ptr(_vector,i));
#else
    return reference_type(*gsl_vector_int_const_ptr(_vector,i));
#endif
  }

  //__________________________________________________________________
  inline 
  vector<int >::reference_type
  vector<int >::operator[](iterator  i)
  {
#if 0
    return reference_type(gsl_vector_int_const_ptr(_vector,i));
#else
    return reference_type(*gsl_vector_int_const_ptr(_vector,i));
#endif
  }
  //__________________________________________________________________
  inline 
  const 
  vector<int >::value_type* 
  vector<int >::element(iterator  i) const
  {
#if 0
    return (value_type*)(gsl_vector_int_const_ptr(_vector,i));
#else
    return const_cast<value_type*>(gsl_vector_int_const_ptr(_vector,i));
#endif
  }
  
  //__________________________________________________________________
  inline 
  vector<int >::value_type* 
  vector<int >::element(iterator  i)
  {
#if 0
    return (value_type*)(gsl_vector_int_ptr(_vector,i));
#else
    return const_cast<value_type*>(gsl_vector_int_ptr(_vector,i));
#endif
  }

  //__________________________________________________________________
  inline void vector<int >::zero()
  { 
    gsl_vector_int_set_zero(_vector);
  }

  //__________________________________________________________________
  inline void 
  vector<int >::set(value_type x)
  {
    gsl_vector_int_set_all(_vector,x);
  } 

  //__________________________________________________________________
  inline void 
  vector<int >::basis(iterator  i)
  {
    gsl_vector_int_set_basis(_vector, i);
  }

  //__________________________________________________________________
  inline vector<int > 
  vector<int >::operator()(iterator  offset, size_type n, iterator  stride)
  {
    return vector<int >(*this, offset, n, stride);
  }

  //__________________________________________________________________
  inline const vector<int > 
  vector<int >::operator()(iterator  offset, size_type n, iterator  stride) 
    const
  {
    return vector<int >(*this, offset, n, stride);
  }

  //__________________________________________________________________
  inline int vector<int >::swap(vector<value_type>& other)
  {
    return gsl_vector_int_swap(_vector, other._vector);
  }

  //__________________________________________________________________
  inline int 
  vector<int >::swap(iterator  i, iterator  j)
  {
    return gsl_vector_int_swap_elements(_vector, i, j);
  }

  //__________________________________________________________________
  inline int vector<int >::reverse()
  {
    return gsl_vector_int_reverse(_vector);
  }

  //__________________________________________________________________
  inline vector<int >& 
  vector<int >::operator=(const vector<value_type>& w)
  {
    gsl_vector_int_memcpy(_vector, w._vector); 
    return *this;
  }
  //__________________________________________________________________
  inline vector<int >& 
  vector<int >::operator=(oper_type m)
  {
    assert(m.get());
    if (!m.get()) GSL_ERROR_VAL("NULL return passed", GSL_EINVAL, *this);
    m->operator()(*this);
    // delete m;
    // m = 0;
    return *this;
  }

  //__________________________________________________________________
  inline bool 
  vector<int >::is_null() const
  {
    return gsl_vector_int_isnull(_vector) == 1 ? true : false;
  }

#if 0 
  //__________________________________________________________________
  inline matrix<int > 
  vector<int >::outer_product(const vector<value_type> w) const
  {
    matrix<int > m(size(),w.size());
    for (vector<int >::iterator  i = 0; i < size(); i++)
      for (vector<int >::iterator  j = 0; j < w.size(); j++)
	m[i][j] = (*this)[i] * w[j];
    return m;
  } 
#endif

#if 0
  // Below are only for complex vectors
  //__________________________________________________________________
  inline vector<int >::value_type 
  vector<int >::inner_product(const vector<value_type>& w)  const
  {
    value_type ret;
    for (vector<int >::iterator  i = 0; 
	 i < size() && i < w.size(); i++)
      ret += this->operator[](i) * w[i];
    return ret;
  }

  //__________________________________________________________________
  inline vector<int >::value_type 
  vector<int >::length() const 
  {
    return sqrt(inner_product(*this));
  }

  //__________________________________________________________________
  inline vector<int> 
  vector<int >::real()
  {
    return 
      vector<int>(gsl_vector_int_real(this->_vector));
  }

  //__________________________________________________________________
  inline const vector<int> 
  vector<int >::real() const
  {
    return 
      vector<int>(gsl_vector_int_const_real(this->_vector));
  }

  //__________________________________________________________________
  inline vector<int> 
  vector<int >::imag()
  {
    return 
      vector<int>(gsl_vector_int_imag(this->_vector));
  }

  //__________________________________________________________________
  inline const vector<int> 
  vector<int >::imag() const 
  {
    return 
      vector<int>(gsl_vector_int_const_imag(this->_vector));
  }

#define _GSLMM_VECTOR_FOREACH(w,f) \
  do { for (vector<int >::iterator i = this->begin(); \
       i != this->end() && i != w.end(); i++) \
    this->operator[](i) f w[i]; } while (false) 
  
  //__________________________________________________________________
  inline vector<int >& 
  vector<int >::operator+=(const vector<value_type>& w)
  {
    _GSLMM_VECTOR_FOREACH(w,+=); return *this;
  }

  //__________________________________________________________________
  inline vector<int >& 
  vector<int >::operator-=(const vector<value_type>& w)
  {
    _GSLMM_VECTOR_FOREACH(w,-=); return *this;
  }

  //__________________________________________________________________
  inline vector<int >& 
  vector<int >::operator*=(const vector<value_type>& w)
  {
    _GSLMM_VECTOR_FOREACH(w,*=); return *this;
  }

  //__________________________________________________________________
  inline vector<int >& 
  vector<int >::operator/=(const vector<value_type>& w)
  {
    _GSLMM_VECTOR_FOREACH(w,/=); return *this;
  }
#undef _GSLMM_VECTOR_FOREACH
#define _GSLMM_VECTOR_FOREACH(x,f) \
  do { for (vector<int >::iterator i = this->begin(); i != this->end(); i++)\
    this->operator[](i) f x; } while(false) 
  
  //__________________________________________________________________
  inline vector<int >&
  vector<int >::operator+=(const value_type x)
  {
    _GSLMM_VECTOR_FOREACH(x,+=); return *this;
  }

  //__________________________________________________________________
  inline vector<int >&
  vector<int >::operator-=(const value_type x)
  {
    _GSLMM_VECTOR_FOREACH(x,-=); return *this;
  }

  //__________________________________________________________________
  inline vector<int >&
  vector<int >::operator*=(const value_type x)
  {
    _GSLMM_VECTOR_FOREACH(x,*=); return *this;
  }

  //__________________________________________________________________
  inline vector<int >&
  vector<int >::operator/=(const value_type x)
  {
    _GSLMM_VECTOR_FOREACH(x,/=); return *this;
  }
#undef _GSLMM_VECTOR_FOREACH
#else
  // Below is only for real valued vectors. 
  //__________________________________________________________________
  inline vector<int >& 
  vector<int >::operator+=(const vector<value_type>& w)
  {
    gsl_vector_int_add(_vector, w._vector); return *this;
  }

  //__________________________________________________________________
  inline 
  vector<int >& 
  vector<int >::operator-=(const vector<value_type>& w)
  {
    gsl_vector_int_sub(_vector, w._vector); return *this;
  }

  //__________________________________________________________________
  inline 
  vector<int >& 
  vector<int >::operator*=(const vector<value_type>& w)
  {
    gsl_vector_int_mul(_vector, w._vector); return *this;
  }

  //__________________________________________________________________
  inline 
  vector<int >&  
  vector<int >::operator/=(const vector<value_type>& w)
  {
    gsl_vector_int_div(_vector, w._vector); return *this;
  }

  //__________________________________________________________________
  inline 
  vector<int >& 
  vector<int >::operator+=(const value_type a)
  {
    gsl_vector_int_add_constant(_vector, a); return *this;
  }

  //__________________________________________________________________
  inline 
  vector<int >& 
  vector<int >::operator-=(const value_type a)
  {
    gsl_vector_int_add_constant(_vector, -a); return *this;
  }

  //__________________________________________________________________
  inline 
  vector<int >& 
  vector<int >::operator*=(const value_type a)
  {
    gsl_vector_int_scale(_vector, a); return *this;
  }

  //__________________________________________________________________
  inline 
  vector<int >& 
  vector<int >::operator/=(const value_type a)
  {
    gsl_vector_int_scale(_vector, 1 / a); return *this;
  }

  //__________________________________________________________________
  inline 
  vector<int >::value_type 
  vector<int >::inner_product(const vector<value_type>& w)  const
  {
    value_type ret = 0;
    for (vector<int >::iterator  i = 0; i < size() && i < w.size(); i++)
      ret += this->operator[](i) * w[i];
    return ret;
  }

  //__________________________________________________________________
  inline 
  vector<int >::value_type 
  vector<int >::length() const
  {
    return value_type(::sqrt(double(inner_product(*this))));
  }

  //__________________________________________________________________
  inline 
  vector<int >::value_type 
  vector<int >::min() const
  {
    return gsl_vector_int_min(_vector);
  }

  //__________________________________________________________________
  inline 
  vector<int >::value_type 
  vector<int >::max() const
  {
    return gsl_vector_int_max(_vector);
  }

  //__________________________________________________________________
  inline 
  void 
  vector<int >::minmax(value_type& min, value_type& max) const
  {
    return gsl_vector_int_minmax(_vector, &min, &max);
  }

  //__________________________________________________________________
  inline 
  vector<int >::iterator  
  vector<int >::min_index() const
  {
    return gsl_vector_int_min_index(_vector);
  }

  //__________________________________________________________________
  inline 
  vector<int >::iterator  
  vector<int >::max_index() const
  {
    return gsl_vector_int_max_index(_vector);
  }

  //__________________________________________________________________
  inline 
  void 
  vector<int >::minmax_index(iterator& min, iterator& max) const
  {
    return gsl_vector_int_minmax_index(_vector, &min, &max);
  }
#endif
}

#if 0
#if 0
# ifndef GSLMM_blas_blas_int
#  include <gslmm/blas/blas_int.hh>
# endif
#endif
#endif

#endif
//____________________________________________________________________
//
// EOF
//

