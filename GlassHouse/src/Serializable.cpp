#include <Serializable.h>

inline Serializable::Serializable(int32_t i_) : i(i_), v(validValue::I) {}
inline Serializable::Serializable(double d_) : d(d_), v(validValue::D) {}
inline Serializable::Serializable(std::string s_) : s(s_), v(validValue::S) {}

std::string Serializable::toString()
{
	switch (v)
	{
	case validValue::I:
		return std::to_string(i);
	case validValue::D:
		return std::to_string(d);
	case validValue::S:
		return s;
	}
}
