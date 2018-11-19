//install dep 
//TODO: you must install mysql-server 
//apt-get install -y libmysqlclient-dev libmysql++-dev libmysqlcppconn-dev

//compile guide
//$ g++ -o rt -lmysqlclient -I/usr/include/mysql =L/usr/lib/mysql 

#include <iostream>
#include <string>
//#include <mysql++/mysql++.h>
#include <mysql/mysql.h> 
#include "record_temp.hpp"

using namespace std;

#define DB_NAME "Temps"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PWD   "447826004"


/*
void RPI_TEMP_RECORD::RPI_TEMP_RECORD::Insert(string temp, string hum) {
		MYSQL	 mysql;
		mysql_init(&mysql);
		mysql_real_connect(&mysql,DB_HOST,DB_USER,DB_PWD,DB_NAME,3306,NULL,0);
		
			string sqlstr = "INSERT INTO pi_temps (temp, humi,update_time) VALUES(" + temp + "," + hum + ", now()" + ");";	
			cout << "SQLCMD =" << sqlstr << endl;
			mysql_query(&mysql,sqlstr.c_str());
			mysql_close(&mysql);
	 
}
*/
void RPI_TEMP_RECORD::insert(std::string temp, std::string hum,std::string pi_cpu_temp){
		MYSQL	 mysql;
		mysql_init(&mysql);
		mysql_real_connect(&mysql,DB_HOST,DB_USER,DB_PWD,DB_NAME,3306,NULL,0);
		
			string sqlstr = "INSERT INTO pi_temps (temp, humi,rpi_cpu_temp,update_time) VALUES(" + temp + "," + hum + "," + pi_cpu_temp + ", now()" + ");";	
			cout << "SQLCMD =" << sqlstr << endl;
			mysql_query(&mysql,sqlstr.c_str());
			mysql_close(&mysql);
	 
}



