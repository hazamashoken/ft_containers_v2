/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:29:13 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/30 19:01:48 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

// c++std=98

# include <iostream>
# include <sstream>

# include "iterator.hpp"
# include "utils/algorithm.hpp"
# include "utils/type_traits.hpp"
# include "utils/utility.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T 											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

		public:
			typedef typename ft::base_iterator<pointer>				iterator;
			typedef typename ft::base_iterator<const_pointer>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			allocator_type		_alloc;
			pointer				_start;
			pointer				_end;
			pointer				_end_of_storage;

			void	_swap_data(vector& other)
			{
				pointer tmp_start = _start;
				pointer tmp_end = _end;
				pointer tmp_end_of_storage = _end_of_storage;

				_start = other._start;
				_end = other._end;
				_end_of_storage = other._end_of_storage;

				other._start = tmp_start;
				other._end = tmp_end;
				other._end_of_storage = tmp_end_of_storage;
			}

			void	_allocate(size_type n)
			{
				_start = _alloc.allocate(n);
				_end = _start;
				_end_of_storage = _start + n;
			}

			/// @brief fill construct with value (like memset)
			/// @param p pointer to the first element of the new range
			/// @param n number of elements to construct
			/// @param val value to construct with
			/// @return pointer to the last element of the new range
			pointer	_fill_construct(pointer p, size_type n, const_reference val)
			{
				for (size_type i = 0; i < n; ++i, ++p)
					_alloc.construct(p, val);
				return p;
			}

			/// @brief copy construct from range with pointer (memcpy)
			/// @param p pointer to the first element of the new range
			/// @param first pointer to the first element of the old range
			/// @param last pointer to the last element of the old range
			/// @return pointer to the last element of the new range
			pointer _copy_construct(pointer p, const_pointer first, const_pointer last)
			{
				for (; first != last; ++first, ++p)
					_alloc.construct(p, *first);
				return p;
			}

			/// @brief copy construct from range with iterator (memcpy)
			/// @tparam InputIterator  iterator type
			/// @param p pointer to the first element of the new range
			/// @param first iterator to the first element of the old range
			/// @param last iterator to the last element of the old range
			/// @return pointer to the last element of the new range
			template <typename InputIterator>
			pointer _copy_construct(pointer p, InputIterator first, InputIterator last)
			{
				// printf("%p %p\n", first, last);
				for (; first != last; ++first, ++p)
				{
					// printf("%p\n", first);
					_alloc.construct(p, *first);
				}
				return p;
			}

			pointer _copy_backward_construct(pointer p, const_pointer first, const_pointer last)
			{
				// std::cout << "copy backward construct pointer" << std::endl;
				pointer tmp = p;
				--last;
				--tmp;
				// std::cout << "value: " << *(last) << " last: " << last << std::endl;
				for (; first != last + 1; --last, --tmp)
				{
					// std::cout << "value: " << *(last) << " last: " << last << std::endl;
					// std::cout << "copy to " << tmp << std::endl;
					// std::cout << std::endl;
					_alloc.construct(tmp, *(last));
					_alloc.destroy(iterator(last));
				}
				return p;
			}

			template <typename InputIterator>
			pointer _copy_backward_construct(pointer p, InputIterator first, InputIterator last)
			{
				// std::cout << "copy backward construct iterator" << std::endl;
				pointer tmp = p;
				--last;
				--tmp;
				// std::cout << "value: " << *(last) << " last: " << last << std::endl;
				for (; first != last + 1; --last, --tmp)
				{
					// std::cout << "value: " << *(last) << " last: " << last << std::endl;
					// std::cout << "copy to " << tmp << std::endl;
					// std::cout << std::endl;
					_alloc.construct(tmp, *(last));
					_alloc.destroy(last);
				}
				return p;
			}


			void	_deallocate()
			{
				if (_start)
					_alloc.deallocate(_start, _end_of_storage - _start);
			}

			void	_reallocate(size_t n)
			{
				pointer new_start = _alloc.allocate(n);
				pointer new_end = new_start;
				pointer new_end_of_storage = new_start + n;

				new_end = _copy_construct(new_end, _start, _end);
				clear();
				_deallocate();

				_start = new_start;
				_end = new_end;
				_end_of_storage = new_end_of_storage;
			}

			template <typename InputIterator>
			void	_initialize(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				if (!_start && first != last)
					_allocate(1);
				try
				{
					for (;first != last; ++first)
						push_back(*first);
				}
				catch(...)
				{
					clear();
					throw;
				}
			}

			template <typename RandomAccessIterator>
			void	_initialize(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
			{
				const size_type n = last - first;
				_start = _alloc.allocate(_check_init_len(n));
				_end_of_storage = _start + n;
				_end = _copy_construct(_start, first, last);
			}

			void _fill_insert(iterator pos, size_type n, value_type val)
			{
				if (n == 0)
					return ;
				if (n > max_size())
					throw std::length_error("vector::_fill_insert");
				size_type offset = pos - begin();
				// enough space
				if (size_type(_end_of_storage - _end) >= n)
				{
					if (pos.base() < _start + n)
					{
						_copy_backward_construct(_end + n, pos.base(), _end);
						// std::copy_backward(pos.base(), _end, _end + n);
						// std::copy(pos.base(), _end, _end + n);
						_end = _end + n;
						_destroy(pos.base(), pos.base() + n - 1);
						// _fill_construct(pos.base(), n, val);
						_fill_construct(pos.base(), n, val);
					}
					else
					{
						_end = _copy_construct(_start + n, pos.base(), _end);
						_erase_start(pos.base() + 1);
						_fill_construct(pos.base(), n, val);
					}
					// fill the elements after pos with val
				}
				else // not enough space
				{
					size_type new_size = _check_init_len(size() + n);
					pointer new_start = _alloc.allocate(new_size);
					pointer new_end = new_start;
					pointer new_end_of_storage = new_start + new_size;

					if (_start == u_nullptr)
					{
						_start = new_start;
						_end = new_end;
						_end_of_storage = new_end_of_storage;
						_end = _fill_construct(_end, n, val);
						return ;
					}
					new_end = _copy_construct(new_end, _start, _start + offset);
					new_end = _fill_construct(new_end, n, val);
					new_end = _copy_construct(new_end, _start + offset, _end);
					clear();
					_deallocate();

					_start = new_start;
					_end = new_end;
					_end_of_storage = new_end_of_storage;
				}
			}

			template <typename InputIterator>
			size_type _distance(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				size_type n = 0;
				while (first != last)
				{
					++first;
					++n;
				}
				return n;
			}

			template <typename InputIterator>
			void _range_insert(iterator pos, InputIterator first,
				InputIterator last, std::input_iterator_tag)
			{
				for (; first != last; ++first)
				{
					pos = insert(pos, *first);
					++pos;
				}
			}

			template <typename RandomAccessIterator>
			void _range_insert(iterator pos, RandomAccessIterator first,
				RandomAccessIterator last, std::random_access_iterator_tag)
			{
				for (; first != last; ++first)
				{
					pos = insert(pos, *first);
					++pos;
				}
			}

			template <typename InputIterator>
			pointer _copy_construct(pointer dest, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				// std::cout << "copy construct input_iterator_tag" << std::endl;
				// std::cout << "first: " << *first << std::endl;
				// std::cout << "last: " << *last << std::endl;
				for (; first != last; ++first, ++dest)
				{
					// std::cout << "value: " << *first << std::endl;
					_alloc.construct(dest, *first);
				}
				return dest;
			}

			template <typename InputIterator>
			void _assign_aux(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				clear();
				size_type n = std::distance(first, last);
				if (n > capacity())
					_reallocate(n);
				// {
				// 	_end = _copy_construct(_start, first, last, ft::_iterator_category(first));
				// }
				// else
				// {
				// 	_end = _copy_construct(_start, first, last, ft::_iterator_category(first));
				// }
				for (; first != last; ++first)
				{
					push_back(*first);
				}
			}

			template <typename RandomAccessIterator>
			void _assign_aux(RandomAccessIterator first, RandomAccessIterator last,
				std::random_access_iterator_tag)
			{
				clear();
				size_type n = std::distance(first, last);
				if (n > capacity())
					_reallocate(n);
				// {
				// 	_end = _copy_construct(_start, first, last);
				// }
				// else
				// {
				// 	_end = _copy_construct(_start, first, last);
				// }
				for (; first != last; ++first)
				{
					push_back(*first);
				}
			}

			/// @brief erase the elements in the range [pos, end)
			/// @param pos the first element to be erased
			void _erase_end(pointer pos)
			{
				for (iterator it = iterator(pos); it != end(); ++it)
					_alloc.destroy(it.base());
				_end = pos;
			}

			/// @brief erase the elements in the range [begin, pos)
			/// @param pos the last element to be erased
			void _erase_start(pointer pos)
			{
				for (iterator it = begin(); it != iterator(pos); ++it)
					_alloc.destroy(it.base());
			}

			/// @brief destroy the elements in the range [first, last)
			/// @param first the first element to be destroyed
			/// @param last the last element to be destroyed
			void _destroy(pointer first, pointer last)
			{
				for (pointer it = first; it != last; ++it)
					_alloc.destroy(it);
			}

			/// @brief destroy the elements in the range [first, last)
			/// @tparam InputIterator the type of the iterator
			/// @param first the first element to be destroyed
			/// @param last the last element to be destroyed
			template <typename InputIterator>
			void _destory(InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
					_alloc.destroy(&(*first));
			}

			size_type _max_size() const
			{
				return _alloc.max_size();
			}

			size_type _check_init_len(size_type n) const
			{
				if (n > _max_size())
					throw std::length_error("vector::_check_init_len");
				return n;
			}

			size_type _check_insert_len(size_type n, const char *msg) const
			{
				if (n > _max_size() - size())
					throw std::length_error(msg);
				const size_type len = size() + std::max(size(), n);
				return len < size() || len > _max_size() ? _max_size() : len;
			}

			void _check_index(size_type n) const
			{
				if (n >= size())
				{
					std::stringstream ss;
					ss << "vector::_check_index: n (which is " << n << ") >= this->size() (which is " << size() << ")";
					throw std::out_of_range(ss.str());
				}
			}

		public:
			allocator_type get_allocator() const
			{
				return allocator_type(_alloc);
			}

			explicit vector(const allocator_type& alloc = allocator_type())
				:  _alloc(alloc), _start(u_nullptr), _end(u_nullptr), _end_of_storage(u_nullptr) {}

			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _start(u_nullptr), _end(u_nullptr), _end_of_storage(u_nullptr)
			{
				_allocate(_check_init_len(n));
				_end = _fill_construct(_end, n, val);

			}

			vector(const vector& other) : _alloc(other.get_allocator())
			{
				_allocate(_check_init_len(other.size()));
				_end = _copy_construct(_end, other._start, other._end);
			}

			template <typename InputIterator>
			vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				: _alloc(alloc), _start(), _end(), _end_of_storage()
			{
				_initialize(first, last, ft::_iterator_category(first));
			}

			~vector()
			{
				clear();
				_deallocate();
			}

			vector& operator=(const vector& other)
			{
				clear();
				_deallocate();
				_allocate(_check_init_len(other.size()));
				_end = _copy_construct(_end, other._start, other._end);
				return *this;
			}

			iterator begin()
			{
				return iterator(_start);
			}

			const_iterator begin() const
			{
				return const_iterator(_start);
			}

			iterator end()
			{
				return iterator(_end);
			}

			const_iterator end() const
			{
				return const_iterator(_end);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			size_type size() const
			{
				return size_type(_end - _start);
			}

			size_type max_size() const
			{
				return _max_size();
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n < size())
				{
					_erase_end(_start + n);
				}
				else if (n > size())
				{
					if (n > capacity())
						_reallocate(_check_init_len(n));
					_end = _fill_construct(_end, n - size(), val);
				}
			}

			size_type capacity() const
			{
				return size_type(_end_of_storage - _start);
			}

			bool empty() const
			{
				return begin() == end();
			}

			void reserve(size_type n)
			{
				if (n > capacity())
					_reallocate(_check_init_len(n));
			}

			reference operator[](size_type n)
			{
				return *(_start + n);
			}

			const_reference operator[](size_type n) const
			{
				return *(_start + n);
			}

			reference at(size_type n)
			{
				_check_index(n);
				return *(_start + n);
			}

			const_reference at(size_type n) const
			{
				_check_index(n);
				return *(_start + n);
			}

			reference front()
			{
				return *_start;
			}

			const_reference front() const
			{
				return *_start;
			}

			reference back()
			{
				return *(_end - 1);
			}

			const_reference back() const
			{
				return *(_end - 1);
			}

			pointer data(void)
			{
				return _start;
			}

			const_pointer data(void) const
			{
				return _start;
			}

			template <typename InputIterator>
			void assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				// std::cout << "assign(InputIterator first, InputIterator last)" << std::endl;
				// std::cout << "first = " << *first << std::endl;
				clear();
				for (; first != last; ++first)
					push_back(*first);
				// _assign_aux(first, last, ft::_iterator_category(first));
			}

			void assign(size_type n, const value_type& val)
			{
				clear();
				if (n <= capacity()) // if to assign less or equal to current capacity()
					_end = _fill_construct(_start, n, val);
				else // if to assign more than current capacity()
				{
					_deallocate();
					_allocate(_check_init_len(n));
					_end = _fill_construct(_start, n, val);
				}
			}


			void push_back(const value_type& val)
			{
				if (size() < capacity())
				{
					_alloc.construct(_end, val);
					++_end;
				}
				else
				{
					_reallocate(_check_insert_len(1, "vector::push_back"));
					_alloc.construct(_end, val);
					++_end;
				}
			}

			void pop_back()
			{
				_alloc.destroy(--_end);
			}

			iterator insert(iterator pos, const value_type& val)
			{
				const size_type offset = pos - begin();
				// std::cout << "offset: " << offset << std::endl;
				_fill_insert(pos, 1, val);
				// std::cout << *begin() << std::endl;
				return iterator(_start + offset);
			}

			void insert(iterator pos, size_type n, const value_type& val)
			{
				_fill_insert(pos, n, val);
			}

			template <typename InputIterator>
			void insert(iterator pos, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				// std::cout << "first: " << *first << std::endl;
				// std::cout << "last: " << *last << std::endl;

				// std::cout << "insert(iterator pos, InputIterator first, InputIterator last)" << std::endl;
				_range_insert(pos, first, last, ft::_iterator_category(first));
				// size_type n = std::distance(first, last);
				// if (n == 0)
				// 	return ;
				// std::cout << "n: " << n << std::endl;
				// if (n + size() > capacity())
				// {
				// 	std::cout << "n + size() > capacity()" << std::endl;
				// 	size_type new_size = _check_init_len(size() + n);
				// 	pointer new_start = _alloc.allocate(new_size);
				// 	pointer new_end = new_start;
				// 	pointer new_end_of_storage = new_start + new_size;

				// 	if (_start == u_nullptr)
				// 	{
				// 		_start = new_start;
				// 		_end = new_end;
				// 		_end_of_storage = new_end_of_storage;
				// 		// _end = _copy_construct(_end, first, last);
				// 		pointer new_end = _end;
				// 		for (; first != last; ++first, ++new_end)
				// 		{
				// 			std::cout << "value: " << *first << std::endl;
				// 			_alloc.construct(new_end, *first);
				// 		}
				// 		_end = new_end;
				// 		return ;
				// 	}
				// 	new_end = _copy_construct(new_end, _start, pos.base());
				// 	// new_end = _copy_construct(new_end, first, last);
				// 	for (; first != last; ++first, ++new_end)
				// 	{
				// 		// std::cout << "value: " << *first << std::endl;
				// 		_alloc.construct(new_end, *first);
				// 	}
				// 	new_end = _copy_construct(new_end, pos.base(), _end);
				// 	clear();
				// 	_deallocate();

				// 	_start = new_start;
				// 	_end = new_end;
				// 	_end_of_storage = new_end_of_storage;
				// }
				// else
				// {
				// 	std::cout << "else" << std::endl;
				// 	_end = _copy_construct(_end + n, _end - n, _end);
				// 	// _copy_construct(_end - n, first, last);
				// 	pointer new_end = _end + n;
				// 	for (; first != last; ++first, ++new_end)
				// 	{
				// 		std::cout << "value: " << *first << std::endl;
				// 		_alloc.construct(new_end, *first);
				// 	}
				// 	_end = new_end;
				// }
			}

			iterator erase(iterator pos)
			{
				if (pos + 1 != end())
					std::copy(pos + 1, end(), pos);
				_alloc.destroy(--_end);
				return pos;
			}

			iterator erase(iterator first, iterator last)
			{
				if (first == last)
					return first;
				iterator it = std::copy(last, end(), first);
				_erase_end(it.base());
				return first;
			}

			void swap(vector& other)
			{
				std::swap(_alloc, other._alloc);
				std::swap(_start, other._start);
				std::swap(_end, other._end);
				std::swap(_end_of_storage, other._end_of_storage);
			}

			void clear()
			{
				_erase_end(_start);
			}
	};

	template <typename T, typename Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T, typename Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, typename Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T, typename Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif // VECTOR_HPP
