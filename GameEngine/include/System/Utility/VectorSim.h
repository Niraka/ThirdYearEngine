/**
A wrapper around a Vector that simplifies the interface to an add and remove by-value
interface.

Use the 'size' and 'at' functions to iterate over the data.

@author Nathan + Wade */

#ifndef VECTOR_SIMPLE_H
#define VECTOR_SIMPLE_H

#include <vector>

template <class T>
class VectorSim
{
	private:
		std::vector<T> m_vec;

	protected:

	public:		
		/**
		Adds an element to the vector.
		@param t The element to add */
		void add(T t)
		{
			m_vec.push_back(t);
		}

		/**
		Returns a reference to the element at the given index. 
		@param iIndex The index of the element to get
		@return A reference to the element */
		T& at(unsigned int iIndex)
		{
			return m_vec.at(iIndex);
		}

		/**
		Returns the size of the vector as the number of elements it currently contains. 
		@return The size of the vector */
		unsigned int size()
		{
			return m_vec.size();
		}

		/**
		Removes all instances of the given element from the vector.
		@param t The element to remove 
		@return The number of elements removed */
		unsigned int remove(T t)
		{
			unsigned int iSize = m_vec.size();
			unsigned int iCounter = 0;
			unsigned int iRemovals = 0;
			for (; iCounter < (iSize - iRemovals); ++iCounter)
			{
				if (m_vec.at(iCounter) == t)
				{
					m_vec.erase(m_vec.begin() + iCounter);
					--iCounter;
					++iRemovals;
				}
			}
			return iRemovals;
		}

		/**
		Returns true if the vector contains at least one copy of the given element.
		@param t The element to find 
		@return True if the element was found */
		bool contains(T t)
		{
			int iSize = m_vec.size();
			int iCounter = 0;
			for (; iCounter < iSize; ++iCounter)
			{
				if (m_vec.at(iCounter) == t)
				{
					return true;
				}
			}
			return false;
		}

		/** 
		Removes all elements. */
		void clear()
		{
			m_vec.clear();
		}

		/**
		Append the contents of another VectorSim to the end of this one
		@param appendVec The Vector sim object to append to this VectorSim*/
		void append(VectorSim<T> appendVec)
		{
			m_vec.insert(m_vec.end(), appendVec.m_vec.begin(), appendVec.m_vec.end());
		}
};

#endif