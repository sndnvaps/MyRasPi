# Generate config.h file with ccmake 
	apt-get install cmake-curses-gui 

#generate Makefile for build 
	cmake . 

#build 
	make 

#install
	make install 


#Test if we insert the temp into database 

	#select the lastest 10 record 
	select * from pi_temps where id > (select max(id) from pi_temps)-10;

	#select the lastest record 
	select * from pi_temps where id = (select max(id) from pi_temps);



