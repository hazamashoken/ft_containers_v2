/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:08:00 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 00:56:22 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

// std=c++98

# include <iostream>
# include <string>

# include "iterator.hpp"
# include "utils/algorithm.hpp"
# include "type_traits.hpp"
# include "utils/utility.hpp"

namespace ft
{
	template < class _Tp, class _Alloc = std::allocator<_Tp> >
	class vector
	{
		public:
			typedef _Tp									value_type;
			typedef _Alloc								allocator_type;
			typedef typename _Alloc::size_type			size_type;
			typedef typename _Alloc::difference_type	difference_type;
			typedef typename _Alloc::reference			reference;
			typedef typename _Alloc::const_reference	const_reference;
			typedef typename _Alloc::pointer			pointer;
			typedef typename _Alloc::const_pointer		const_pointer;

		public:
			typedef typename ft::base_iterator<pointer>				iterator;
			typedef typename ft::base_iterator<const_pointer>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			pointer _start;
			pointer _finish;
			pointer _end_of_storage;
			allocator_type _alloc;

			/// @brief allocate memory for n elements
			/// @param __n memory size to be allocated
			/// @return pointer to the allocated memory
			pointer
			_M_allocate(size_type __n )
			{
				return __n != 0 ? _alloc.allocate(__n) : pointer();
			}

			/// @brief deallocate memory
			/// @param __p pointer to the memory to be deallocated
			/// @param __n memory size to be deallocated
			void
			_M_deallocate(pointer __p, size_type __n)
			{
				if (__p)
					_alloc.deallocate(__p, __n);
			}

			/// @brief allocate memory for n elements
			/// @param __n memory size to be allocated
			void
			_M_create_storage(size_type __n)
			{
				this->_start = _M_allocate(__n);
				this->_finish = this->_start;
				this->_end_of_storage = this->_start + __n;
			}

			/// @brief check if memory to be allocated is valid
			/// @param __n memory size to be allocated
			/// @return n if valid, throw length_error if not
			size_type
			_M_check_len(size_type __n)
			{
				if (__n > _M_max_size())
					throw std::length_error("cannot create ft::vector larger than max_size()");
				const size_type __len = size() + (std::max)(size(), __n);
				return (__len < size() || __len > _M_max_size()) ? _M_max_size() : __len;
			}

			/// @brief check if index is valid
			/// @param __n index to be checked
			void
			_M_check_index(size_type __n) const
			{
				if (__n >= size())
					throw std::out_of_range("vector::_M_range_check");
			}

			/// @brief check if memory to be allocated is valid
			/// @return n if valid, throw length_error if not
			size_type
			_M_max_size(const allocator_type& __a = allocator_type()) const
			{
				return __a.max_size();
			}


			/// @brief check if memory to be allocated is valid
			/// @param __n memory size to be allocated
			/// @param _a allocator to be used
			/// @return n if valid, throw length_error if not
			size_type
			_M_check_init_len(size_type __n, const allocator_type& __a = allocator_type())
			{
				if (__n > _M_max_size(__a))
					throw std::length_error("cannot create ft::vector larger than max_size()");
				return __n;
			}

			/// @brief destroy elements in range [first, last)
			/// @param first pointer to the first element to be destroyed
			/// @param last pointer to the last element to be destroyed
			void
			_M_destroy(pointer first, pointer last)
			{
				for (; first != last; ++first)
				{
					_alloc.destroy(first);
				}
			}

			/// @brief allocate and copy elements from range [first, last)
			/// @tparam _ForwardIterator iterator type
			/// @param __n memory size to be allocated
			/// @param __first pointer to the first element to be copied
			/// @param __last pointer to the last element to be copied
			/// @return pointer to the allocated memory
			template <typename _ForwardIterator>
			pointer
			_M_allocate_and_copy(size_type __n, _ForwardIterator __first, _ForwardIterator __last)
			{
				pointer __result = _M_allocate(__n);
				try{
					_M_uninitialized_copy(__first, __last, __result);
					return __result;
				} catch (...)
				{
					_M_deallocate(__result, __n);
					throw;
				}
			}

			/// @brief reallocate memory and copy elements from range [first, last) to the new memory of size __n
			/// @param __n memory size to be allocated
			/// @return pointer to the allocated memory
			pointer
			_M_reallocate(size_type __n)
			{
				pointer __new_start = _M_allocate(_M_check_init_len(__n));
				pointer __new_finish = _M_uninitialized_copy(_start, _finish, __new_start);
				_M_destroy(_start, _finish);
				_M_deallocate(_start, _end_of_storage - _start);
				_start = __new_start;
				_finish = __new_finish;
				_end_of_storage = _start + __n;
				return _start;
			}

			/// @brief reallocate memory and copy elements from range [first, last)
			/// to the new memory of size __n and insert __x at __position relative to the new memory
			/// @param __position iterator to the position to insert __x
			/// @param __x element to be inserted
			void
			_M_realloc_insert(iterator __position, const value_type& __x)
			{
				const size_type __len = _M_check_len_err(1, "vector::_M_realloc_insert");
				pointer __old_start = this->_start;
				pointer __old_finish = this->_finish;
				const size_type __elems_before = __position - begin();
				pointer __new_start(this->_M_allocate(__len));
				pointer __new_finish(__new_start);
				try
				{
					this->_alloc.construct(__new_start + __elems_before, __x);
					__new_finish = _M_uninitialized_copy(__old_start, __position.base(), __new_start);
					++__new_finish;
					__new_finish = _M_uninitialized_copy(__position.base(), __old_finish, __new_finish);

				}
				catch(...)
				{
					_M_destroy(__new_start, __new_finish);
					_M_deallocate(__new_start, __len);
					throw;
				}
				_M_destroy(__old_start, __old_finish);
				_M_deallocate(__old_start, this->_end_of_storage - __old_start);
				this->_start = __new_start;
				this->_finish = __new_finish;
				this->_end_of_storage = __new_start + __len;
			}

			/// @brief fill uninitialized memory with val via construct
			/// @param first pointer to the first element to be filled
			/// @param n number of elements to be filled
			/// @param val value to be filled
			/// @return pointer to the last element filled
			pointer
			_M_uninitialized_fill_n(pointer __position, size_type __n, const value_type& __x)
			{
				pointer cur = __position;
				try
				{
					for (; __n > 0; --__n, ++cur)
						_alloc.construct(cur, __x);
					return cur;
				}
				catch (...)
				{
					_M_destroy(__position, cur);
					throw;
				}
			}

			/// @brief insert n elements with value x at position __position
			/// @param __position position to insert
			/// @param __n number of elements to insert
			/// @param __x value to insert
			void
			_M_fill_insert(iterator __position, size_type __n, const value_type& __x)
			{
				if (__n != 0)
				{
					if (size_type(this->_end_of_storage - this->_finish) >= __n)
					{
						value_type __x_copy = __x;
						const size_type __elems_after = end() - __position;
						pointer __old_finish(this->_finish);
						if (__elems_after > __n)
						{
							_M_uninitialized_copy(this->_finish - __n, this->_finish, this->_finish);
							this->_finish += __n;
							std::copy_backward(__position.base(), __old_finish - __n, __old_finish);
							std::fill(__position.base(), __position.base() + __n, __x_copy);
						}
						else
						{
							this->_finish = _M_uninitialized_fill_n(this->_finish, __n - __elems_after, __x_copy);
							_M_uninitialized_copy(__position, iterator(__old_finish), this->_finish);
							this->_finish += __elems_after;
							std::fill(__position.base(), __old_finish, __x_copy);
						}
					}
					else
					{
						const size_type __len = _M_check_len_err(__n, "vector::_M_fill_insert");
						pointer __new_start = _M_allocate(__len);
						pointer __new_finish = __new_start;
						try
						{
							__new_finish = _M_uninitialized_copy(begin(), __position, __new_start);
							__new_finish= _M_uninitialized_fill_n(__new_finish, __n, __x);
							__new_finish = _M_uninitialized_copy(__position, end(), __new_finish);
						}
						catch(...)
						{
							_M_destroy(__new_start, __new_finish);
							_M_deallocate(__new_start, __len);
							throw;
						}
						_M_destroy(this->_start, this->_finish);
						_M_deallocate(this->_start, this->_end_of_storage - this->_start);
						this->_start = __new_start;
						this->_finish = __new_finish;
						this->_end_of_storage = __new_start + __len;
					}
				}
			}

			/// @brief fill uninitialized memory with val via construct
			/// @param __n number of elements to be filled
			/// @param __x value to be filled
			void
			_M_fill_initialize(size_type __n, const value_type& __x)
			{
				this->_finish =
					_M_uninitialized_fill_n(this->_start, __n, __x);
			}

			/// @brief copy into uninitialized memory via construct
			/// @tparam _InputIterator iterator type
			/// @param __first iterator to the first element to be copied
			/// @param __last iterator to the last element to be copied
			/// @param __result pointer to the first element to be filled
			/// @return pointer to the last element filled
			template <typename _InputIterator>
			pointer
			_M_uninitialized_copy(_InputIterator __first, _InputIterator __last, pointer __result)
			{
				pointer __cur = __result;
				try
				{
					for (; __first != __last; ++__first, ++__cur)
						_alloc.construct(__cur, *__first);
					return __cur;
				}
				catch (...)
				{
					_M_destroy(__result, __cur);
					throw;
				}
			}

			/// @brief fill uninitialized memory with val via construct
			/// @tparam _InputIterator iterator type
			/// @param __first iterator to the first element to be filled
			/// @param __n number of elements to be filled
			/// @param __x value to be filled
			/// @return
			template <typename _InputIterator>
			pointer
			_M_uninitialized_fill_n(_InputIterator __first, size_type __n, const value_type& __x)
			{
				pointer __cur = &(*__first);
				try
				{
					for (; __n > 0; --__n, ++__cur)
						_alloc.construct(__cur, __x);
					return __cur;
				}
				catch (...)
				{
					_M_destroy(&(*__first), __cur);
					throw;
				}
			}

			/// @brief copy elements from [__first, __last) to [__result, __result + (__last - __first))
			/// @param __first iterator to the first element to be copied
			/// @param __last iterator to the last element to be copied
			/// @param __result pointer to the first element to be filled
			/// @return pointer to the last element filled
			pointer
			_M_uninitialized_copy_backward(pointer __first, pointer __last, pointer __result)
			{
				pointer __cur = __result;
				try
				{
					for (; __last != __first; --__last, --__cur)
						_alloc.construct(__cur, *(__last - 1));
					return __result;
				}
				catch (...)
				{
					_M_destroy(__cur, __result);
					throw;
				}
			}


			/// @brief use to initialize elements of size n in the allocated memory
			/// @tparam _InputIterator iterator type
			/// @param __first iterator to the first element to be initialized
			/// @param __last iterator to the last element to be initialized
			/// @param __input_iterator_tag iterator tag
			template <typename _InputIterator>
			void
			_M_range_initialize(_InputIterator __first, _InputIterator __last, std::input_iterator_tag)
			{
				try {
					for (; __first != __last; ++__first)
						push_back(*__first);
				} catch (...) {
					clear();
					throw;
				}
			}

			/// @brief use to initialize elements of size n in the allocated memory
			/// @tparam _ForwardIterator iterator type
			/// @param __first iterator to the first element to be initialized
			/// @param __last iterator to the last element to be initialized
			/// @param __forward_iterator_tag iterator tag
			template <typename _ForwardIterator>
			void
			_M_range_initialize(_ForwardIterator __first, _ForwardIterator __last, std::forward_iterator_tag)
			{
				const size_type __n = std::distance(__first, __last);
				this->_start = _M_allocate(_M_check_init_len(__n, this->_alloc));
				this->_end_of_storage = this->_start + __n;
				this->_finish = _M_uninitialized_copy(__first, __last, this->_start);
			}

			void
			_D_debug()
			{
				std::cout << "\033[1;35m" << "size: " << size() << "\033[0m" << std::endl;
				std::cout << "\033[1;35m" << "capacity: " << capacity() << "\033[0m" << std::endl;
				std::cout << "\033[1;35m" << "start:          " << this->_start << "\033[0m" << std::endl;
				std::cout << "\033[1;35m" << "finish:         " << this->_finish << "\033[0m" << std::endl;
				std::cout << "\033[1;35m" << "size: " << this->_finish - this->_start << "\033[0m" << std::endl;
				std::cout << "\033[1;35m" << "end_of_storage: " << this->_end_of_storage << "\033[0m" << std::endl;
				std::cout << "\033[1;35m" << "vector: " << "\033[0m" << std::endl;
				for (iterator it = begin(); it != end(); ++it)
					std::cout << *it << " ";
				std::cout << std::endl;
				std::cout << "\033[1;35m" << "vector till cap: " << "\033[0m" << std::endl;
				for (iterator it = begin(); it.base() != this->_end_of_storage; ++it)
					std::cout << *it << " ";
				std::cout << std::endl;
				std::cout << std::endl;
			}

			/// @brief fill the vector with n elements of value val
			/// @param __n number of elements to be filled
			/// @param __value value to be filled
			void
			_M_fill_assign(size_type __n, const value_type& __value)
			{
				if (__n <= size())
				{
					std::fill_n(this->_start, __n, __value);
					_M_erase_at_end(this->_start + __n);
				}
				else
				{
					if (__n <= capacity())
					{
						clear();
						std::fill(begin(), end(), __value);
						const size_type __add = __n - size();
						_M_uninitialized_fill_n(end(), __add, __value);
						this->_finish = this->_start + __add;
					}
					else
					{
						clear();
						_M_deallocate(this->_start, capacity());
						pointer __tmp_start = _M_allocate(_M_check_init_len(__n, this->_alloc));
						pointer __tmp_finish = _M_uninitialized_fill_n(__tmp_start, __n, __value);
						this->_start = __tmp_start;
						this->_finish = __tmp_finish;
						this->_end_of_storage = this->_start + __n;
					}
				}
			}

			/// @brief check if the new length of the vector is valid
			/// @param __n length to add to the vector
			/// @param __s error message
			/// @return
			size_type
			_M_check_len_err(size_type __n, const char* __s) const
			{
				if (__n > max_size() - size())
					throw std::length_error(__s);
				const size_type __len = size() + (std::max)(size(), __n);
				return (__len < size() || __len > max_size()) ? max_size() : __len;
			}

			/// @brief insert n elements of value val at position pos
			/// @tparam _InputIterator iterator type
			/// @param __pos position to insert
			/// @param __first first element to insert
			/// @param __last last element to insert
			/// @param iterator_tag iterator tag
			template <typename _InputIterator>
			void
			_M_range_insert(iterator __pos, _InputIterator __first,
				_InputIterator __last, std::input_iterator_tag)
			{
				if (__pos == end())
				{
					for (; __first != __last; ++__first)
						_M_fill_insert(end(), 1, *__first);
				}
				else if (__first != __last)
				{
					vector __tmp(__first, __last, get_allocator());
					insert(__pos, iterator(__tmp.begin()), iterator(__tmp.end()));
				}
			}

			/// @brief insert n elements of value val at position pos
			/// @tparam _ForwardIterator iterator type
			/// @param __position position to insert
			/// @param __first first element to insert
			/// @param __last last element to insert
			/// @param iterator_tag iterator tag
			template <typename _ForwardIterator>
			void
			_M_range_insert(iterator __position, _ForwardIterator __first,
				_ForwardIterator __last, std::forward_iterator_tag)
			{
				if (__first != __last)
				{
					const size_type __n = std::distance(__first, __last);
					if (size_type(this->_end_of_storage - this->_finish) >= __n)
					{
						const size_type __elems_after = end() - __position;
						pointer __old_finish(this->_finish);
						if (__elems_after > __n)
						{
							_M_uninitialized_copy(end() - __n, end(), this->_finish);
							this->_finish += __n;
							std::copy_backward(iterator(__position), iterator(__old_finish - __n), iterator(__old_finish));
							std::copy(__first, __last, __position);
						}
						else
						{
							_ForwardIterator __mid = __first;
							std::advance(__mid, __elems_after);
							_M_uninitialized_copy(__mid, __last, this->_finish);
							this->_finish += __n - __elems_after;
							_M_uninitialized_copy(__position, iterator(__old_finish), this->_finish);
							this->_finish += __elems_after;
							std::copy(__first, __mid, __position);
						}
					}
					else
					{
						const size_type __len = _M_check_len_err(__n, "vector::_M_range_insert");
						pointer __new_start = _M_allocate(__len);
						pointer __new_finish = __new_start;
						try{
							__new_finish = _M_uninitialized_copy(this->_start, __position.base(), __new_start);
							__new_finish = _M_uninitialized_copy(__first, __last, __new_finish);
							__new_finish = _M_uninitialized_copy(__position.base(), this->_finish, __new_finish);
						} catch (...)
						{
							_M_destroy(__new_start, __new_finish);
							_M_deallocate(__new_start, __len);
							throw;
						}
						_M_destroy(this->_start, this->_finish);
						_M_deallocate(this->_start, this->_end_of_storage - this->_start);
						this->_start = __new_start;
						this->_finish = __new_finish;
						this->_end_of_storage = __new_start + __len;
					}
				}

				// if (__first == __last)
				// 	return;
				// const size_type n = std::distance(__first, __last);
				// if (size_type(_end_of_storage - _finish) >= n)
				// {
				// 	reverse_iterator r_old(rbegin());
				// 	reverse_iterator r_new(iterator(_finish + n));
				// 	for (; r_new < rbegin(); ++r_new, ++r_old)
				// 		_alloc.construct(&(*r_new), *r_old);
				// 	for (; r_new < reverse_iterator(__position); ++r_new, ++r_old)
				// 		*r_new = *r_old;
				// 	for (; __first != __last; ++__first, ++__position)
				// 		*__position = *__first;
				// 	_finish = _finish + n;
				// }
				// else
				// {
				// 	const size_type idx = __position - begin();
				// 	_M_reallocate(_M_check_len_err(n, "vector::_M_range_insert"));
				// 	_M_range_insert(begin() + idx, __first, __last,
				// 		ft::__iterator_category(__first));
				// }
			}

			/// @brief assign current vector with a range of elements from a forward iterator
			/// @tparam _ForwardIterator forward iterator type
			/// @param __first first iterator
			/// @param __last last iterator
			/// @param __tag forward iterator tag
			template <typename _ForwardIterator>
			void
			_M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
				std::forward_iterator_tag)
			{
				const size_type __len = std::distance(__first, __last);
				if (__len > capacity())
				{
					_M_check_init_len(__len);
					pointer __tmp = _M_allocate_and_copy(__len, __first, __last);
					_M_destroy(this->_start, this->_finish);
					_M_deallocate(this->_start, this->_end_of_storage - this->_start);
					this->_start = __tmp;
					this->_end_of_storage = this->_start + __len;
					this->_finish = this->_end_of_storage;
				}
				else if (size() >= __len)
				{
					_M_erase_at_end(std::copy(__first, __last, this->_start));
				}
				else
				{
					_ForwardIterator __mid = __first;
					std::advance(__mid, size());
					std::copy(__first, __mid, this->_start);
					this->_finish = _M_uninitialized_copy(__mid, __last, this->_finish);
				}
			}

			/// @brief assign current vector with a range of elements from a input iterator
			/// @tparam _InputIterator input iterator type
			/// @param __first first iterator
			/// @param __last last iterator
			/// @param __tag input iterator tag
			template <typename _InputIterator>
			void
			_M_assign_aux(_InputIterator __first, _InputIterator __last,
				std::input_iterator_tag)
			{
				pointer __cur = this->_start;
				for (; __first != __last && __cur != this->_finish; ++__cur, (void)++__first)
					*__cur = *__first;
				if (__first == __last)
					_M_erase_at_end(__cur);
				else
					_M_range_insert(end(), __first, __last, ft::__iterator_category(__first));
			}

			/// @brief destroy elements from pos to end
			/// @param __pos first element
			void
			_M_erase_at_end(pointer __pos)
			{
				if (this->_finish != __pos)
				{
					_M_destroy(__pos, this->_finish);
					this->_finish = __pos;
				}
			}

			/// @brief insert element at pos
			/// @param __pos position to insert
			/// @param __x element to insert
			void
			_M_insert_aux(iterator __pos, const value_type& __x)
			{
				this->_alloc.construct(this->_finish, *(this->_finish - 1));
				++this->_finish;
				value_type __x_copy = __x;
				std::copy_backward(__pos, iterator(this->_finish - 2), iterator(this->_finish - 1));
				*__pos = __x_copy;
			}

		public:
			/// @brief return allocator type used
			/// @return allocator type used
			allocator_type
			get_allocator() const
			{
				return allocator_type(this->_alloc);
			}

			/// @brief default constructor
			/// @param alloc allocator to be used
			explicit vector(const allocator_type& __a = allocator_type())
				: _start(u_nullptr), _finish(u_nullptr), _end_of_storage(u_nullptr), _alloc(__a)
			{}

			/// @brief fill constructor
			/// @param n number of elements to be filled
			/// @param val value to be filled
			/// @param alloc allocator to be used
			explicit vector(size_type __n, const value_type& __x = value_type(),
				const allocator_type& __a = allocator_type())
				: _start(u_nullptr), _finish(u_nullptr), _end_of_storage(u_nullptr), _alloc(__a)
			{
				_M_create_storage(_M_check_len(__n));
				this->_finish = _M_uninitialized_fill_n(this->_start, __n, __x);
			}

			/// @brief copy constructor
			/// @param __x vector to be copied
			vector(const vector& __x)
				: _alloc(__x.get_allocator())
			{
				_M_create_storage(_M_check_init_len(__x.size()));
				this->_finish = _M_uninitialized_copy(__x.begin(), __x.end(), this->_start);
			}

			/// @brief range constructor
			/// @tparam _InputIterator iterator type
			/// @param __first iterator to the first element to be initialized
			/// @param __last iterator to the last element to be initialized
			/// @param __a allocator to be used
			/// @param __enable_if<!ft::is_integer<_InputIterator>::value>::type* = 0 enable if _InputIterator is not an integer
			template <typename _InputIterator>
			vector(_InputIterator __first, _InputIterator __last,
				const allocator_type& __a = allocator_type(),
				typename ft::enable_if<!ft::is_integral<_InputIterator>::value>::type* = 0)
				: _start(), _finish(), _end_of_storage(), _alloc(__a)
			{
				_M_range_initialize(__first, __last, ft::__iterator_category(__first));
			}

			/// @brief destructor
			~vector()
			{
				_M_destroy(this->_start, this->_finish);
				_M_deallocate(this->_start, capacity());
			}

			/// @brief assign operator
			/// @param __x vector to be copied
			/// @return reference to the vector
			vector&
			operator=(const vector& __x)
			{
				if (&__x != this)
				{
					const size_type __xlen = __x.size();
					if (__xlen > capacity())
					{
						pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
						_M_destroy(this->_start, this->_finish);
						_M_deallocate(this->_start, capacity());
						this->_start = __tmp;
						this->_end_of_storage = this->_start + __xlen;
					}
					else if (size() >= __xlen)
					{
						_M_destroy(std::copy(__x.begin(), __x.end(), begin()).base(), this->_finish);
					}
					else
					{
						std::copy(__x._start, __x._start + size(), this->_start);
						_M_uninitialized_copy(__x._start + size(), __x._finish, this->_finish);
					}
					this->_finish = this->_start + __xlen;
				}
				return *this;
			}

			reference
			operator[](size_type __n)
			{
				return *(this->_start + __n);
			}

			const_reference
			operator[](size_type __n) const
			{
				return *(this->_start + __n);
			}

			/// @brief assign a given value to a vector
			/// @param __n number of elements to be assigned
			/// @param __val value to be assigned
			void
			assign(size_type __n, const value_type& __val)
			{
				_M_fill_assign(__n, __val);
			}

			/// @brief assign a range of values to a vector using an iterator
			/// @tparam _InputIterator iterator type
			/// @param __first iterator to the first element to be assigned
			/// @param __last iterator to the last element to be assigned
			template <class _InputIterator>
			void
			assign(_InputIterator __first, _InputIterator __last,
				typename ft::enable_if<!ft::is_integral<_InputIterator>::value>::type* = 0)
			{
				_M_assign_aux(__first, __last, ft::__iterator_category(__first));
			}

			/// @brief return the iterator to the first element
			/// @return iterator to the first element
			iterator
			begin()
			{
				return iterator(this->_start);
			}

			/// @brief return the const iterator to the first element
			/// @return const iterator to the first element
			const_iterator
			begin() const
			{
				return const_iterator(this->_start);
			}

			/// @brief return the iterator to the last element
			/// @return iterator to the last element
			iterator
			end()
			{
				return iterator(this->_finish);
			}

			/// @brief return the const iterator to the last element
			/// @return const iterator to the last element
			const_iterator
			end() const
			{
				return const_iterator(this->_finish);
			}

			/// @brief return the reverse iterator to the first element
			/// @return reverse iterator to the first element
			reverse_iterator
			rbegin()
			{
				return reverse_iterator(end());
			}

			/// @brief return the const reverse iterator to the first element
			/// @return const reverse iterator to the first element
			const_reverse_iterator
			rbegin() const
			{
				return const_reverse_iterator(end());
			}

			/// @brief return the reverse iterator to the last element
			/// @return reverse iterator to the last element
			reverse_iterator
			rend()
			{
				return reverse_iterator(begin());
			}

			/// @brief return the const reverse iterator to the last element
			/// @return const reverse iterator to the last element
			const_reverse_iterator
			rend() const
			{
				return const_reverse_iterator(begin());
			}

			/// @brief return the size of the vector
			/// @return size of the vector
			size_type
			size() const
			{
				return size_type(this->_finish - this->_start);
			}

			/// @brief return the maximum size of the vector
			/// @return maximum size of the vector
			size_type
			max_size() const
			{
				return _M_max_size();
			}

			/// @brief resize the vector and insert a value to the end of new elements
			/// @param __n new size of the vector
			/// @param __x value to be assigned to the end of new elements
			void
			resize(size_type __n, value_type __x = value_type())
			{
				if (__n > size())
				{
					_M_fill_insert(end(), __n - size(), __x);
				} else if (__n < size())
				{
					_M_erase_at_end(this->_start + __n);
				}
			}

			/// @brief return the capacity of the vector
			/// @return capacity of the vector
			size_type
			capacity() const
			{
				return size_type(this->_end_of_storage - this->_start);
			}

			/// @brief check if the vector is empty
			/// @return true if the vector is empty, false otherwise
			bool
			empty() const
			{
				return begin() == end();
			}

			/// @brief allocate a new memory space and copy the elements to the new space
			/// @param __n size to be reserved
			void
			reserve(size_type __n)
			{
				if (__n > max_size())
				{
					throw std::length_error("vector::reserve");
				}
				if (this->capacity() < __n)
				{
					const size_type __old_size = size();
					pointer __tmp;
					__tmp = _M_allocate_and_copy(__n, iterator(this->_start), iterator(this->_finish));
					_M_destroy(this->_start, this->_finish);
					_M_deallocate(this->_start, capacity());
					this->_start = __tmp;
					this->_finish = __tmp + __old_size;
					this->_end_of_storage = this->_start + __n;
				}
			}

			/// @brief return the reference to the first element
			/// @return reference to the first element
			reference
			front()
			{
				return *begin();
			}

			/// @brief return the const reference to the first element
			/// @return const reference to the first element
			const_reference
			front() const
			{
				return *begin();
			}

			/// @brief return the reference to the last element
			/// @return reference to the last element
			reference
			back()
			{
				return *(end() - 1);
			}

			/// @brief return the const reference to the last element
			/// @return const reference to the last element
			const_reference
			back() const
			{
				return *(end() - 1);
			}

			/// @brief return the pointer to the first element
			/// @return pointer to the first element
			pointer
			data()
			{
				return this->_start;
			}

			/// @brief return the const pointer to the first element
			/// @return	const pointer to the first element
			const_pointer
			data() const
			{
				return this->_start;
			}

			/// @brief check if index is valid then return the reference to the element at the given position
			/// @param __n index of the element
			/// @return reference to the element at the given position
			reference
			at(size_type __n)
			{
				_M_check_index(__n);
				return *(this->_start + __n);
			}

			/// @brief check if index is valid then return the const reference to the element at the given position
			/// @param __n index of the element
			/// @return const reference to the element at the given position
			const_reference
			at(size_type __n) const
			{
				_M_check_index(__n);
				return *(this->_start + __n);
			}

			/// @brief insert a value to the end of the vector
			/// @param __x value to be inserted
			void
			push_back(const value_type& __x)
			{
				if (this->_finish != this->_end_of_storage)
				{
					this->_alloc.construct(this->_finish, __x);
					++this->_finish;
				}
				else
				{
					_M_realloc_insert(end(), __x);
				}
			}

			/// @brief remove the last element
			void
			pop_back()
			{
				--this->_finish;
				this->_alloc.destroy(this->_finish);
			}

			/// @brief insert a value to the given position
			/// @param __pos position to be inserted
			/// @param __x value to be inserted
			/// @return iterator to the inserted element
			iterator
			insert(iterator __pos, const value_type& __x)
			{
				const size_type __elem_before = __pos - begin();
				_M_fill_insert(__pos, 1, __x);
				return begin() + __elem_before;
			}

			/// @brief insert a value to the given position
			/// @param __pos position to be inserted
			/// @param __n number of elements to be inserted
			/// @param __x value to be inserted
			void
			insert(iterator __pos, size_type __n, const value_type& __x)
			{
				_M_fill_insert(__pos, __n, __x);
			}

			/// @brief insert a range of values to the given position from an pair of iterators
			/// @tparam _InputIterator iterator type
			/// @param __pos iterator to the position to be inserted
			/// @param __first iterator to the first element of the range
			/// @param __last iterator to the last element of the range
			/// @param enable_if to enable this function only when _InputIterator is not an integral type
			template <typename _InputIterator>
			void
			insert(iterator __pos, _InputIterator __first, _InputIterator __last,
				typename ft::enable_if<!ft::is_integral<_InputIterator>::value>::type* = 0)
			{
				_M_range_insert(__pos, __first, __last, ft::__iterator_category(__first));
			}

			/// @brief destroy the element at the given position
			/// @param __pos iterator to the element to be destroyed
			/// @return iterator to the next element
			iterator
			erase(iterator __pos)
			{
				if (__pos + 1 != end())
				{
					std::copy(__pos + 1, end(), __pos);
				}
				--this->_finish;
				this->_alloc.destroy(this->_finish);
				return __pos;
			}

			/// @brief destroy the elements in the range from first to last
			/// @param first iterator to the first element to be destroyed
			/// @param last iterator to the last element to be destroyed
			/// @return iterator to the next element of the last element to be destroyed
			iterator
			erase(iterator first, iterator last)
			{
				if (first == last)
					return first;
				iterator __new_finish = std::copy(last, end(), first);
				_M_erase_at_end(__new_finish.base());
				return first;
			}

			/// @brief swap the contents of the vector with another vector
			/// @param __x vector to be swapped with
			void
			swap(vector& __x)
			{
				std::swap(this->_start, __x._start);
				std::swap(this->_finish, __x._finish);
				std::swap(this->_end_of_storage, __x._end_of_storage);
			}

			/// @brief destroy all elements
			void
			clear()
			{
				_M_erase_at_end(this->_start);
			}

	}; // class vector

	/// @brief equality comparison
	/// @tparam _Tp type of the elements
	/// @tparam _Alloc allocator type
	/// @param __x first vector
	/// @param __y second vector
	/// @return true if the two vectors are equal, false otherwise
	template <typename _Tp, typename _Alloc>
	inline bool
	operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{
		return (__x.size() == __y.size()
			&& ft::equal(__x.begin(), __x.end(), __y.begin()));
	}

	/// @brief less than comparison
	/// @tparam _Tp type of the elements
	/// @tparam _Alloc allocator type
	/// @param __x first vector
	/// @param __y second vector
	/// @return true if the two vectors are not equal, false otherwise
	template <typename _Tp, typename _Alloc>
	inline bool
	operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{
		return ft::lexicographical_compare(__x.begin(), __x.end(),
					__y.begin(), __y.end());
	}

	/// @brief inequality comparison
	/// @tparam _Tp type of the elements
	/// @tparam _Alloc allocator type
	/// @param __x first vector
	/// @param __y second vector
	/// @return true if the two vectors are not equal, false otherwise
	template <typename _Tp, typename _Alloc>
	inline bool
	operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{
		return !(__x == __y);
	}

	/// @brief greater than comparison
	/// @tparam _Tp type of the elements
	/// @tparam _Alloc allocator type
	/// @param __x first vector
	/// @param __y second vector
	/// @return true if the first vector is greater than the second vector, false otherwise
	template <typename _Tp, typename _Alloc>
	inline bool
	operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{
		return __y < __x;
	}

	/// @brief less than or equal to comparison
	/// @tparam _Tp type of the elements
	/// @tparam _Alloc allocator type
	/// @param __x first vector
	/// @param __y second vector
	/// @return true if the first vector is less than or equal to the second vector, false otherwise
	template <typename _Tp, typename _Alloc>
	inline bool
	operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{
		return !(__y < __x);
	}

	/// @brief greater than or equal to comparison
	/// @tparam _Tp type of the elements
	/// @tparam _Alloc allocator type
	/// @param __x first vector
	/// @param __y second vector
	/// @return true if the first vector is greater than or equal to the second vector, false otherwise
	template <typename _Tp, typename _Alloc>
	inline bool
	operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{
		return !(__x < __y);
	}

	/// @brief swap the contents of two vectors
	/// @tparam _Tp type of the elements
	/// @tparam _Alloc allocator type
	/// @param __x first vector
	/// @param __y second vector
	template <typename _Tp, typename _Alloc>
	inline void
	swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
	{
		__x.swap(__y);
	}

} // namespace ft

#endif // VECTOR_HPP
