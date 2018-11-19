CREATE DATABASE IF NOT EXISTS Temps DEFAULT CHARSET utf8 COLLATE utf8_general_ci;
use Temps;
set charset utf8;

DROP TABLE IF EXISTS pi_temps;

CREATE TABLE pi_temps (
	id int(8) unsigned NOT NULL AUTO_INCREMENT,
	name varchar(30) NOT NULL DEFAULT 'DHT.RPI_RECORDER' ,
	temp varchar(5) NOT NULL DEFAULT '0.0' COMMENT 'DHT.Temperature',
	humi varchar(5) NOT NULL DEFAULT '0.0' COMMENT 'DHT.Humidity',
	rpi_cpu_temp varchar(6) NOT NULL DEFAULT '0.0' COMMENT 'RPI.CPU.Temperature',
	update_time datetime NOT NULL COMMENT 'update time',
	PRIMARY KEY (id)
) charset=utf8;
/*
ALTER TABLE pi_temps add update_time datetime NOT NULL COMMENT 'update time';
ALTER TABLE pi_temps add pi_cpu_temp varchar(6) NOT NULL DEFAULT '0.0' COMMENT 'RPI.CPU.Temperature';
*/



