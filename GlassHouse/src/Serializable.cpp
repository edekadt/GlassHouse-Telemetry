#include <Serializable.h>

Serializable::Serializable(size_t st_) : st(st_), v(validValue::ST) {}
Serializable::Serializable(int32_t i_) : i(i_), v(validValue::I) {}
Serializable::Serializable(double d_) : d(d_), v(validValue::D) {}
Serializable::Serializable(std::string s_) : s(s_), v(validValue::S) {}
Serializable::Serializable(bool b_) : b(b_), v(validValue::B) {}

std::string Serializable::toString()
{
	switch (v)
	{
	case validValue::ST:
		return std::to_string(st);
	case validValue::I:
		return std::to_string(i);
	case validValue::D:
		return std::to_string(d);
	case validValue::B:
		return std::to_string(b);
	case validValue::S:
		return s;
	}
}
