/**
An inheritable utility class that adds a queryable flag that can be set to notify reader
classes that this class has been modified.

@author Nathan */

#ifndef HAS_MODIFICATION_FLAG_H
#define HAS_MODIFICATION_FLAG_H

class HasModificationFlag
{
	private:

	protected:
		bool m_bModifiedFlag;

	public:
		/**
		Constructs a HasModificationFlag. The flag defaults to false. */
		HasModificationFlag();

		/**
		Queries whether this class's properties have been modified since the last call
		to this function. Note that calling this function will also reset the modified
		flag to false if it was true. */
		bool hasBeenModified();
};

#endif