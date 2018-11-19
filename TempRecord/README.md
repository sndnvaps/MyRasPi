# pickup example from http://curran.blog.51cto.com/2788306/533169

# dep
	apt-get install -y libmysqlclient-dev 

# create database with sql file 
	$ mysql -u root -p < create-table-mysql.sql

# build example file 

	$ mkdir build && cd build && cmake ../ && make  
	# it just build the libTempRecord




