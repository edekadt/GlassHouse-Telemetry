#pragma once

#include <string>

class Serializable
{
public:
	Serializable(int32_t i_);
	Serializable(double d_);
	Serializable(std::string s_);

	std::string toString();

	~Serializable() {};

private:
	enum validValue {I, D, S}; // Int, Double, String
	validValue v;
	union {
		int32_t i;
		double d;
		std::string s;
	};
};
