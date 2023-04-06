// MathLibrary.h - Contains declarations of math functions
#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

class GLASSHOUSE_API BaseClass
{
public:
	BaseClass();
	virtual int returnID() const;
	void writeFile();
protected:
	int id;
};
