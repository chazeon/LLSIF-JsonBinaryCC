#ifndef JBCC_H
#define JBCC_H

#include <yajl_parse.h>
#include <yajl_gen.h>

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace jbcc {

	class Parser {
	private:
		yajl_handle handle;
		void *ctx;
		yajl_callbacks *callbacks;
	public:
		using Callbacks = yajl_callbacks;
		Parser(void *ctx, Callbacks *callbacks) {
			this->ctx = ctx;
			this->callbacks = callbacks; // should be ptr or copy?
			handle = yajl_alloc(this->callbacks, nullptr, this->ctx);
			// config
		}
		~Parser() {
			yajl_free(handle);
		}
		yajl_status parse(std::string jsonText) { // should use status as return?
			return yajl_parse(handle, reinterpret_cast<const unsigned char*>(jsonText.c_str()), jsonText.length());
		}
	};

	class Generator {
	private:
		yajl_gen handle;
	public:
		using Handle = yajl_gen;
		Generator() {
			handle = yajl_gen_alloc(nullptr); // test failure
			yajl_gen_config(handle, yajl_gen_beautify, true);
			// config
		}
		~Generator() {
			yajl_gen_free(handle);
		}
		std::string end() {
			const unsigned char *buf;
			size_t len;
			yajl_gen_get_buf(handle, &buf, &len);

			auto result = std::string(reinterpret_cast<const char *>(buf), len); // Possible memory leakage

			yajl_gen_clear(handle);

			return result;
		}

		Handle getHandle() {
			return handle;
		}
	};

	class Reformatter {
	private:
		Generator generator;
		Parser parser;
	public: 
		static int reformat_null(void * ctx);
		static int reformat_boolean(void * ctx, int boolean);
		static int reformat_int(void * ctx, long long integerVal);
		static int reformat_double(void * ctx, double doubleVal);
		//static int reformat_number(void * ctx, const char * s, size_t l);
		static int reformat_string(void * ctx, const unsigned char * stringVal, size_t stringLen, int /*cte_pool*/);
		static int reformat_map_key(void * ctx, const unsigned char * stringVal, size_t stringLen, int /*cte_pool*/);
		static int reformat_start_map(void * ctx, unsigned int /*size*/);
		static int reformat_end_map(void * ctx);
		static int reformat_start_array(void * ctx, unsigned int /*size*/);
		static int reformat_end_array(void * ctx);

		Parser::Callbacks callbacks{
			reformat_null,
			reformat_boolean,
			reformat_int,//nullptr,
			reformat_double,//nullptr,
			nullptr, //reformat_number,
			reformat_string, // cte_pool
			reformat_start_map, // size
			reformat_map_key, // cte_pool
			reformat_end_map,
			reformat_start_array, // size
			reformat_end_array
		};

		Reformatter() : generator(), parser(generator.getHandle(), &callbacks) {}

		std::string reformat(std::string input) {
			parser.parse(input);
			return generator.end();
		}
	};
}


#endif // !JBCC_H
