/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:43:34 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 00:02:08 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <cstddef>
# include <memory>
# include <functional>
# include "../type_traits.hpp"
# include "../utils/pair.hpp"
# include "../utils/algorithm.hpp"
# include "../iterator.hpp"

namespace ft
{
	enum _Rb_tree_color { _S_red = false, _S_black = true };

	/// @brief the node of the tree
	/// @link https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
	struct _Rb_tree_node_base
	{
		typedef _Rb_tree_node_base* _Base_ptr;
		typedef const _Rb_tree_node_base* _Const_Base_ptr;

		_Rb_tree_color		_M_color;
		_Base_ptr			_M_parent;
		_Base_ptr			_M_left;
		_Base_ptr			_M_right;

		/// @brief return the pointer to the minimum node of the tree (most left node)
		/// @param __x the root of the tree
		/// @return the minimum node of the tree
		static _Base_ptr
		_S_minimum(_Base_ptr __x)
		{
			while (__x->_M_left != 0)
				__x = __x->_M_left;
			return __x;
		}

		/// @brief return the const pointer to the minimum node of the tree (most left node)
		/// @param __x the root of the tree
		/// @return the minimum node of the tree
		static _Const_Base_ptr
		_S_minimum(_Const_Base_ptr __x)
		{
			while (__x->_M_left != 0)
				__x = __x->_M_left;
			return __x;
		}

		/// @brief return the pointer to the maximum node of the tree (most right node)
		/// @param __x the root of the tree
		/// @return the maximum node of the tree
		static _Base_ptr
		_S_maximum(_Base_ptr __x)
		{
			while (__x->_M_right != 0)
				__x = __x->_M_right;
			return __x;
		}

		/// @brief return the const pointer to the maximum node of the tree (most right node)
		/// @param __x the root of the tree
		/// @return the maximum node of the tree
		static _Const_Base_ptr
		_S_maximum(_Const_Base_ptr __x)
		{
			while (__x->_M_right != 0)
				__x = __x->_M_right;
			return __x;
		}

		/// @brief return the pointer to the next node of the tree
		/// @param __x the node to find the next node
		/// @return the next node of the tree
		static _Rb_tree_node_base*
		_S_Rb_tree_increment(_Rb_tree_node_base* __x)
		{
			if (__x->_M_right != 0)
			{
				__x = __x->_M_right;
				while (__x->_M_left != 0)
					__x = __x->_M_left;
			}
			else
			{
				_Rb_tree_node_base* __y = __x->_M_parent;
				while (__x == __y->_M_right)
				{
					__x = __y;
					__y = __y->_M_parent;
				}
				if (__x->_M_right != __y)
					__x = __y;
			}
			return __x;
		}

		/// @brief return the const pointer to the next node of the tree
		/// @param __x the node to find the next node
		/// @return the next node of the tree
		static const _Rb_tree_node_base*
		_S_Rb_tree_increment(const _Rb_tree_node_base* __x)
		{
			return _S_Rb_tree_increment(const_cast<_Rb_tree_node_base*>(__x));
		}

		/// @brief return the pointer to the previous node of the tree
		/// @param __x the node to find the previous node
		/// @return the previous node of the tree
		static _Rb_tree_node_base*
		_S_Rb_tree_decrement(_Rb_tree_node_base* __x)
		{
			if (__x->_M_color == _S_red
				&& __x->_M_parent->_M_parent == __x)
				__x = __x->_M_right;
			else if (__x->_M_left != 0)
			{
				_Rb_tree_node_base* __y = __x->_M_left;
				while (__y->_M_right != 0)
					__y = __y->_M_right;
				__x = __y;
			}
			else
			{
				_Rb_tree_node_base* __y = __x->_M_parent;
				while (__x == __y->_M_left)
				{
					__x = __y;
					__y = __y->_M_parent;
				}
				__x = __y;
			}
			return __x;
		}

		/// @brief return the const pointer to the previous node of the tree
		/// @param __x the node to find the previous node
		/// @return the previous node of the tree
		static const _Rb_tree_node_base*
		_S_Rb_tree_decrement(const _Rb_tree_node_base* __x)
		{
			return _S_Rb_tree_decrement(const_cast<_Rb_tree_node_base*>(__x));
		}

		/// @brief rotate the tree to the right
		/// @param __x the node to rotate
		/// @param __root the root of the tree
		/// @return the new root of the tree
		static _Rb_tree_node_base*
		_S_Rb_tree_rotate_left(_Rb_tree_node_base* const __x,
			_Rb_tree_node_base*& __root)
		{
			_Rb_tree_node_base* const __y = __x->_M_right;

			__x->_M_right = __y->_M_left;
			if (__y->_M_left != 0)
				__y->_M_left->_M_parent = __x;
			__y->_M_parent = __x->_M_parent;

			if (__x == __root)
				__root = __y;
			else if (__x == __x->_M_parent->_M_left)
				__x->_M_parent->_M_left = __y;
			else
				__x->_M_parent->_M_right = __y;
			__y->_M_left = __x;
			__x->_M_parent = __y;
			return __y;
		}

		/// @brief rotate the tree to the left
		/// @param __x the node to rotate
		/// @param __root the root of the tree
		/// @return the new root of the tree
		static _Rb_tree_node_base*
		_S_Rb_tree_rotate_right(_Rb_tree_node_base* const __x,
			_Rb_tree_node_base*& __root)
		{
			_Rb_tree_node_base* const __y = __x->_M_left;

			__x->_M_left = __y->_M_right;
			if (__y->_M_right != 0)
				__y->_M_right->_M_parent = __x;
			__y->_M_parent = __x->_M_parent;

			if (__x == __root)
				__root = __y;
			else if (__x == __x->_M_parent->_M_right)
				__x->_M_parent->_M_right = __y;
			else
				__x->_M_parent->_M_left = __y;
			__y->_M_right = __x;
			__x->_M_parent = __y;
			return __y;
		}

		static void
		_S_Rb_tree_insert_and_rebalance(const bool __insert_left,
										_Rb_tree_node_base* __x,
										_Rb_tree_node_base* __p,
										_Rb_tree_node_base& __header)
		{
			_Rb_tree_node_base *& __root = __header._M_parent;

			__x->_M_parent = __p;
			__x->_M_left = 0;
			__x->_M_right = 0;
			__x->_M_color = _S_red;

			if (__insert_left)
			{
				__p->_M_left = __x;
				if (__p == &__header)
				{
					__header._M_parent = __x;
					__header._M_right = __x;
				}
				else if (__p == __header._M_left)
					__header._M_left = __x;
			}
			else
			{
				__p->_M_right = __x;
				if (__p == __header._M_right)
					__header._M_right = __x;
			}

			while (__x != __root
					&& __x->_M_parent->_M_color == _S_red)
			{
				_Rb_tree_node_base* const __xpp = __x->_M_parent->_M_parent;

				if (__x->_M_parent == __xpp->_M_left)
				{
					_Rb_tree_node_base* const __y = __xpp->_M_right;
					if (__y && __y->_M_color == _S_red)
					{
						__x->_M_parent->_M_color = _S_black;
						__y->_M_color = _S_black;
						__xpp->_M_color = _S_red;
						__x = __xpp;
					}
					else
					{
						if (__x == __x->_M_parent->_M_right)
						{
							__x = __x->_M_parent;
							_S_Rb_tree_rotate_left(__x, __root);
						}
						__x->_M_parent->_M_color = _S_black;
						__xpp->_M_color = _S_red;
						_S_Rb_tree_rotate_right(__xpp, __root);
					}
				}
				else
				{
					_Rb_tree_node_base* const __y = __xpp->_M_left;
					if (__y && __y->_M_color == _S_red)
					{
						__x->_M_parent->_M_color = _S_black;
						__y->_M_color = _S_black;
						__xpp->_M_color = _S_red;
						__x = __xpp;
					}
					else
					{
						if (__x == __x->_M_parent->_M_left)
						{
							__x = __x->_M_parent;
							_S_Rb_tree_rotate_right(__x, __root);
						}
						__x->_M_parent->_M_color = _S_black;
						__xpp->_M_color = _S_red;
						_S_Rb_tree_rotate_left(__xpp, __root);
					}
				}
			}
			__root->_M_color = _S_black;
		}

		static _Rb_tree_node_base*
		_S_Rb_tree_rebalance_for_erase(_Rb_tree_node_base* const __z,
										_Rb_tree_node_base& __header)
		{
			_Rb_tree_node_base *& __root = __header._M_parent;
			_Rb_tree_node_base *& __leftmost = __header._M_left;
			_Rb_tree_node_base *& __rightmost = __header._M_right;
			_Rb_tree_node_base* __y = __z;
			_Rb_tree_node_base* __x = 0;
			_Rb_tree_node_base* __x_parent = 0;
			if (__y->_M_left == 0) /// __y left child is null.
				__x = __y->_M_right; ///
			else if (__y->_M_right == 0) /// __y right child is null.
				__x = __y->_M_left;
			else /// __y both child are null
			{
				__y = __y->_M_right;
				while (__y->_M_left != 0)
					__y = __y->_M_left;
				__x = __y->_M_right;
			}
			if (__y != __z)
			{
				__z->_M_left->_M_parent = __y;
				__y->_M_left = __z->_M_left;
				if (__y != __z->_M_right)
				{
					__x_parent = __y->_M_parent;
					if (__x)
						__x->_M_parent = __y->_M_parent;
					__y->_M_parent->_M_left = __x;
					__y->_M_right = __z->_M_right;
					__z->_M_right->_M_parent = __y;
				}
				else
					__x_parent = __y;
				if (__root == __z)
					__root = __y;
				else if (__z->_M_parent->_M_left == __z)
					__z->_M_parent->_M_left = __y;
				else
					__z->_M_parent->_M_right = __y;
				__y->_M_parent = __z->_M_parent;
				std::swap(__y->_M_color, __z->_M_color);
				__y = __z;
			}
			else
			{
				__x_parent = __y->_M_parent;
				if (__x)
					__x->_M_parent = __y->_M_parent;
				if (__root == __z)
					__root = __x;
				else if (__z->_M_parent->_M_left == __z)
					__z->_M_parent->_M_left = __x;
				else
					__z->_M_parent->_M_right = __x;
				if (__leftmost == __z)
				{
					if (__z->_M_right == 0)
						__leftmost = __z->_M_parent;
					else
						__leftmost = _Rb_tree_node_base::_S_minimum(__x);
				}
				if (__rightmost == __z)
				{
					if (__z->_M_left == 0)
						__rightmost = __z->_M_parent;
					else
						__rightmost = _Rb_tree_node_base::_S_maximum(__x);
				}
			}
			if (__y->_M_color != _S_red)
			{
				while (__x != __root && (__x == 0 || __x->_M_color == _S_black))
					if (__x == __x_parent->_M_left)
					{
						_Rb_tree_node_base* __w = __x_parent->_M_right;
						if (__w->_M_color == _S_red)
						{
							__w->_M_color = _S_black;
							__x_parent->_M_color = _S_red;
							_S_Rb_tree_rotate_left(__x_parent, __root);
							__w = __x_parent->_M_right;
						}
						if ((__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)
							&& (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black))
						{
							__w->_M_color = _S_red;
							__x = __x_parent;
							__x_parent = __x_parent->_M_parent;
						}
						else
						{
							if (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black)
							{
								if (__w->_M_left)
									__w->_M_left->_M_color = _S_black;
								__w->_M_color = _S_red;
								_S_Rb_tree_rotate_right(__w, __root);
								__w = __x_parent->_M_right;
							}
							__w->_M_color = __x_parent->_M_color;
							__x_parent->_M_color = _S_black;
							if (__w->_M_right)
								__w->_M_right->_M_color = _S_black;
							_S_Rb_tree_rotate_left(__x_parent, __root);
							break;
						}
					}
					else
					{
						_Rb_tree_node_base* __w = __x_parent->_M_left;
						if (__w->_M_color == _S_red)
						{
							__w->_M_color = _S_black;
							__x_parent->_M_color = _S_red;
							_S_Rb_tree_rotate_right(__x_parent, __root);
							__w = __x_parent->_M_left;
						}
						if ((__w->_M_right == 0 || __w->_M_right->_M_color == _S_black)
							&& (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black))
						{
							__w->_M_color = _S_red;
							__x = __x_parent;
							__x_parent = __x_parent->_M_parent;
						}
						else
						{
							if (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)
							{
								if (__w->_M_right)
									__w->_M_right->_M_color = _S_black;
								__w->_M_color = _S_red;
								_S_Rb_tree_rotate_left(__w, __root);
								__w = __x_parent->_M_left;
							}
							__w->_M_color = __x_parent->_M_color;
							__x_parent->_M_color = _S_black;
							if (__w->_M_left)
								__w->_M_left->_M_color = _S_black;
							_S_Rb_tree_rotate_right(__x_parent, __root);
							break;
						}
					}
				if (__x)
					__x->_M_color = _S_black;
			}
			return __y;
		}

		unsigned int
		_Rb_tree_black_count(const _Rb_tree_node_base* __node,
							const _Rb_tree_node_base* __root)
		{
			if (__node == 0)
				return 0;
			unsigned int __sum = 0;
			do
			{
				if (__node->_M_color == _S_black)
					++__sum;
				if (__node == __root)
					break;
				__node = __node->_M_parent;
			} while (true);
			return __sum;
		}
	}; // struct _Rb_tree_node_base

	template <typename _Key_compare>
	struct _Rb_tree_key_compare
	{
		_Key_compare _M_key_compare;

		_Rb_tree_key_compare()
			: _M_key_compare()
		{}

		_Rb_tree_key_compare(const _Key_compare& __comp)
			: _M_key_compare(__comp)
		{}

	}; // struct _Rb_tree_key_compare

	struct _Rb_tree_header
	{
		_Rb_tree_node_base _M_header;
		std::size_t _M_node_count;

		_Rb_tree_header()
		{
			_M_header._M_color = _S_red;
			_M_reset();
		}

		void
		_M_move_data(_Rb_tree_header& __from)
		{
			_M_header._M_color = __from._M_header._M_color;
			_M_header._M_parent = __from._M_header._M_parent;
			_M_header._M_left = __from._M_header._M_left;
			_M_header._M_right = __from._M_header._M_right;
			_M_header._M_parent->_M_parent = &_M_header;
			_M_node_count = __from._M_node_count;

			__from._M_reset();
		}

		void
		_M_reset()
		{
			_M_header._M_parent = 0;
			_M_header._M_left = &_M_header;
			_M_header._M_right = &_M_header;
			_M_node_count = 0;
		}
	}; // struct _Rb_tree_header

	template <typename _Val>
	struct _Rb_tree_node : public _Rb_tree_node_base
	{
		typedef _Rb_tree_node<_Val>* _Link_type;
		_Val _M_value_field;

		_Val*
		_M_valptr()
		{
			return &_M_value_field;
		}

		const _Val*
		_M_valptr() const
		{
			return &_M_value_field;
		}


	}; // struct _Rb_tree_node

	_Rb_tree_node_base*
	_Rb_tree_increment(_Rb_tree_node_base* __x)
	{
		return _Rb_tree_node_base::_S_Rb_tree_increment(__x);
	}

	const _Rb_tree_node_base*
	_Rb_tree_increment(const _Rb_tree_node_base* __x)
	{
		return _Rb_tree_node_base::_S_Rb_tree_increment(__x);
	}

	_Rb_tree_node_base*
	_Rb_tree_decrement(_Rb_tree_node_base* __x)
	{
		return _Rb_tree_node_base::_S_Rb_tree_decrement(__x);
	}

	const _Rb_tree_node_base*
	_Rb_tree_decrement(const _Rb_tree_node_base* __x)
	{
		return _Rb_tree_node_base::_S_Rb_tree_decrement(__x);
	}

	void
	_Rb_tree_insert_and_rebalance(const bool __insert_left,
								_Rb_tree_node_base* __x,
								_Rb_tree_node_base* __p,
								_Rb_tree_node_base& __header)
	{
		return _Rb_tree_node_base::_S_Rb_tree_insert_and_rebalance(__insert_left,
																__x,
																__p,
																__header);
	}

	_Rb_tree_node_base*
	_Rb_tree_rebalance_for_erase(_Rb_tree_node_base* const __z,
								_Rb_tree_node_base& __header)
	{
		return _Rb_tree_node_base::_S_Rb_tree_rebalance_for_erase(__z,
																__header);
	}

	template <typename _Tp>
	struct _Rb_tree_iterator
	{
		typedef _Tp		value_type;
		typedef _Tp&	reference;
		typedef _Tp*	pointer;

		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		typedef _Rb_tree_iterator<_Tp>			_Self;
		typedef _Rb_tree_node_base::_Base_ptr	_Base_ptr;
		typedef _Rb_tree_node<_Tp>*				_Link_type;

		_Rb_tree_iterator()
			: _M_node()
		{}

		explicit
		_Rb_tree_iterator(_Base_ptr __x)
			: _M_node(__x)
		{}

		reference
		operator*() const
		{
			return *static_cast<_Link_type>(_M_node)->_M_valptr();
		}

		pointer
		operator->() const
		{
			return static_cast<_Link_type>(_M_node)->_M_valptr();
		}

		_Self&
		operator++()
		{
			_M_node = _Rb_tree_increment(_M_node);
			return *this;
		}

		_Self
		operator++(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_increment(_M_node);
			return __tmp;
		}

		_Self&
		operator--()
		{
			_M_node = _Rb_tree_decrement(_M_node);
			return *this;
		}

		_Self
		operator--(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_decrement(_M_node);
			return __tmp;
		}

		friend bool
		operator==(const _Self& __x, const _Self& __y)
		{
			return __x._M_node == __y._M_node;
		}

		friend bool
		operator!=(const _Self& __x, const _Self& __y)
		{
			return __x._M_node != __y._M_node;
		}

		_Base_ptr _M_node;
	}; // struct _Rb_tree_iterator

	template <typename _Tp>
	struct _Rb_tree_const_iterator
	{
		typedef _Tp			value_type;
		typedef const _Tp&	reference;
		typedef const _Tp*	pointer;

		typedef _Rb_tree_iterator<_Tp> iterator;

		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		typedef _Rb_tree_const_iterator<_Tp>		_Self;
		typedef _Rb_tree_node_base::_Const_Base_ptr	_Base_ptr;
		typedef const _Rb_tree_node<_Tp>*			_Link_type;

		_Rb_tree_const_iterator()
			: _M_node()
		{}

		explicit
		_Rb_tree_const_iterator(_Base_ptr __x)
			: _M_node(__x)
		{}

		_Rb_tree_const_iterator(const iterator& __it)
			: _M_node(__it._M_node)
		{}

		iterator
		_M_const_cast()
		{
			return iterator(const_cast<typename iterator::_Base_ptr>(_M_node));
		}

		reference
		operator*() const
		{
			return *static_cast<_Link_type>(_M_node)->_M_valptr();
		}

		pointer
		operator->() const
		{
			return static_cast<_Link_type>(_M_node)->_M_valptr();
		}

		_Self&
		operator++()
		{
			_M_node = _Rb_tree_increment(_M_node);
			return *this;
		}

		_Self
		operator++(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_increment(_M_node);
			return __tmp;
		}

		_Self&
		operator--()
		{
			_M_node = _Rb_tree_decrement(_M_node);
			return *this;
		}

		_Self
		operator--(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_decrement(_M_node);
			return __tmp;
		}

		friend bool
		operator==(const _Self& __x, const _Self& __y)
		{
			return __x._M_node == __y._M_node;
		}

		friend bool
		operator!=(const _Self& __x, const _Self& __y)
		{
			return __x._M_node != __y._M_node;
		}

		_Base_ptr _M_node;
	}; // struct _Rb_tree_const_iterator

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc = std::allocator<_Val> >
	class _Rb_tree
	{
		typedef typename _Alloc::template rebind<_Rb_tree_node<_Val> >::other
			_Node_allocator;

		protected:
			typedef _Rb_tree_node_base*	_Base_ptr;
			typedef const _Rb_tree_node_base*	_Const_Base_ptr;

			typedef _Rb_tree_node<_Val>*	_Link_type;
			typedef const _Rb_tree_node<_Val>*	_Const_Link_type;

		private:
			struct _Reuse_or_alloc_node
			{
				_Reuse_or_alloc_node(_Rb_tree& __t)
				: _M_root(__t._M_root()), _M_nodes(__t._M_rightmost()), _M_t(__t)
				{
					if (_M_root)
					{
						_M_root->_M_parent = 0;

						if (_M_nodes->_M_left)
							_M_nodes = _M_nodes->_M_left;
					}
					else
						_M_nodes = 0;
				}

				~_Reuse_or_alloc_node()
				{
					_M_t._M_erase(static_cast<_Link_type>(_M_root));
				}

				template <typename _Arg>
				_Link_type
				operator()(const _Arg& __arg)
				{
					_Link_type __node = static_cast<_Link_type>(_M_extract());
					if (__node)
					{
						_M_t._M_destroy_node(__node);
						_M_t._M_construct_node(__node, __arg);
						return __node;
					}
					return _M_t._M_create_node(__arg);
				}

				private:
					_Base_ptr
					_M_extract()
					{
						if (!_M_nodes)
							return _M_nodes;

						_Base_ptr __node = _M_nodes;
						_M_nodes = _M_nodes->_M_parent;
						if (_M_nodes)
						{
							if (_M_nodes->_M_right == __node)
							{
								_M_nodes->_M_right = 0;
								if (_M_nodes->_M_left)
								{
									_M_nodes = _M_nodes->_M_left;
									while (_M_nodes->_M_right)
										_M_nodes = _M_nodes->_M_right;

									if (_M_nodes->_M_left)
										_M_nodes = _M_nodes->_M_left;
								}
							}
							else
								_M_nodes->_M_left = 0;
						}
						else
							_M_root = 0;
						return __node;
					}

					_Base_ptr _M_root;
					_Base_ptr _M_nodes;
					_Rb_tree& _M_t;
			}; // struct _Reuse_or_alloc_node

			struct _Alloc_node
			{
				_Alloc_node(_Rb_tree& __t)
				: _M_t(__t)
				{}

				template <typename _Arg>
				_Link_type
				operator()(const _Arg& __arg)
				{
					return _M_t._M_create_node(__arg);
				}

				private:
					_Rb_tree& _M_t;
			}; // struct _Alloc_node

		public:
			typedef _Key			key_type;
			typedef _Val			value_type;
			typedef value_type*		pointer;
			typedef const value_type*	const_pointer;
			typedef value_type&		reference;
			typedef const value_type&	const_reference;
			typedef size_t				size_type;
			typedef ptrdiff_t			difference_type;
			typedef _Alloc				allocator_type;

			_Node_allocator&
			_M_get_Node_allocator()
			{ return this->_M_impl; }

			const _Node_allocator&
			_M_get_Node_allocator() const
			{ return this->_M_impl; }

			allocator_type
			get_allocator() const
			{ return allocator_type(_M_get_Node_allocator()); }

		protected:
			_Link_type
			_M_get_node()
			{ return _M_get_Node_allocator().allocate(1); }

			void
			_M_put_node(_Link_type __p)
			{ _M_get_Node_allocator().deallocate(__p, 1); }

			void
			_M_construct_node(_Link_type __node, const value_type& __x)
			{
				try
				{
					get_allocator().construct(__node->_M_valptr(), __x);
				}
				catch(...)
				{
					_M_put_node(__node);
					throw;
				}
			}

			_Link_type
			_M_create_node(const value_type& __x)
			{
				_Link_type __tmp = _M_get_node();
				_M_construct_node(__tmp, __x);
				return __tmp;
			}

			void
			_M_destroy_node(_Link_type __p)
			{
				get_allocator().destroy(__p->_M_valptr());
			}

			void
			_M_drop_node(_Link_type __p)
			{
				_M_destroy_node(__p);
				_M_put_node(__p);
			}

			template <typename _NodeGen>
			_Link_type
			_M_clone_node(_Const_Link_type __x, _NodeGen& __node_gen)
			{
				_Link_type __tmp = __node_gen(*__x->_M_valptr());
				__tmp->_M_color = __x->_M_color;
				__tmp->_M_left = 0;
				__tmp->_M_right = 0;
				return __tmp;
			}

			protected:
				template <typename _Key_compare>
				struct _Rb_tree_impl
				: public _Node_allocator
				, public _Rb_tree_key_compare<_Key_compare>
				, public _Rb_tree_header
				{
					typedef _Rb_tree_key_compare<_Key_compare> _Base_key_compare;

					_Rb_tree_impl()
					: _Node_allocator()
					{ }

					_Rb_tree_impl(const _Key_compare& __comp, const _Node_allocator& __a)
					: _Node_allocator(__a)
					, _Base_key_compare(__comp)
					{ }

					_Rb_tree_impl(const _Rb_tree_impl& __x)
					: _Node_allocator(__x)
					, _Base_key_compare(__x._M_key_compare)
					{ }


				}; // struct _Rb_tree_impl

			_Rb_tree_impl<_Compare> _M_impl;

			protected:
				_Base_ptr&
				_M_root()
				{ return this->_M_impl._M_header._M_parent; }

				_Const_Base_ptr
				_M_root() const
				{ return this->_M_impl._M_header._M_parent; }

				_Base_ptr&
				_M_leftmost()
				{ return this->_M_impl._M_header._M_left; }

				_Const_Base_ptr
				_M_leftmost() const
				{ return this->_M_impl._M_header._M_left; }

				_Base_ptr&
				_M_rightmost()
				{ return this->_M_impl._M_header._M_right; }

				_Const_Base_ptr
				_M_rightmost() const
				{ return this->_M_impl._M_header._M_right; }

				_Link_type
				_M_begin()
				{ return static_cast<_Link_type>(_M_impl._M_header._M_parent); }

				_Const_Link_type
				_M_begin() const
				{ return static_cast<_Const_Link_type>(_M_impl._M_header._M_parent); }

				_Base_ptr
				_M_end()
				{ return &this->_M_impl._M_header; }

				_Const_Base_ptr
				_M_end() const
				{ return &this->_M_impl._M_header; }

				static const_reference
				_S_value(_Const_Link_type __x)
				{ return *__x->_M_valptr(); }

				static const_reference
				_S_value(_Const_Base_ptr __x)
				{ return *static_cast<_Const_Link_type>(__x)->_M_valptr(); }

				static const _Key&
				_S_key(_Const_Link_type __x)
				{ return _KeyOfValue()(*__x->_M_valptr()); }

				static const _Key&
				_S_key(_Const_Base_ptr __x)
				{ return _S_key(static_cast<_Const_Link_type>(__x)); }

				static _Link_type
				_S_left(_Base_ptr __x)
				{ return static_cast<_Link_type>(__x->_M_left); }

				static _Const_Link_type
				_S_left(_Const_Base_ptr __x)
				{ return static_cast<_Const_Link_type>(__x->_M_left); }

				static _Link_type
				_S_right(_Base_ptr __x)
				{ return static_cast<_Link_type>(__x->_M_right); }

				static _Const_Link_type
				_S_right(_Const_Base_ptr __x)
				{ return static_cast<_Const_Link_type>(__x->_M_right); }

				static _Base_ptr
				_S_minimum(_Base_ptr __x)
				{ return _Rb_tree_node_base::_S_minimum(__x); }

				static _Const_Base_ptr
				_S_minimum(_Const_Base_ptr __x)
				{ return _Rb_tree_node_base::_S_minimum(__x); }

				static _Base_ptr
				_S_maximum(_Base_ptr __x)
				{ return _Rb_tree_node_base::_S_maximum(__x); }

				static _Const_Base_ptr
				_S_maximum(_Const_Base_ptr __x)
				{ return _Rb_tree_node_base::_S_maximum(__x); }

			public:
				typedef _Rb_tree_iterator<value_type> iterator;
				typedef _Rb_tree_const_iterator<value_type> const_iterator;

				typedef ft::reverse_iterator<iterator> reverse_iterator;
				typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

				ft::pair<_Base_ptr, _Base_ptr>
				_M_get_insert_unique_pos(const key_type& __k)
				{
					typedef ft::pair<_Base_ptr, _Base_ptr> _Res;
					_Link_type __x = _M_begin();
					_Base_ptr __y = _M_end();
					bool __comp = true;
					while (__x != 0)
					{
						__y = __x;
						__comp = _M_impl._M_key_compare(__k, _S_key(__x));
						__x = __comp ? _S_left(__x) : _S_right(__x);
					}
					iterator __j = iterator(__y);
					if (__comp)
					{
						if (__j == begin())
							return _Res(__x, __y);
						else
							--__j;
					}
					if (_M_impl._M_key_compare(_S_key(__j._M_node), __k))
						return _Res(__x, __y);
					return _Res(__j._M_node, 0);
				}

				ft::pair<_Base_ptr, _Base_ptr>
				_M_get_insert_equal_pos(const key_type& __k)
				{
					typedef ft::pair<_Base_ptr, _Base_ptr> _Res;
					_Link_type __x = _M_begin();
					_Base_ptr __y = _M_end();
					while (__x != 0)
					{
						__y = __x;
						__x = _M_impl._M_key_compare(__k, _S_key(__x)) ?
							_S_left(__x) : _S_right(__x);
					}
					return _Res(__x, __y);
				}

				ft::pair<_Base_ptr, _Base_ptr>
				_M_get_insert_hint_unique_pos(const_iterator __position,
								const key_type& __k)
				{
					iterator __pos = __position._M_const_cast();
					typedef ft::pair<_Base_ptr, _Base_ptr> _Res;

					if (__pos._M_node == _M_end())
					{
						if (size() > 0
							&& _M_impl._M_key_compare(_S_key(_M_rightmost()),
									__k))
							return _Res(0, _M_rightmost());
						else
							return _M_get_insert_unique_pos(__k);
					}
					else if (_M_impl._M_key_compare(__k, _S_key(__pos._M_node)))
					{
						iterator __before = __pos;
						if (__pos._M_node == _M_leftmost())
							return _Res(_M_leftmost(), _M_leftmost());
						else if (_M_impl._M_key_compare(_S_key((--__before)._M_node),
									__k))
						{
							if (_S_right(__before._M_node) == 0)
								return _Res(0, __before._M_node);
							else
								return _Res(__pos._M_node, __pos._M_node);
						}
						else
							return _M_get_insert_unique_pos(__k);
					}
					else if (_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
					{
						iterator __after = __pos;
						if (__pos._M_node == _M_rightmost())
							return _Res(0, _M_rightmost());
						else if (_M_impl._M_key_compare(__k,
									_S_key((++__after)._M_node)))
						{
							if (_S_right(__pos._M_node) == 0)
								return _Res(0, __pos._M_node);
							else
								return _Res(__after._M_node, __after._M_node);
						}
						else
							return _M_get_insert_unique_pos(__k);
					}
					else
						return _Res(__pos._M_node, 0);
				}

				ft::pair<_Base_ptr, _Base_ptr>
				_M_get_insert_hint_equal_pos(const_iterator __position,
								const key_type& __k)
				{
					iterator __pos = __position._M_const_cast();
					typedef ft::pair<_Base_ptr, _Base_ptr> _Res;

					if (__pos._M_node == _M_end())
					{
						if (size() > 0
							&& !_M_impl._M_key_compare(__k,
									_S_key(_M_rightmost())))
							return _Res(0, _M_rightmost());
						else
							return _M_get_insert_equal_pos(__k);
					}
					else if (!_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
					{
						iterator __before = __pos;
						if (__pos._M_node == _M_leftmost())
							return _Res(_M_leftmost(), _M_leftmost());
						else if (!_M_impl._M_key_compare(__k, _S_key((--__before)._M_node)))
						{
							if (_S_right(__before._M_node) == 0)
								return _Res(0, __before._M_node);
							else
								return _Res(__pos._M_node, __pos._M_node);
						}
						else
							return _M_get_insert_equal_pos(__k);
					}
					else
					{
						iterator __after = __pos;
						if (__pos._M_node == _M_rightmost())
							return _Res(0, _M_rightmost());
						else if (!_M_impl._M_key_compare(_S_key((++__after)._M_node), __k))
						{
							if (_S_right(__pos._M_node) == 0)
								return _Res(0, __pos._M_node);
							else
								return _Res(__after._M_node, __after._M_node);
						}
						else
							return _Res(0, 0);
					}
				}

			private:
				template <typename _NodeGen>
				iterator
				_M_insert_(_Base_ptr __x, _Base_ptr __p,
						const value_type& __v, _NodeGen& __node_gen)
				{
					bool __insert_left = (__x != 0 || __p == _M_end()
						|| _M_impl._M_key_compare(_KeyOfValue()(__v),
									_S_key(__p)));

					_Link_type __z = __node_gen(__v);

					_Rb_tree_insert_and_rebalance(__insert_left, __z, __p,
								this->_M_impl._M_header);
					++_M_impl._M_node_count;
					return iterator(__z);
				}

				iterator
				_M_insert_lower(_Base_ptr __y, const value_type& __v)
				{
					bool __insert_left = (__y == _M_end()
						|| !_M_impl._M_key_compare(_S_key(__y),
							_KeyOfValue()(__v)));

					_Link_type __x = _M_create_node(__v);

					_Rb_tree_insert_and_rebalance(__insert_left, __x, __y,
								this->_M_impl._M_header);
					++_M_impl._M_node_count;
					return iterator(__x);
				}

				iterator
				_M_insert_equal_lower(const value_type& __v)
				{
					_Link_type __x = _M_begin();
					_Base_ptr __y = _M_end();
					while (__x != 0)
					{
						__y = __x;
						__x = !_M_impl._M_key_compare(_S_key(__x), _KeyOfValue()(__v) ?
								_S_left(__x) : _S_right(__x));
					}
					return _M_insert_lower(__y, __v);
				}

				template <typename _NodeGen>
				_Link_type
				_M_copy(_Const_Link_type __x, _Base_ptr __p, _NodeGen& __node_gen)
				{
					_Link_type __top = _M_clone_node(__x, __node_gen);
					__top->_M_parent = __p;
					try
					{
						if (__x->_M_right)
							__top->_M_right = _M_copy(_S_right(__x), __top, __node_gen);
						__p = __top;
						__x = _S_left(__x);

						while (__x != 0)
						{
							_Link_type __y = _M_clone_node(__x, __node_gen);
							__p->_M_left = __y;
							__y->_M_parent = __p;
							if (__x->_M_right)
								__y->_M_right = _M_copy(_S_right(__x), __y, __node_gen);
							__p = __y;
							__x = _S_left(__x);
						}
					}
					catch(...)
					{
						_M_erase(__top);
						throw;
					}
					return __top;
				}

				template <typename _NodeGen>
				_Link_type
				_M_copy(const _Rb_tree& __x, _NodeGen& __gen)
				{
					_Link_type __root = _M_copy(__x._M_begin(), _M_end(), __gen);
					_M_leftmost() = _S_minimum(__root);
					_M_rightmost() = _S_maximum(__root);
					_M_impl._M_node_count = __x._M_impl._M_node_count;
					return __root;
				}

				_Link_type
				_M_copy(const _Rb_tree& __x)
				{
					_Alloc_node __an(*this);
					return _M_copy(__x, __an);
				}

				void
				_M_erase(_Link_type __x)
				{
					while (__x != 0)
					{
						_M_erase(_S_right(__x));
						_Link_type __y = _S_left(__x);
						_M_drop_node(__x);
						__x = __y;
					}
				}

				iterator
				_M_lower_bound(_Link_type __x, _Base_ptr __y,
						const _Key& __k)
				{
					while (__x != 0)
						if (!_M_impl._M_key_compare(_S_key(__x), __k))
							__y = __x, __x = _S_left(__x);
						else
							__x = _S_right(__x);
					return iterator(__y);
				}

				const_iterator
				_M_lower_bound(_Const_Link_type __x, _Const_Base_ptr __y,
						const _Key& __k) const
				{
					while (__x != 0)
						if (!_M_impl._M_key_compare(_S_key(__x), __k))
							__y = __x, __x = _S_left(__x);
						else
							__x = _S_right(__x);
					return const_iterator(__y);
				}

				iterator
				_M_upper_bound(_Link_type __x, _Base_ptr __y,
						const _Key& __k)
				{
					while (__x != 0)
						if (_M_impl._M_key_compare(__k, _S_key(__x)))
							__y = __x, __x = _S_left(__x);
						else
							__x = _S_right(__x);
					return iterator(__y);
				}

				const_iterator
				_M_upper_bound(_Const_Link_type __x, _Const_Base_ptr __y,
						const _Key& __k) const
				{
					while (__x != 0)
						if (_M_impl._M_key_compare(__k, _S_key(__x)))
							__y = __x, __x = _S_left(__x);
						else
							__x = _S_right(__x);
					return const_iterator(__y);
				}

			public:
				_Rb_tree() { }

				_Rb_tree(const _Compare& __comp,
						const allocator_type& __a = allocator_type())
				: _M_impl(__comp, _Node_allocator(__a)) { }

				_Rb_tree(const _Rb_tree& __x)
				: _M_impl(__x._M_impl)
				{
					if (__x._M_root() != 0)
						_M_root() = _M_copy(__x);
				}

				~_Rb_tree()
				{
					_M_erase(_M_begin());
				}

				_Rb_tree&
				operator=(const _Rb_tree& __x);

				_Compare
				key_comp() const
				{ return _M_impl._M_key_compare; }

				iterator
				begin()
				{ return iterator(this->_M_impl._M_header._M_left); }

				const_iterator
				begin() const
				{ return const_iterator(this->_M_impl._M_header._M_left); }

				iterator
				end()
				{ return iterator(&_M_impl._M_header); }

				const_iterator
				end() const
				{ return const_iterator(&_M_impl._M_header); }

				reverse_iterator
				rbegin()
				{ return reverse_iterator(end()); }

				const_reverse_iterator
				rbegin() const
				{ return const_reverse_iterator(end()); }

				reverse_iterator
				rend()
				{ return reverse_iterator(begin()); }

				const_reverse_iterator
				rend() const
				{ return const_reverse_iterator(begin()); }

				bool
				empty() const
				{ return _M_impl._M_node_count == 0; }

				size_type
				size() const
				{ return _M_impl._M_node_count; }

				size_type
				max_size() const
				{ return _Node_allocator::max_size(); }

				void
				swap(_Rb_tree& __t)
				{
					if (_M_root() == 0)
					{
						if (__t._M_root() != 0)
							_M_impl._M_move_data(__t._M_impl);
					}
					else if (__t._M_root() == 0)
						__t._M_impl._M_move_data(_M_impl);
					else
					{
						std::swap(_M_root(), __t._M_root());
						std::swap(_M_leftmost(), __t._M_leftmost());
						std::swap(_M_rightmost(), __t._M_rightmost());

						_M_root()->_M_parent = _M_end();
						__t._M_root()->_M_parent = __t._M_end();
						std::swap(this->_M_impl._M_node_count, __t._M_impl._M_node_count);
					}
					std::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);
					std::swap(_M_get_Node_allocator(), __t._M_get_Node_allocator());
				}

				ft::pair<iterator, bool>
				_M_insert_unique(const value_type& __v)
				{
					typedef ft::pair<iterator, bool> _Res;
					ft::pair<_Base_ptr, _Base_ptr> __res =
						_M_get_insert_unique_pos(_KeyOfValue()(__v));

					if (__res.second)
					{
						_Alloc_node __an(*this);
						return _Res(_M_insert_(__res.first, __res.second, __v, __an),
								true);
					}
					return _Res(iterator(__res.first), false);
				}

				iterator
				_M_insert_equal(const value_type& __v)
				{
					ft::pair<_Base_ptr, _Base_ptr> __res =
						_M_get_insert_equal_pos(_KeyOfValue()(__v));
					_Alloc_node __an(*this);
					return _M_insert_(__res.first, __res.second, __v, __an);
				}

				template <typename _NodeGen>
				iterator
				_M_insert_unique_(const_iterator __position, const value_type& __v,
						_NodeGen& __node_gen)
				{
					ft::pair<_Base_ptr, _Base_ptr> __res =
						_M_get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));
					if (__res.second)
						return _M_insert_(__res.first, __res.second, __v, __node_gen);
					return iterator(__res.first);
				}

				iterator
				_M_insert_unique_(const_iterator __pos, const value_type& __v)
				{
					_Alloc_node __an(*this);
					return _M_insert_unique_(__pos, __v, __an);
				}

				template <typename _NodeGen>
				iterator
				_M_insert_equal_(const_iterator __position, const value_type& __v,
						_NodeGen& __node_gen)
				{
					ft::pair<_Base_ptr, _Base_ptr> __res =
						_M_get_insert_hint_equal_pos(__position, _KeyOfValue()(__v));
					return _M_insert_(__res.first, __res.second, __v, __node_gen);
				}

				iterator
				_M_insert_equal_(const_iterator __pos, const value_type& __x)
				{
					_Alloc_node __an(*this);
					return _M_insert_equal_(__pos, __x, __an);
				}

				template <typename _InputIterator>
				void
				_M_insert_range_unique(_InputIterator __first, _InputIterator __last)
				{
					_Alloc_node __an(*this);
					for(; __first != __last; ++__first)
						_M_insert_unique_(end(), *__first, __an);
				}

				template <typename _InputIterator>
				void
				_M_insert_range_equal(_InputIterator __first, _InputIterator __last)
				{
					_Alloc_node __an(*this);
					for(; __first != __last; ++__first)
						_M_insert_equal_(end(), *__first, __an);
				}

			private:
				void
				_M_erase_aux(const_iterator __position)
				{
					_Link_type __y = static_cast<_Link_type>
						(_Rb_tree_rebalance_for_erase
						 (const_cast<_Base_ptr>(__position._M_node),
						  this->_M_impl._M_header));
					_M_drop_node(__y);
					--_M_impl._M_node_count;
				}

				void
				_M_erase_aux(const_iterator __first, const_iterator __last)
				{
					if (__first == begin() && __last == end())
						clear();
					else
						while (__first != __last)
							_M_erase_aux(__first++);
				}

			public:
				void
				erase(iterator __position)
				{
					_M_erase_aux(__position);
				}

				void
				erase(const_iterator __position)
				{
					_M_erase_aux(__position);
				}

				size_type
				erase(const key_type& __x)
				{
					ft::pair<iterator, iterator> __p = equal_range(__x);
					const size_type __old_size = size();
					_M_erase_aux(__p.first, __p.second);
					return __old_size - size();
				}

				void
				erase(iterator __first, iterator __last)
				{
					_M_erase_aux(__first, __last);
				}

				void
				erase(const_iterator __first, const_iterator __last)
				{
					_M_erase_aux(__first, __last);
				}

				void
				erase(const key_type* __first, const key_type* __last)
				{
					while (__first != __last)
						erase(*__first++);
				}

				void
				clear()
				{
					_M_erase(_M_begin());
					_M_impl._M_reset();
				}

				iterator
				find(const key_type& __k)
				{
					iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
					return (__j == end()
							|| _M_impl._M_key_compare(__k,
									_S_key(__j._M_node))) ? end() : __j;
				}

				const_iterator
				find(const key_type& __k) const
				{
					const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
					return (__j == end()
							|| _M_impl._M_key_compare(__k,
									_S_key(__j._M_node))) ? end() : __j;
				}

				size_type
				count(const key_type& __k) const
				{
					ft::pair<const_iterator, const_iterator> __p = equal_range(__k);
					const size_type __n = std::distance(__p.first, __p.second);
					return __n;
				}

				iterator
				lower_bound(const key_type& __k)
				{ return _M_lower_bound(_M_begin(), _M_end(), __k); }

				const_iterator
				lower_bound(const key_type& __k) const
				{ return _M_lower_bound(_M_begin(), _M_end(), __k); }

				iterator
				upper_bound(const key_type& __k)
				{ return _M_upper_bound(_M_begin(), _M_end(), __k); }

				const_iterator
				upper_bound(const key_type& __k) const
				{ return _M_upper_bound(_M_begin(), _M_end(), __k); }

				ft::pair<iterator, iterator>
				equal_range(const key_type& __k)
				{
					_Link_type __x = _M_begin();
					_Base_ptr __y = _M_end();

					while (__x != 0)
					{
						if (_M_impl._M_key_compare(_S_key(__x), __k))
							__x = _S_right(__x);
						else if (_M_impl._M_key_compare(__k, _S_key(__x)))
							__y = __x, __x = _S_left(__x);
						else
							{
								_Link_type __xu(__x);
								_Base_ptr __yu = __y;
								__y = __x, __x = _S_left(__x);
								__xu = _S_right(__xu);
								return ft::pair<iterator, iterator>
									(_M_lower_bound(__x, __y, __k),
									 _M_upper_bound(__xu, __yu, __k));
							}
					}
					return ft::pair<iterator, iterator>(iterator(__y),
							iterator(__y));
				}

				ft::pair<const_iterator, const_iterator>
				equal_range(const key_type& __k) const
				{
					_Const_Link_type __x = _M_begin();
					_Const_Base_ptr __y = _M_end();

					while (__x != 0)
					{
						if (_M_impl._M_key_compare(_S_key(__x), __k))
							__x = _S_right(__x);
						else if (_M_impl._M_key_compare(__k, _S_key(__x)))
							__y = __x, __x = _S_left(__x);
						else
							{
								_Const_Link_type __xu(__x);
								_Const_Base_ptr __yu = __y;
								__y = __x, __x = _S_left(__x);
								__xu = _S_right(__xu);
								return ft::pair<const_iterator, const_iterator>
									(_M_lower_bound(__x, __y, __k),
									 _M_upper_bound(__xu, __yu, __k));
							}
					}
					return ft::pair<const_iterator, const_iterator>
						(const_iterator(__y), const_iterator(__y));
				}

				bool
				__rb_verify() const
				{
					if (_M_impl._M_node_count == 0 || begin() == end())
						return _M_impl._M_node_count == 0 && begin() == end()
							&& this->_M_impl._M_header._M_left == _M_end()
							&& this->_M_impl._M_header._M_right == _M_end();

					unsigned int __len = _Rb_tree_black_count(_M_leftmost(), _M_root());
					for (const_iterator __it = begin(); __it != end(); ++__it)
					{
						_Const_Link_type __x = static_cast<_Const_Link_type>(__it._M_node);
						_Const_Link_type __L = _S_left(__x);
						_Const_Link_type __R = _S_right(__x);

						if (__x->_M_color == _S_red)
							if ((__L && __L->_M_color == _S_red)
									|| (__R && __R->_M_color == _S_red))
								return false;
						if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L)))
							return false;

						if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__x)))
							return false;

						if (!__L && !__R && _Rb_tree_black_count(__x, _M_root()) != __len)
							return false;
					}
					if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
						return false;
					if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
						return false;
					return true;
				}

				friend bool
				operator==(const _Rb_tree& __x, const _Rb_tree& __y)
				{
					return __x.size() == __y.size()
						&& ft::equal(__x.begin(), __x.end(), __y.begin());
				}

				friend bool
				operator<(const _Rb_tree& __x, const _Rb_tree& __y)
				{
					return ft::lexicographical_compare(__x.begin(), __x.end(),
							__y.begin(), __y.end());
				}

				friend bool
				operator!=(const _Rb_tree& __x, const _Rb_tree& __y)
				{ return !(__x == __y); }

				friend bool
				operator>(const _Rb_tree& __x, const _Rb_tree& __y)
				{ return __y < __x; }

				friend bool
				operator<=(const _Rb_tree& __x, const _Rb_tree& __y)
				{ return !(__y < __x); }

				friend bool
				operator>=(const _Rb_tree& __x, const _Rb_tree& __y)
				{ return !(__x < __y); }
	}; // class _Rb_tree

	template <typename _Key, typename _Value, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	inline void
	swap(_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __x,
			_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __y)
	{ __x.swap(__y); }

	template <typename _Key, typename _Value, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>&
	_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::
	operator=(const _Rb_tree& __x)
	{
		if (this != &__x)
		{
			_Reuse_or_alloc_node __roan(*this);
			_M_impl._M_reset();
			_M_impl._M_key_compare = __x._M_impl._M_key_compare;
			if (__x._M_root() != 0)
				_M_root() = _M_copy(__x, __roan);
		}
		return *this;
	}
} // namespace std

#endif
