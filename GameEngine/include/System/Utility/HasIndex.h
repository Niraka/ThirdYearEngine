/**
A utility class for the allocation of an index to an object. 

This class is just a time-saver & mostly for use in conjunction with VectorInd. A Locking
version will prevent the index from being set more than once.

@author Nathan */

#ifndef HAS_INDEX_H
#define HAS_INDEX_H

class HasIndex
{
	private:
		bool m_bLocked;
		bool m_bIsSet;
		unsigned int m_uiIndex;

	protected:

	public:
		/**
		Constructs a HasIndex in either locking or non-locking mode.
		@param bLocked (Optional) True to lock the index. Defaults to false. */
		HasIndex(bool bLocked = false);

		/**
		Destructs the HasIndex object. */
		~HasIndex();

		/**
		Sets the index. If locking mode is enabled, the index may only be set once.
		@param uiIndex The index to assign */
		void setIndex(unsigned int uiIndex);

		/**
		Gets the index.
		@return The index */
		const unsigned int& getIndex() const;
};

#endif