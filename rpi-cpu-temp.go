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
	buf := make([]byte, 5)
	n, _ := file.Read(buf)
	fmt.Println("buf = ", string(buf[:n]))
	ori_temp := string(buf)
        f, err := strconv.ParseFloat(ori_temp, 64)
        if err != nil {
           fmt.Printf("cann't convert rpi_cpu_temp str to float64 err_msg:[%s]",err.Error())
        }
        rpi_temp := fmt.Sprintf("%2.2f", f/1000)
        return rpi_temp
}
