#pragma once
template<class T>
class Singleton
{
	
protected:
	// constructor for the singelton 
	Singleton() {}
	// deconstructor
	~Singleton()
	{
		delete instance;
	}

	// disables the equal operator to prevent assignation of the singelton to an other value 
	Singleton& operator=(const Singleton) = delete;
	// disables the copy function to prevent the creation of an other singelton 
	Singleton(const Singleton&) = delete;


public:

	static T* getinstance()
	{
		// check that tha there is no instance of the singleton all ready created 
		if (instance == nullptr)
		{
			instance = new T();
			return instance;
		}
		else
		{
			return instance;
		}
	}

private:
	//declaration of the variable 
	static T* instance;

};
