#include "jbcc.h"

#include <iterator>

// Reformatter, C++ version

int jbcc::Reformatter::reformat_null(void * ctx)
{
	yajl_gen g = (yajl_gen)ctx;
	return yajl_gen_status_ok == yajl_gen_null(g);
}

int jbcc::Reformatter::reformat_boolean(void * ctx, int boolean)
{
	yajl_gen g = (yajl_gen)ctx;
	return yajl_gen_status_ok == yajl_gen_bool(g, boolean);
}

int jbcc::Reformatter::reformat_int(void * ctx, long long intVal)
{
	yajl_gen g = (yajl_gen)ctx;
	auto s = std::to_string(intVal);
	return yajl_gen_status_ok == yajl_gen_number(g, s.c_str(), s.length());
}

int jbcc::Reformatter::reformat_double(void * ctx, double doubleVal)
{
	yajl_gen g = (yajl_gen)ctx;
	auto s = std::to_string(doubleVal);
	return yajl_gen_status_ok == yajl_gen_number(g, s.c_str(), s.length());
}

//int jbcc::Reformatter::reformat_number(void * ctx, const char * s, size_t l)
//{
//	yajl_gen g = (yajl_gen)ctx;
//	return yajl_gen_status_ok == yajl_gen_number(g, s, l);
//}

int jbcc::Reformatter::reformat_string(void * ctx, const unsigned char * stringVal,
	size_t stringLen, int /*cte_pool*/)
{
	yajl_gen g = (yajl_gen)ctx;
	return yajl_gen_status_ok == yajl_gen_string(g, stringVal, stringLen);
}

int jbcc::Reformatter::reformat_map_key(void * ctx, const unsigned char * stringVal,
	size_t stringLen, int /*cte_pool*/)
{
	yajl_gen g = (yajl_gen)ctx;
	return yajl_gen_status_ok == yajl_gen_string(g, stringVal, stringLen);
}

int jbcc::Reformatter::reformat_start_map(void * ctx, unsigned int /*size*/)
{
	yajl_gen g = (yajl_gen)ctx;
	return yajl_gen_status_ok == yajl_gen_map_open(g);
}


int jbcc::Reformatter::reformat_end_map(void * ctx)
{
	yajl_gen g = (yajl_gen)ctx;
	return yajl_gen_status_ok == yajl_gen_map_close(g);
}

int jbcc::Reformatter::reformat_start_array(void * ctx, unsigned int /*size*/)
{
	yajl_gen g = (yajl_gen)ctx;
	return yajl_gen_status_ok == yajl_gen_array_open(g);
}

int jbcc::Reformatter::reformat_end_array(void * ctx)
{
	yajl_gen g = (yajl_gen)ctx;
	return yajl_gen_status_ok == yajl_gen_array_close(g);
}