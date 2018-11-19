#ifndef RECORD_TEMP_HPP
#define RECORD_TEMP_HPP 
#include <mysql/mysqld_error.h>
namespace RPI_TEMP_RECORD {
		void insert(std::string temp, std::string hum,std::string pi_cpu_temp);
		//void insert(std::string temp, std::string hum, std::string pi_cpu_temp);
}

#endif

