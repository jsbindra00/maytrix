#pragma once
#include <boost/filesystem.hpp>
#include <iostream>
#include <streambuf>
#include <fstream>
namespace nr {
	namespace utility {
		template<class DirectoryIteratorType>
		static std::vector<boost::filesystem::path> ListItems(const boost::filesystem::path& currentPath) {
			std::vector<boost::filesystem::path> res;
			DirectoryIteratorType begin(currentPath);
			DirectoryIteratorType end;
			std::copy(begin, end, std::back_insert_iterator<std::vector<boost::filesystem::path>>(res));
			return res;
		}
		template<class It1, class It2>
		static void PrintContainer(It1 start, It2 end) {
			std::for_each(start, end, [](const std::iterator_traits<It1>::value_type& item) {
				std::cout << item << "\n";
				});
		}
		static std::string ReadFile(const boost::filesystem::path& path) {
			if (!boost::filesystem::is_regular_file(path))
			{
				std::cout << "Non regular file" << std::endl;
				assert(true);
			}
			std::ifstream fileStream(path.string());
			if (!fileStream.is_open()) throw "";
			return { std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>() };
		}
		static boost::filesystem::path AddLeaf(boost::filesystem::path path, const std::string& leaf)
		{
			return path /= leaf;
		}
		static bool CreateFile(boost::filesystem::path path)
		{
			std::ofstream file(path.string());
			if (!file) return false;
			file.close();
			return true;
		}
	
	}
}

