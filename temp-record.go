package main

import (
	"database/sql"
	"fmt"
	_ "github.com/go-sql-driver/mysql"
	"time"
)

//Db数据库连接池
var DB *sql.DB

func InitMySQL() {
	DB, _ = sql.Open("mysql", "root:5XSwBxGx@tcp(localhost:3306)/Temps?parseTime=true&loc=Local")
	//设置数据库最大连接数
	DB.SetConnMaxLifetime(100)
	//设置上数据库最大闲置连接数
	DB.SetMaxIdleConns(10)
	//验证连接
	if err := DB.Ping(); err != nil {
		lg.Infof("open database fail")
		return
	}
	lg.Infof("MySQL Server connnect success")
}

func Insert(temp, humi, cpu_temp string, update_time time.Time) bool {
	//开启事务
	tx, err := DB.Begin()
	if err != nil {
		lg.Infof("tx fail")
		return false
	}
	//准备sql语句
	//使用sql now()命令来获取插入的时间
	stmt, err := tx.Prepare("INSERT INTO pi_temps(temp, humi,rpi_cpu_temp,update_time) VALUES(?, ?, ?, ?)")
	if err != nil {
		lg.Infof("Prepare fail")
		return false
	}
	//将参数传递到sql语句中并且执行
	res, err := stmt.Exec(temp, humi, cpu_temp, update_time)
	if err != nil {
		lg.Infof("Exec fail")
		return false
	}
	//将事务提交
	tx.Commit()
	//获得上一个插入自增的id
	fmt.Println(res.LastInsertId())
	return true
}
