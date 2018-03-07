#pragma once

#include "Utility.hpp"
#include <algorithm>


namespace LudosLib
{
	namespace DataStructs
	{
		template <typename T, typename cmp_t1 = Lesser<T>, typename cmp_t2 = Greater<T>>
		class Set
		{
			AVLNode<T> *m_root;
			cmp_t1 m_cmp1; cmp_t2 m_cmp2;
			const bool m_isRoot;

			AVLNode<T> *Root() { return (m_isRoot ? nullptr : m_root); }

		public:
			Set() : m_root(nullptr), m_isRoot(true) { static_assert(inheritancecheck<SingleCmp<T>, cmp_t1>() && inheritancecheck<SingleCmp<T>, cmp_t2>()); }
			~Set() { if (m_isRoot) Clear(); }
			
			AVLNode<T> *Insert(T value)
			{
				if (Empty())
				{
					m_root = new AVLNode<T>(value);
					return Root();
				}

				if (m_cmp1(value, m_root->data))
					m_root->left = Set(m_root->left).Insert(value);
				else if (m_cmp2(value, m_root->data))
					m_root->right = Set(m_root->right).Insert(value);
				else return Root();

				Update();
				ApplyRotations();
				return Root();
			}

		private:
			AVLNode<T> *RotateToLeaf()
			{
				if (Set(m_root->left).Empty() && Set(m_root->right).Empty())
				{
					Clear();
					return nullptr;
				}

				if (Balance() < 0)
				{
					LeftRotate();
					m_root->left = Set(m_root->left).RotateToLeaf();
				}
				else
				{
					RightRotate();
					m_root->right = Set(m_root->right).RotateToLeaf();
				}

				Update();
				ApplyRotations();
				return Root();
			}

		public:
			AVLNode<T> *Remove(T value)
			{
				if (Empty())
					return nullptr;

				if (m_cmp1(value, m_root->data))
					m_root->left = Set(m_root->left).Remove(value);
				else if (m_cmp2(value, m_root->data))
					m_root->right = Set(m_root->right).Remove(value);
				else return (m_isRoot ? nullptr : RotateToLeaf());

				Update();
				ApplyRotations();
				return Root();
			}

			bool Find(T value)
			{
				if (Empty()) return false;
				if (m_cmp1(value, m_root->data))
					return Set(m_root->left).Find(value);
				if (m_cmp2(value, m_root->data))
					return Set(m_root->right).Find(value);
				return true;
			}

			void Clear() { delete m_root; m_root = nullptr; }

			size_t Size() { return (Empty() ? 0 : m_root->size); }
			bool Empty() { return (m_root == nullptr); }

		private:
			Set(AVLNode<T> *node) : m_root(node), m_isRoot(false) {}

			size_t Height() { return (Empty() ? 0 : m_root->height); }
			int Balance() { return (((int)Set(m_root->left).Height()) - ((int)Set(m_root->right).Height())); }

			void Update()
			{
				m_root->size = Set(m_root->left).Size() + Set(m_root->right).Size() + 1;
				m_root->height = std::max(Set(m_root->left).Height(), Set(m_root->right).Height()) + 1;
			}

			void LeftRotate()
			{
				AVLNode<T> *newRoot = m_root->right;
				m_root->right = newRoot->left;
				newRoot->left = m_root;

				Update();
				m_root = newRoot;
				Update();
			}

			void RightRotate()
			{
				AVLNode<T> *newRoot = m_root->left;
				m_root->left = newRoot->right;
				newRoot->right = m_root;

				Update();
				m_root = newRoot;
				Update();
			}

			void ApplyRotations()
			{
				if (Balance() == 2)
				{
					Set unbalance(m_root->left);
					if (unbalance.Balance() == -1)
					{
						unbalance.LeftRotate();
						m_root->left = unbalance.Root();
					}
					RightRotate();
				}
				else if (Balance() == -2)
				{
					Set unbalance(m_root->right);
					if (unbalance.Balance() == 1)
					{
						unbalance.RightRotate();
						m_root->right = unbalance.Root();
					}
					LeftRotate();
				}
			}
		};
	}
}