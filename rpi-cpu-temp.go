package main

import (
	"fmt"
	"os"
	"strconv"
)

func RpiCpuTemp() string {
	temp_file := "/sys/class/thermal/thermal_zone0/temp"
	file, _ := os.Open(temp_file)
	defer file.Close()
	buf := make([]byte, 15)
	n, _ := file.Read(buf)
	//fmt.Println("buf = ", string(buf[:n]))
	f, _ := strconv.ParseFloat(string(buf[:n]), 64)
	rpi_temp := fmt.Sprintf("%2.2f%", f/1000)
	return rpi_temp
}
