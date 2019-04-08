// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#pragma once;



#include <list>
#include <string>
#include <functional>
#include <assert.h>
typedef unsigned int Hash;
extern std::hash<std::string> s_hash;

template<class T, int SIZE>
class HashMap
{
public:

	HashMap()
	{
		//Figures out if the size is a power of two and throws an error if its not
		//Needs a power of two to work properly with the translate function
		const bool powerIsTure = (powerOfTwo(SIZE) == true);
		assert(powerIsTure);

		mMask = SIZE - 1;
	}

	// Insert data into our hashmap if it is not already there
	bool Insert(T& data)
	{
		//Which bucket?
		const bool bExists = (Find(data->mHash) != nullptr);

		if (bExists)
		{
			return false;
		}

		InsertNoCheck(data);

		return true;
	}

	// Slam the data into our hashmap with no regard for nothin'
	void InsertNoCheck(T& data)
	{
		//find the bucket
		int bucketIndex = Translate(data->mHash);
		mBuckets[bucketIndex].push_back(data);
	}


	//Finds a hash in the map
	T Find(Hash hash)
	{
		//Which bucket?
		int bucketIndex = Translate(hash);
		std::list<T>& thisBucket = mBuckets[bucketIndex];

		for (T& entry : thisBucket)
		{
			//Yes officer, this hash right here
			if (entry->mHash == hash)
			{
				return entry;
			}
		}
		return nullptr;
	}

	// Finds the data form the map as a const
	const T Find(Hash hash) const
	{
		int bucketIndex = Translate(hash);
		const std::list<T>& thisBucket = mBuckets[bucketIndex];

		for (const T& entry : thisBucket)
		{
			if (entry->mHash == hash)
			{
				return entry;
			}
		}
		return nullptr;
	}

	bool powerOfTwo(int size)
	{
		return (size && !(size & (size - 1)));
	}


	void Delete(T data)
	{
		int bucketIndex = Translate(data->mHash);
		std::list<T>& bucket = mBuckets[bucketIndex];
		for (T& entry : bucket)
		{
			if (entry->mHash == data->mHash)
			{
				bucket.remove(entry);
				break;
			}
		}
	}

private:

	// Knocks a hash of any size down to one that will fit in our map
	int Translate(Hash hash) const
	{
		return (hash & mMask);
	}

private:

	Hash mMask;
	std::list<T> mBuckets[SIZE];
};
