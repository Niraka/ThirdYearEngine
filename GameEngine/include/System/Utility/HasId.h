/**
A templated id getter and setter class that provides a convenient way to store ids
on objects. 

@author Nathan */

#ifndef HAS_ID_H
#define HAS_ID_H

template <class T>
class HasId
{
	private:
		T m_id; 
		bool m_bIdSet;
		bool m_bIsLocking;

	protected:

	public:
		/**
		Constructs a default HasId in locking mode. */
		HasId()
		{
			m_bIsLocking = true;
			m_bIdSet = false;
		}

		/**
		Constructs a HasId object with the desired locking mode.
		@param bIsLocking The locking mode */
		HasId(bool bIsLocking)
		{
			m_bIsLocking = bIsLocking;
			m_bIdSet = false;
		}

		/**
		Constructs a HasId object with the desired locking mode.
		@param bIsLocking The locking mode */
		HasId(bool bIsLocking, T id)
		{
			m_bIsLocking = bIsLocking;
			m_id = id;
			m_bIdSet = true;
		}

		void setId(T id)
		{
			if (m_bIsLocking)
			{
				if (!m_bIdSet)
				{
					m_id = id;
					m_bIdSet = true;
				}
			}
			else
			{
				m_id = id;
			}
		}

		T getId() const
		{
			return m_id;
		}
};

#endif