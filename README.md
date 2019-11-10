1. Install go first
2. go get -u github.com/d2r2/go-dht
3. git clone https://github.com/sndnvaps/MyRasPi -b go-dht22 $GOPATH/src/github.com/sndnvaps/MyRasPi
4. change dht22.go#L48, set it for youself
5. go build
6. install docker && docker-compose
7. run mysql server with cmd: docker-compose up 
8. $ ./MyRasPi # Print out the Temperature & Humidity info of DHT22 and insert it into mysql server
9. get the temp & humi from web: (https://rpi_pi:8080/echart.php](https://rpi_ip:8080/echart.php)
