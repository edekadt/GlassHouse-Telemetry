#pragma once

#include <string>

class Serializable
{
public:
	Serializable(size_t st_);
	Serializable(int32_t i_);
	Serializable(double d_);
	Serializable(std::string s_);
	Serializable(bool b_);

	std::string toString();

	~Serializable() {};

private:
	enum validValue { ST, I, D, S, B}; // Size_t, Int, Double, String
	validValue v;
	union {
		size_t st;
		int32_t i;
		double d;
		std::string s;
		bool b;
	};
};
