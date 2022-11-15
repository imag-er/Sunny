#pragma once
#include <string>
#include <iostream>
#include <fmt/core.h>
enum class iss
{
	r = '\r' ,
	n = '\n' 
};
class information_stream
{
public:
	void init( );

	template<typename text_type>
	inline information_stream& operator<<( text_type );

	~information_stream( );
private:
	FILE* old_stream;
};

extern information_stream isout;

template<typename text_type>
inline information_stream& information_stream::operator<<( text_type str)
{
	std::cout << str;
	return *this;
}

template <>
inline information_stream& information_stream::operator<<( std::string str )
{
	std::cout << str;
	return *this;
}

template <>
inline information_stream& information_stream::operator<<( std::wstring str )
{
	std::wcout << str;
	return *this;
}
template <>
inline information_stream& information_stream::operator<<( iss s )
{
	std::cout << static_cast< const char >( s );
	return *this;

}