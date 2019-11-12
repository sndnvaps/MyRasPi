<!DOCTYPE html>
<html style="height: 100%">
   <head>
       <meta charset="utf-8">
   </head>
   <body style="height: 100%; margin: 0">
       <div id="container" style="height: 100%"></div>
       <script type="text/javascript" src="src/echarts.min.js"></script>
       <script type="text/javascript" src="src/jquery.min.js"></script>

       <script type="text/javascript">

var dom = document.getElementById("container");
var myChart = echarts.init(dom);
var app = {};
option = null;


    // 初始化三个数组，盛装从数据库中获取到的数据
    var temps = [];
    var humis = [];
    var update_times = [];

//调用ajax来实现异步的加载数据
    function getrecords() {
        $.ajax({
            type: "get",
            async: false,
            url: "getrecord.php?search=all",
            data: {},
            dataType: "json",
            success: function(result){
                if(result){
                    for(var i = 0 ; i < result.length; i++){
                        temps.push(result[i].temp);
                        humis.push(result[i].humi);
                        update_times.push(result[i].update_time);

                    }
                }
            },
            error: function(errmsg) {
                alert("Ajax获取服务器数据出错了！"+ errmsg);
            }
        });
    return temps,humis,update_times;
    }

getrecords();

// 调用ajax来实现异步的加载数据，只获取一条数据
    function getrecord() {
        $.ajax({
            type: "get",
            async: false,
            url: "getrecord.php?search=one",
            data: {},
            dataType: "json",
            success: function(result){
                if(result){
                    for(var i = 0 ; i < result.length; i++){
                        temps.push(result[i].temp);
                        humis.push(result[i].humi);
                        update_times.push(result[i].update_time);

                    }
                }
            },
            error: function(errmsg) {
                alert("Ajax获取服务器数据出错了！"+ errmsg);
            }
        });
    return temps,humis,update_times;
    }

option = {

    // Make gradient line here
    visualMap: [{
        show: false,
        type: 'continuous',
        seriesIndex: 0,
        min: 0,
        max: 400
    }, {
        show: false,
        type: 'continuous',
        seriesIndex: 1,
        dimension: 0,
        min: 0,
        max: update_times.length - 1
    }],


    title: [{
        left: 'center',
        text: '温度曲线'
    }, {
        top: '55%',
        left: 'center',
        text: '湿度曲线'
    }],
    tooltip: {
        trigger: 'axis'
    },
    xAxis: [{
        data: update_times
    }, {
        data: update_times,
        gridIndex: 1
    }],
    yAxis: [{
        splitLine: {show: false},
        axisLabel: {
            formatter: '{value} °C'
        }
    }, {
        splitLine: {show: false},
        axisLabel: {
            formatter: '{value} %'
        },
        gridIndex: 1
    }],
    grid: [{
        bottom: '60%'
    }, {
        top: '60%'
    }],
    series: [{
        type: 'line',
        showSymbol: false,
        data: temps,
    }, {
        type: 'line',
        showSymbol: false,
        data: humis,
        xAxisIndex: 1,
        yAxisIndex: 1
    }]
};;

//myChart.setOption(option,true);

//Refresh every 30 sec
setInterval(function() {
    getrecord();
   // var myChart = echarts.init(document.getElementById('container'));
    myChart.setOption({
      xAxis: [{
        data: update_times
        }, {
        data: update_times,
        gridIndex: 1
        }],
       grid: [{
           bottom: '60%'
       }, {
          top: '60%'
       }],
       series: [{
          data : temps
       }, {
          data: humis,
          yAxisIndex: 1
       }]
      });
  },1000 * 30); //ReFresh 30 sec

if (option && typeof option == "object") {
     myChart.setOption(option,true);
}

       </script>
   </body>
</html>
