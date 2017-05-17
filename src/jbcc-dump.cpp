#include "jbcc.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <argparse.hpp>


int main(int argc, const char **argv)
{

	ArgumentParser parser;
	parser.appName("jbcc-dump");
	parser.addArgument("-o", "--output", 1);
	parser.addFinalArgument("input");
	parser.parse(argc, argv);

	std::string input_uri(parser.retrieve<std::string>("input"));

	std::ifstream fin(input_uri, std::ios::binary);

	std::vector<char> buffer(
		(std::istreambuf_iterator<char>(fin)),
		(std::istreambuf_iterator<char>())
	);

	std::string jsonText(buffer.begin(), buffer.end());

	fin.close();

	std::string output_uri = parser.retrieve<std::string>("output");
	if (output_uri != "") {
		std::ofstream fout(output_uri);
		fout << jbcc::Reformatter().reformat(jsonText) << std::endl;
		fout.close();
	}
	else {
		std::cout << jbcc::Reformatter().reformat(jsonText) << std::endl;
	}
	//system("pause");

	return 0;
}