
#ifndef __GLIBCPP_INTERNAL_ITERATOR_H
#define __GLIBCPP_INTERNAL_ITERATOR_H

namespace std
{
 
  template<typename _Iterator>
    class reverse_iterator 
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
		      typename iterator_traits<_Iterator>::value_type,
		      typename iterator_traits<_Iterator>::difference_type,
		      typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator current;

    public:
      typedef _Iterator 				       iterator_type;
      typedef typename iterator_traits<_Iterator>::difference_type 	
      							       difference_type;
      typedef typename iterator_traits<_Iterator>::reference   reference;
      typedef typename iterator_traits<_Iterator>::pointer     pointer;

    public:
      /**
       *  The default constructor gives an undefined state to this %iterator.
      */
      reverse_iterator() { }

      /**
       *  This %iterator will move in the opposite direction that @p x does.
      */
      explicit 
      reverse_iterator(iterator_type __x) : current(__x) { }

      /**
       *  The copy constructor is normal.
      */
      reverse_iterator(const reverse_iterator& __x) 
      : current(__x.current) { }

      /**
       *  A reverse_iterator across other types can be copied in the normal
       *  fashion.
      */
      template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x)
	: current(__x.base()) { }
    
      /**
       *  @return  @c current, the %iterator used for underlying work.
      */
      iterator_type 
      base() const { return current; }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reference  
      operator*() const 
      {
	_Iterator __tmp = current;
	return *--__tmp;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      pointer 
      operator->() const { return &(operator*()); }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reverse_iterator& 
      operator++() 
      {
	--current;
	return *this;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reverse_iterator 
      operator++(int) 
      {
	reverse_iterator __tmp = *this;
	--current;
	return __tmp;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reverse_iterator& 
      operator--() 
      {
	++current;
	return *this;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reverse_iterator operator--(int) 
      {
	reverse_iterator __tmp = *this;
	++current;
	return __tmp;
      }
      
      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reverse_iterator 
      operator+(difference_type __n) const 
      { return reverse_iterator(current - __n); }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reverse_iterator& 
      operator+=(difference_type __n) 
      {
	current -= __n;
	return *this;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reverse_iterator 
      operator-(difference_type __n) const 
      { return reverse_iterator(current + __n); }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reverse_iterator& 
      operator-=(difference_type __n) 
      {
	current += __n;
	return *this;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reference 
      operator[](difference_type __n) const { return *(*this + __n); }  
    }; 
 
  //@{
  /**
   *  @param  x  A %reverse_iterator.
   *  @param  y  A %reverse_iterator.
   *  @return  A simple bool.
   *
   *  Reverse iterators forward many operations to their underlying base()
   *  iterators.  Others are implemented in terms of one another.
   *
  */
  template<typename _Iterator>
    inline bool 
    operator==(const reverse_iterator<_Iterator>& __x, 
	       const reverse_iterator<_Iterator>& __y) 
    { return __x.base() == __y.base(); }

  template<typename _Iterator>
    inline bool 
    operator<(const reverse_iterator<_Iterator>& __x, 
	      const reverse_iterator<_Iterator>& __y) 
    { return __y.base() < __x.base(); }

  template<typename _Iterator>
    inline bool 
    operator!=(const reverse_iterator<_Iterator>& __x, 
	       const reverse_iterator<_Iterator>& __y) 
    { return !(__x == __y); }

  template<typename _Iterator>
    inline bool 
    operator>(const reverse_iterator<_Iterator>& __x, 
	      const reverse_iterator<_Iterator>& __y) 
    { return __y < __x; }

  template<typename _Iterator>
    inline bool 
    operator<=(const reverse_iterator<_Iterator>& __x, 
		const reverse_iterator<_Iterator>& __y) 
    { return !(__y < __x); }

  template<typename _Iterator>
    inline bool 
    operator>=(const reverse_iterator<_Iterator>& __x, 
	       const reverse_iterator<_Iterator>& __y) 
    { return !(__x < __y); }

  template<typename _Iterator>
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator>& __x, 
	      const reverse_iterator<_Iterator>& __y) 
    { return __y.base() - __x.base(); }

  template<typename _Iterator>
    inline reverse_iterator<_Iterator> 
    operator+(typename reverse_iterator<_Iterator>::difference_type __n,
	      const reverse_iterator<_Iterator>& __x) 
    { return reverse_iterator<_Iterator>(__x.base() - __n); }
  //@}

  // 24.4.2.2.1 back_insert_iterator
  /**
   *  These are output iterators, constructed from a container-of-T.
   *  Assigning a T to the iterator appends it to the container using
   *  push_back.
   *
   *  Tip:  Using the back_inserter function to create these iterators can
   *  save typing.
  */
  template<typename _Container>
    class back_insert_iterator 
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;

    public:
      /// A nested typedef for the type of whatever container you used.
      typedef _Container          container_type;
      
      /// The only way to create this %iterator is with a container.
      explicit 
      back_insert_iterator(_Container& __x) : container(&__x) { }

      /**
       *  @param  value  An instance of whatever type
       *                 container_type::const_reference is; presumably a
       *                 reference-to-const T for container<T>.
       *  @return  This %iterator, for chained operations.
       *
       *  This kind of %iterator doesn't really have a "position" in the
       *  container (you can think of the position as being permanently at
       *  the end, if you like).  Assigning a value to the %iterator will
       *  always append the value to the end of the container.
      */
      back_insert_iterator&
      operator=(typename _Container::const_reference __value) 
      { 
	container->push_back(__value);
	return *this;
      }

      /// Simply returns *this.
      back_insert_iterator& 
      operator*() { return *this; }

      /// Simply returns *this.  (This %iterator does not "move".)
      back_insert_iterator& 
      operator++() { return *this; }

      /// Simply returns *this.  (This %iterator does not "move".)
      back_insert_iterator
      operator++(int) { return *this; }
    };

  /**
   *  @param  x  A container of arbitrary type.
   *  @return  An instance of back_insert_iterator working on @p x.
   *
   *  This wrapper function helps in creating back_insert_iterator instances.
   *  Typing the name of the %iterator requires knowing the precise full
   *  type of the container, which can be tedious and impedes generic
   *  programming.  Using this function lets you take advantage of automatic
   *  template parameter deduction, making the compiler match the correct
   *  types for you.
  */
  template<typename _Container>
    inline back_insert_iterator<_Container> 
    back_inserter(_Container& __x) 
    { return back_insert_iterator<_Container>(__x); }

  /**
   *  These are output iterators, constructed from a container-of-T.
   *  Assigning a T to the iterator prepends it to the container using
   *  push_front.
   *
   *  Tip:  Using the front_inserter function to create these iterators can
   *  save typing.
  */
  template<typename _Container>
    class front_insert_iterator 
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;

    public:
      /// A nested typedef for the type of whatever container you used.
      typedef _Container          container_type;

      /// The only way to create this %iterator is with a container.
      explicit front_insert_iterator(_Container& __x) : container(&__x) { }

      /**
       *  @param  value  An instance of whatever type
       *                 container_type::const_reference is; presumably a
       *                 reference-to-const T for container<T>.
       *  @return  This %iterator, for chained operations.
       *
       *  This kind of %iterator doesn't really have a "position" in the
       *  container (you can think of the position as being permanently at
       *  the front, if you like).  Assigning a value to the %iterator will
       *  always prepend the value to the front of the container.
      */
      front_insert_iterator&
      operator=(typename _Container::const_reference __value) 
      { 
	container->push_front(__value);
	return *this;
      }

      /// Simply returns *this.
      front_insert_iterator& 
      operator*() { return *this; }

      /// Simply returns *this.  (This %iterator does not "move".)
      front_insert_iterator& 
      operator++() { return *this; }

      /// Simply returns *this.  (This %iterator does not "move".)
      front_insert_iterator 
      operator++(int) { return *this; }
    };

  /**
   *  @param  x  A container of arbitrary type.
   *  @return  An instance of front_insert_iterator working on @p x.
   *
   *  This wrapper function helps in creating front_insert_iterator instances.
   *  Typing the name of the %iterator requires knowing the precise full
   *  type of the container, which can be tedious and impedes generic
   *  programming.  Using this function lets you take advantage of automatic
   *  template parameter deduction, making the compiler match the correct
   *  types for you.
  */
  template<typename _Container>
    inline front_insert_iterator<_Container> 
    front_inserter(_Container& __x) 
    { return front_insert_iterator<_Container>(__x); }

  /**
   *  These are output iterators, constructed from a container-of-T.
   *  Assigning a T to the iterator inserts it in the container at the
   *  %iterator's position, rather than overwriting the value at that
   *  position.
   *
   *  (Sequences will actually insert a @e copy of the value before the
   *  %iterator's position.)
   *
   *  Tip:  Using the inserter function to create these iterators can
   *  save typing.
  */
  template<typename _Container>
    class insert_iterator 
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
      typename _Container::iterator iter;

    public:
      /// A nested typedef for the type of whatever container you used.
      typedef _Container          container_type;
      
      /**
       *  The only way to create this %iterator is with a container and an
       *  initial position (a normal %iterator into the container).
      */
      insert_iterator(_Container& __x, typename _Container::iterator __i) 
      : container(&__x), iter(__i) {}
   
      /**
       *  @param  value  An instance of whatever type
       *                 container_type::const_reference is; presumably a
       *                 reference-to-const T for container<T>.
       *  @return  This %iterator, for chained operations.
       *
       *  This kind of %iterator maintains its own position in the
       *  container.  Assigning a value to the %iterator will insert the
       *  value into the container at the place before the %iterator.
       *
       *  The position is maintained such that subsequent assignments will
       *  insert values immediately after one another.  For example,
       *  @code
       *     // vector v contains A and Z
       *
       *     insert_iterator i (v, ++v.begin());
       *     i = 1;
       *     i = 2;
       *     i = 3;
       *
       *     // vector v contains A, 1, 2, 3, and Z
       *  @endcode
      */
      insert_iterator&
      operator=(const typename _Container::const_reference __value) 
      { 
	iter = container->insert(iter, __value);
	++iter;
	return *this;
      }

      /// Simply returns *this.
      insert_iterator& 
      operator*() { return *this; }

      /// Simply returns *this.  (This %iterator does not "move".)
      insert_iterator& 
      operator++() { return *this; }

      /// Simply returns *this.  (This %iterator does not "move".)
      insert_iterator& 
      operator++(int) { return *this; }
    };
  
  /**
   *  @param  x  A container of arbitrary type.
   *  @return  An instance of insert_iterator working on @p x.
   *
   *  This wrapper function helps in creating insert_iterator instances.
   *  Typing the name of the %iterator requires knowing the precise full
   *  type of the container, which can be tedious and impedes generic
   *  programming.  Using this function lets you take advantage of automatic
   *  template parameter deduction, making the compiler match the correct
   *  types for you.
  */
  template<typename _Container, typename _Iterator>
    inline insert_iterator<_Container> 
    inserter(_Container& __x, _Iterator __i)
    {
      return insert_iterator<_Container>(__x, 
					 typename _Container::iterator(__i));
    }
} // namespace std

namespace __gnu_cxx
{  
  // This iterator adapter is 'normal' in the sense that it does not
  // change the semantics of any of the operators of its iterator
  // parameter.  Its primary purpose is to convert an iterator that is
  // not a class, e.g. a pointer, into an iterator that is a class.
  // The _Container parameter exists solely so that different containers
  // using this template can instantiate different types, even if the
  // _Iterator parameter is the same.
  using std::iterator_traits;
  using std::iterator;
  template<typename _Iterator, typename _Container>
    class __normal_iterator
      : public iterator<typename iterator_traits<_Iterator>::iterator_category,
                        typename iterator_traits<_Iterator>::value_type,
                        typename iterator_traits<_Iterator>::difference_type,
                        typename iterator_traits<_Iterator>::pointer,
                        typename iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator _M_current;
      
    public:
      typedef typename iterator_traits<_Iterator>::difference_type 	
      							       difference_type;
      typedef typename iterator_traits<_Iterator>::reference   reference;
      typedef typename iterator_traits<_Iterator>::pointer     pointer;

      __normal_iterator() : _M_current(_Iterator()) { }

      explicit 
      __normal_iterator(const _Iterator& __i) : _M_current(__i) { }

      // Allow iterator to const_iterator conversion
      template<typename _Iter>
      inline __normal_iterator(const __normal_iterator<_Iter, _Container>& __i)
	: _M_current(__i.base()) { }

      // Forward iterator requirements
      reference
      operator*() const { return *_M_current; }
      
      pointer
      operator->() const { return _M_current; }
      
      __normal_iterator&
      operator++() { ++_M_current; return *this; }
      
      __normal_iterator
      operator++(int) { return __normal_iterator(_M_current++); }
      
      // Bidirectional iterator requirements
      __normal_iterator&
      operator--() { --_M_current; return *this; }
      
      __normal_iterator
      operator--(int) { return __normal_iterator(_M_current--); }
      
      // Random access iterator requirements
      reference
      operator[](const difference_type& __n) const
      { return _M_current[__n]; }
      
      __normal_iterator&
      operator+=(const difference_type& __n)
      { _M_current += __n; return *this; }

      __normal_iterator
      operator+(const difference_type& __n) const
      { return __normal_iterator(_M_current + __n); }
      
      __normal_iterator&
      operator-=(const difference_type& __n)
      { _M_current -= __n; return *this; }
      
      __normal_iterator
      operator-(const difference_type& __n) const
      { return __normal_iterator(_M_current - __n); }
      
      const _Iterator& 
      base() const { return _M_current; }
    };

  // Note: In what follows, the left- and right-hand-side iterators are
  // allowed to vary in types (conceptually in cv-qualification) so that
  // comparaison between cv-qualified and non-cv-qualified iterators be
  // valid.  However, the greedy and unfriendly operators in std::rel_ops
  // will make overload resolution ambiguous (when in scope) if we don't
  // provide overloads whose operands are of the same type.  Can someone
  // remind me what generic programming is about? -- Gaby
  
  // Forward iterator requirements
  template<typename _IteratorL, typename _IteratorR, typename _Container>
  inline bool
  operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
	     const __normal_iterator<_IteratorR, _Container>& __rhs)
  { return __lhs.base() == __rhs.base(); }

  template<typename _Iterator, typename _Container>
  inline bool
  operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
             const __normal_iterator<_Iterator, _Container>& __rhs)
  { return __lhs.base() == __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
  inline bool
  operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
	     const __normal_iterator<_IteratorR, _Container>& __rhs)
  { return __lhs.base() != __rhs.base(); }

  template<typename _Iterator, typename _Container>
  inline bool
  operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
             const __normal_iterator<_Iterator, _Container>& __rhs)
  { return __lhs.base() != __rhs.base(); }

  // Random access iterator requirements
  template<typename _IteratorL, typename _IteratorR, typename _Container>
  inline bool 
  operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
	    const __normal_iterator<_IteratorR, _Container>& __rhs)
  { return __lhs.base() < __rhs.base(); }

  template<typename _Iterator, typename _Container>
  inline bool
  operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
             const __normal_iterator<_Iterator, _Container>& __rhs)
  { return __lhs.base() < __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
  inline bool
  operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
	    const __normal_iterator<_IteratorR, _Container>& __rhs)
  { return __lhs.base() > __rhs.base(); }

  template<typename _Iterator, typename _Container>
  inline bool
  operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
	    const __normal_iterator<_Iterator, _Container>& __rhs)
  { return __lhs.base() > __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
  inline bool
  operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
	     const __normal_iterator<_IteratorR, _Container>& __rhs)
  { return __lhs.base() <= __rhs.base(); }

  template<typename _Iterator, typename _Container>
  inline bool
  operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
	     const __normal_iterator<_Iterator, _Container>& __rhs)
  { return __lhs.base() <= __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
  inline bool
  operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
	     const __normal_iterator<_IteratorR, _Container>& __rhs)
  { return __lhs.base() >= __rhs.base(); }

  template<typename _Iterator, typename _Container>
  inline bool
  operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
	     const __normal_iterator<_Iterator, _Container>& __rhs)
  { return __lhs.base() >= __rhs.base(); }

  // _GLIBCPP_RESOLVE_LIB_DEFECTS
  // According to the resolution of DR179 not only the various comparison
  // operators but also operator- must accept mixed iterator/const_iterator
  // parameters.
  template<typename _IteratorL, typename _IteratorR, typename _Container>
  inline typename __normal_iterator<_IteratorL, _Container>::difference_type
  operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
	     const __normal_iterator<_IteratorR, _Container>& __rhs)
  { return __lhs.base() - __rhs.base(); }

  template<typename _Iterator, typename _Container>
  inline __normal_iterator<_Iterator, _Container>
  operator+(typename __normal_iterator<_Iterator, _Container>::difference_type __n,
	    const __normal_iterator<_Iterator, _Container>& __i)
  { return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }
} // namespace __gnu_cxx

#endif 

// Local Variables:
// mode:C++
// End:
