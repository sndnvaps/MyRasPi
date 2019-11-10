package main

import (
	"github.com/d2r2/go-dht"
	logger "github.com/d2r2/go-logger"
	cron "gopkg.in/robfig/cron.v3"
	"os"
	"os/signal"
	"syscall"
)

var (
	lg = logger.NewPackageLogger("main",
		//logger.DebugLevel,
		logger.InfoLevel,
	)
	sensorType = dht.AM2302
	pin        = 4
)

func RunEveryMinutes() {
	c := cron.New()
	//Every Minutes go Read the dht22 info
	c.AddFunc("*/1  * * * *", GetDhtxxData)
	// 开始
	c.Start()
	//defer c.Stop()
	select {}
}
func GetDhtxxData() {
	// Read DHT22 sensor data from specific pin, retrying 10 times in case of failure.
	temperature, humidity, retried, err := dht.ReadDHTxxWithRetry(sensorType, pin, false, 10)
	// Uncomment/comment next line to suppress/increase verbosity of output
	logger.ChangePackageLogLevel("dht", logger.InfoLevel)
	if err == nil {
		lg.Infof("Sensor = %v: Temperature = %v*C, Humidity = %v%% (retried %d times)",
			sensorType, temperature, humidity, retried)
	}

}

func main() {
	logger.EnableSyslog(true)
	logger.SetLogFileName("MyRasPi.log")
	defer logger.FinalizeLogger()
	signalChan := make(chan os.Signal, 1)
	signal.Notify(signalChan, syscall.SIGINT, syscall.SIGTERM,syscall.SIGKILL, os.Interrupt)
	go func() {
		for {
			select {
			case <-signalChan:
		                lg.Infof("正在结束！")
				os.Exit(0)
			}
		}
	}()
	RunEveryMinutes()

}
