<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
  <meta http-equiv="Cache-control" content="no-cache">
  <meta http-equiv='refresh' content='600';url='index.php'> <!-- Refreshes page every 600 seconds -->
  <META NAME="description" CONTENT="Meusydd Weather Station">
  <META  HTTP-EQUIV="EXPIRES"  CONTENT="Mon, 31 Dec 2002 23:59:59 GMT">  
  <META NAME="keywords" CONTENT="GPRS weather station llanbedrgoch meusydd">

  <link REL="SHORTCUT ICON" HREF="goat.ico">
  <title>Meusydd Weather Station 2</title>
  <script src="http://www.goatindustries.co.uk/weather/amcharts/amcharts/amcharts.js"></script>
  <script src="http://www.amcharts.com/lib/3/gauge.js"></script>
  <script src="http://www.amcharts.com/lib/3/serial.js"></script>  
  <script src="http://www.amcharts.com/lib/3/plugins/dataloader/dataloader.min.js"></script>
</html>
<?php
include ("getid.php");
 ?>
 <script>
    myCallback();    
    var intervalID = window.setInterval(myCallback, 120000);
    function myCallback() {
    
    var chart1 = AmCharts.makeChart( "chartdivtempgauge", {
    "type": "gauge",
    "faceBorderWidth":2,
    "startDuration": 0,
    "dataLoader": {
    "url": "data/datatemp01.php",   
        "timestamp": true,
 
        "complete": function(chart) {
         chart.invalidateSize();
         
        }
        },
    "titles":
     [
     {
    "text": "Temperatures",
    "size": 15
    }
    ],
    "axes": [
    {
    "bands": [
    {
    //  DARK BLUE
    "startValue": -20,
    "endValue": -10,
    "radius": 140,
    "innerRadius": 150,
    "color": "#0000ff"
    },
    {
    //  LIGHT BLUE
    "startValue": -10,
    "endValue": 0,
    "radius": 140,
    "innerRadius": 150,
    "color": "#00acff"
    },						
    {
    //  ORANGE
    "startValue": 15,
    "endValue": 25,
    "radius": 140,
    "innerRadius": 150,
    "color": "#ffa500"
    },
    {
    //  RED
    "startValue": 25,
    "endValue": 40,
    "radius": 140,
    "innerRadius": 150,
    "color": "#ff0000"
    },
    {
    //  GREEN
    "startValue": 0,
    "endValue": 15,
    "radius": 140,
    "innerRadius": 150,
    "color": "#008000"
    },
    {
    //  BORDER GREY
    "startValue": -20,
    "endValue": 40,
    "radius": 148,
    "innerRadius": 150,
    "color": "#323232"
    }
    ],
        "id": "axis1",
        "axisAlpha": 0,
        "endAngle": 130,
        "startValue": -20,
        "endValue": 40,
        "minorTickInterval": 0.5,
        "showFirstLabel": false,
        "startAngle": -130,
        "topTextYOffset": 50,
        "valueInterval": 5,
        "bottomText": "Degrees C",
        "radius": 150
      }, {
        "id": "axis2",
        "axisAlpha": 0,
        "endAngle": 130,
        "startValue": -20,
        "endValue": 40,
        "radius": 100,
        "showFirstLabel": false,
        "startAngle": -130,
        "valueInterval": 5,
        "labelFrequency": 1,
        "valueInterval": 5
      } ]
    } );
    
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 var chart7 = AmCharts.makeChart( "chartdivhumiditygauge", {
        "type": "gauge",
        "faceBorderWidth":2,
        "startDuration": 0,
        "dataLoader": {
        "url": "data/datahumidity01.php",  
        "timestamp": true, 
        "complete": function(chart) {
         chart.invalidateSize();
        }
        }, 
        "titles":
    [
    {
        "text": "Humidity",
        "size": 15
    }
    ],
        "axes": [
    {
        "bands": [
   {
//  BORDER GREY
        "startValue": 0,
        "endValue": 100,
        "radius": 69,
        "innerRadius": 70,
        "color": "#323232"
   }
   ],
        "id": "axis1",
        "axisAlpha": 0,
        "endAngle": 130,
        "startValue": 0,
        "endValue": 100,
        "minorTickInterval": 5,
        "showFirstLabel": false,
        "startAngle": -130,
        "topTextYOffset": 100,
        "valueInterval": 10,
        "radius": 70,
        "labelOffset": 3
        
    }
    ]
    });
//////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 var chart10 = AmCharts.makeChart( "chartdivpressuregauge", {
        "type": "gauge",
        "faceBorderWidth":2,
        "startDuration": 0,
        "dataLoader": {
        "url": "data/dataPressureSwing01.php",  
        "timestamp": true, 
        "complete": function(chart) {
         chart.invalidateSize();
        }
        }, 
        "titles":
    [
    {
        "text": "Pressure Swing",
        "size": 15
    }
    ],
        "axes": [
    {
        "bands": [
   {
//  BORDER GREY
        "startValue": -10,
        "endValue": 10,
        "radius": 69,
        "innerRadius": 70,
        "color": "#323232"
   }
   ],
        "id": "axis1",
        "axisAlpha": 0,
        "endAngle": 130,
        "startValue": -5,
        "endValue": 5,
        "minorTickInterval": 0.5,
        "showFirstLabel": false,
        "startAngle": -130,
        "topTextYOffset": 50,
        "valueInterval": 1,
        "radius": 70,
        "labelOffset": 3
        
    }
    ]
    });
//////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////
 var chart7 = AmCharts.makeChart( "chartdivmoisturegauge", {
        "type": "gauge",
        "faceBorderWidth":2,
        "startDuration": 0,
        "dataLoader": {
        "url": "data/datamoisture01.php",  
        "timestamp": true, 
        "complete": function(chart) {
         chart.invalidateSize();
        }
        }, 
        "titles":
    [
    {
        "text": "Soil Moisture",
        "size": 15
    }
    ],
        "axes": [
    {
        "bands": [
   {
      //  RED
      "startValue": 0,
      "endValue": 30,
      "radius": 63,
      "innerRadius": 70,
      "color": "#ff0000"
      },					
      {
      //  ORANGE
      "startValue": 30,
      "endValue": 65,
      "radius": 63,
      "innerRadius": 70,
      "color": "#ffa500"
      },
      {
      //  GREEN
      "startValue": 65,
      "endValue": 100,
      "radius": 63,
      "innerRadius": 70,
      "color": "#008000"
      },
      {
//  BORDER GREY
        "startValue": 0,
        "endValue": 100,
        "radius": 69,
        "innerRadius": 70,
        "color": "#323232"
   }
   ],
        "id": "axis1",
        "axisAlpha": 0,
        "endAngle": 130,
        "startValue": 0,
        "endValue": 100,
        "minorTickInterval": 5,
        "showFirstLabel": false,
        "startAngle": -130,
        "topTextYOffset": 100,
        "valueInterval": 10,
        "radius": 70,
        "labelOffset": 3
    }
    ]
    });
////////////////////////////////////////////////////////////////////////////////////    
////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////     
////////////////////////////////////////////////////////////////////////////////////
       var chart2 = AmCharts.makeChart( "chartdivvoltsgauge", {
      "type": "gauge",
      "faceBorderWidth":2,
      "startDuration": 0,
        "dataLoader": {
        "url": "data/datavolts01.php", 
        "timestamp": true, 
        "complete": function(chart) {
         chart.invalidateSize();
        }
        },      
      "titles": 
      [
      {
      "text": "Battery Volts",
      "size": 15
      }
      ],	  	  
      "axes": [ 
      {	  
      "bands": [
      {
      //  RED
      "startValue": 8,
      "endValue": 12,
      "radius": 45,
      "innerRadius": 50,
      "color": "#ff0000"
      },					
      {
      //  ORANGE
      "startValue": 15,
      "endValue": 17,
      "radius": 45,
      "innerRadius": 50,
      "color": "#ffa500"
      },
      {
      //  RED
      "startValue": 17,
      "endValue": 18,
      "radius": 45,
      "innerRadius": 50,
      "color": "#ff0000"
      },
      {
      //  GREEN
      "startValue": 12,
      "endValue": 15,
      "radius": 45,
      "innerRadius": 50,
      "color": "#008000"
      },
      {
      //  BORDER GREY
      "startValue": 11,
      "endValue": 18,
      "radius": 49,
      "innerRadius": 50,
      "color": "#323232"
      }			
			    ],  
        "id": "axis1",
        "axisAlpha": 0,
        "endAngle": 130,
	"startValue": 8,
        "endValue": 18,
        "minorTickInterval": 0.2,
        "showFirstLabel": false,
        "startAngle": -130,
        "topTextYOffset": 50,
        "valueInterval": 1,
        "radius": 50,
        "labelOffset": 0
      }
      ]
    } );
////////////////////////////////////////////////////////////////////////////////////
    var chart3 = AmCharts.makeChart( "chartdivwindspeedgauge", {
      "type": "gauge",
      "faceBorderWidth":2,
      "startDuration": 0,
      "dataLoader": {
      "url": "data/datawind01.php", 
        "timestamp": true,  
        "complete": function(chart) {
         chart.invalidateSize();
        }
        },         
      "titles":
    [
    {
       "text": "Wind Speed",
       "size": 15
    }
    ],
       "axes": [
    {
       "bands": [
    {
     "startValue": 25,
     "endValue": 50,
     "radius": 140,
     "innerRadius": 150,
     "color": "#ffa500"
    },
    {
    "startValue": 50,
    "endValue": 80,
    "radius": 140,
    "innerRadius": 150,
    "color": "#ff0000"
    },
    {
    "startValue": 0,
    "endValue": 25,
    "radius": 140,
    "innerRadius": 150,
    "color": "#008000"
    },
    {
    "startValue": 0,
    "endValue": 80,
    "radius": 148,
    "innerRadius": 150,
    "color": "#323232"
    }
    ],
    //  "axisThickness": 2,
    //	"bandOutlineThickness": 5,
        "id": "axis1",
        "axisAlpha": 0,
        "endAngle": 130,
        "endValue": 80,
        "minorTickInterval": 0.5,
        "showFirstLabel": false,
        "startAngle": -130,
        "topTextYOffset": 10,
        "bottomText": "mph",
        "valueInterval": 5,
        "radius": 150
    }, {
        "id": "axis2",
        "axisAlpha": 0,
        "endAngle": 130,
        "endValue": 80,
        "radius": 100,
        "showFirstLabel": false,
        "startAngle": -130,
        "valueInterval": 5,
        "labelFrequency": 1,
        "valueInterval": 5
      } ]
    });
////////////////////////////////////////////////////////////////////////////////////
    var chart4 = AmCharts.makeChart( "chartdivwindwaygauge", {
      "type": "gauge",
      "faceBorderWidth":2,
      "startDuration": 0,
      "dataLoader": {
      "url": "data/datawindway01.php", 
        "timestamp": true,  
        "complete": function(chart) {
         chart.invalidateSize();
        }
        },
      "titles": 
      [
      {
      "text": "Wind Direction",
      "size": 15
      }
      ],	  	  
      "axes": [ 
      {	  
      "bands": [
      {
      //  BORDER GREY
      "startValue": 0,
      "endValue": 360,
      "radius": 69,
      "innerRadius": 70,
      "color": "#323232"
      }			
      ],  
        "id": "axis1",
        "axisAlpha": 0,
        "endAngle": 360,
        "startValue": 0,
        "endValue": 360,
        "minorTickInterval": 5,
        "showFirstLabel": false,
        "startAngle": 0,
        "topTextYOffset": 50,
        "valueInterval": 45,
        "radius": 70
      }
      ]
    } );
    
////////////////////////////////////////////////////////////////////////////////////
  
//////////////////////////////////////////////////////////////////////////////////		
    var chart6 = AmCharts.makeChart("chartdivRain01", {
       type: "serial",
      "dataLoader": {
      "url": "data/dataRain06.php",
        "timestamp": true,  
        "complete": function(chart) {
         chart.invalidateSize();
        }
        },
				
      categoryField: "time",
      startDuration: 0,
      categoryAxis: {
         // "parseDates": true
         gridPosition: "start",
         "labelRotation": "90",
      },
      valueAxes: [{
           position: "left",
           title: "Rainfall in mm",
           maximum: 50,
           minimum: 0,
           minorGridEnabled: true
         }],
       graphs: [

        {
           type: "column",
           title: "",
           valueField: "rainday",
           fillAlphas:1,
           fillColors: "#118CE5",
           lineColor: "#000000",
           balloonText: "<span style='font-size:13px;'>[[title]] in [[category]]:<b>[[value]]</b></span>"
        }
        ],
        legend: {
           useGraphSettings: true
        },
        creditsPosition:"top-right"
            });
///////////////////////////////////////////////////////////////////////////////////		
     var chart8 = AmCharts.makeChart("chartdivRainWeek01", {
     type: "serial",
      "dataLoader": {
      "url": "data/dataRain2Week01.php", 
        "timestamp": true,  
        "complete": function(chart) {
         chart.invalidateSize();
        }
        },
				
       categoryField: "day",
       startDuration: 0,
       categoryAxis: {
    // "parseDates": true
        gridPosition: "start",
       "labelRotation": "90",
      },
       valueAxes: [{
       position: "left",
       title: "Rainfall in mm",
       maximum: 50,
       minimum: 0,
       minorGridEnabled: true
       }],
       graphs: [
       {
       type: "column",
       title: "Calendar Day Rain (mm)",
       valueField: "rainday",
       fillAlphas:1,
       fillColors: "#118CE5",
       lineColor: "#000000",
        balloonText: "<span style='font-size:13px;'>[[title]] in [[category]]:<b>[[value]]</b></span>"
        }
        ],
        legend: {
        useGraphSettings: true
        },

        creditsPosition:"top-right"

        }); 
        
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
        }
//////////////////////////////////////////////////////////////////////////////////       
    </script> 
    
    <style type="text/css">
<!--
#clock {
    padding: 10px;
    position:absolute;
    left: 50px;
    top: 50px;
    z-index:1;
    color: black;
}
#Layer2 {
	position:absolute;
	width:1000px;
	height:1000px;
	z-index:1;
	left: 0px;
	top: 0px;
}
#Layer5 {
	position:absolute;
	width:450px;
	height:50px;
	z-index:1;
	left: 300px;
	top: 0px;
}
#Layer6 {
	position:absolute;
	width:1000px;
	height:100px;
	z-index:1;
	left: 0px;
	top: 850px;
}
#Layer7 {
	position:absolute;
	width:100px;
	height:30px;
	z-index:1;
	left: 847px;
	top: 443px;
}
#Layer8 {
	position:absolute;
	width:200px;
	height:30px;
	z-index:1;
	left: 347px;
	top: 550px;
}
#Layer9 {
	position:absolute;
	width:250px;
	height:30px;
	z-index:5;
	left: 10px;
	top: 870px;
}
#MenuLayer {
	position:absolute;
	width:350px;
	height:60px;
	z-index:5;
        left: 265px;
	top: 470px;
}
.style1 {
	font-size: 20px;
	font-weight: bold;
}
</style>			
</head>
           
<style type="text/css">
  ul {list-style: none;padding: 0px;margin: 0px;}
  ul li {display: block;position: relative;float: left;border:1px solid #000}
  li ul {display: none;}
  ul li a {display: block;background: #FFA;padding: 5px 10px 5px 10px;text-decoration: none;
           white-space: nowrap;color: #000;}
  ul li a:hover {background: #f0f;}
  li:hover ul {display: block; position: absolute;}
  li:hover li {float: none;}
  li:hover a {background: #47c;}
  li:hover li a:hover {background: #4d2;}
  #drop-nav li ul li {border-top: 0px;}
</style>

<body>
<div id="MenuLayer"><ul id="drop-nav">
  <li><a href="http://www.goatindustries.co.uk/weather/">Home</a>
    <ul>
      <li><a href="http://www.goatindustries.co.uk/weather/">Home</a></li>
    </ul>
  </li>
    <li><a href="http://www.goatindustries.co.uk/weather2/alltimerecords.php">All Time Records</a>

  </li>
  <li><a href="#">Graphs</a>
    <ul>
      <li><a href="http://www.goatindustries.co.uk/weather/plain.html">Rain and Pressure</a></li>
      <li><a href="http://www.goatindustries.co.uk/weather/temperatures.html">Temperatures</a></li>
      <li><a href="#">Wind Speed</a></li>
      <li><a href="#">Wind Direction</a></li>
      <li><a href="#">Humidity</a></li>
      <li><a href="http://www.goatindustries.co.uk/weather/pressure.html">Pressure</a></li>
      <li><a href="http://www.goatindustries.co.uk/weather/rainfall.html">Rainfall</a></li>
      <li><a href="#">Volts</a></li>	  	  	  
    </ul>
  </li>
  <li><a href="http://www.goatindustries.co.uk/">Contact</a>
    <ul>
      <li><a href="http://www.goatindustries.co.uk/">General Inquiries</a></li>
    </ul>
  </li>
</ul></div>

  	<div id="chartdivRain01" style="position: absolute; left: 30px; top: 520px; width:130px; height:350px; z-index: 3"></div>
  	<div id="chartdivRainWeek01" style="position: absolute; left: 140px; top: 520px; width:800px; height:341px; z-index: 3"></div>  	
     	<div id="chartdivPressure" style="position: absolute; left: 460px; top: 530px; width:530px; height:590px; z-index: 3"></div>
  	<div id="chartdivhumiditygauge" style="position: absolute; left: 800px; top: 15px; width:200px; height:180px; z-index: 3"></div>
  	<div id="chartdivpressuregauge" style="position: absolute; left: 800px; top: 320px; width:200px; height:180px; z-index: 3"></div>
  	<div id="chartdivwindwaygauge" style="position: absolute; left: 10px; top: 320px; width:200px; height:190px; z-index: 3"></div>
    	<div id="chartdivwindspeedgauge" style="position: absolute; left: 485px; top: 90px; width:400px; height:330px; z-index: 3"></div>
        <div id="chartdivtempgauge" style="position: absolute; left: 135px; top: 90px; width:400px; height:330px; z-index: 3"></div>
  	<div id="chartdivmoisturegauge" style="position: absolute; left: 10px; top: 15px; width:200px; height:180px; z-index: 3"></div>
  	<div id="chartdivvoltsgauge" style="position: absolute; left: 410px; top: 40px; width:200px; height:140px; z-index: 3"></div>  	
	
    <div id="Layer2"></div>
    <div id="Layer1" style="position: absolute; left: 10px; top: 12px; width: 900px; height: 20px; z-index: 4"></div>
    <span style="position: absolute; left: 610px; top: 465px; width: 148px; height: 20px; z-index: 4"><a href="http://www.goatindustries.co.uk/"><img src="images/goatlogo.png" border="0"></a></span>	
    <span style="position: absolute; left: 340px; top: 400px; width: 148px; height: 20px; z-index: 4"><img src="images/key01.png"></span>
    
    
    
	
    <div id="layer5"><table width="500" height="60" border="0" cellpadding="2" cellspacing="2" id="Layer5" >
    <tr>
    <td bgcolor="#FFFFFF"><div align="center">
    <?echo $dayhourminutes;?>
  Meusydd Weather Station, Llanbedrgoch, UK. Java script by <a href="https://www.amcharts.com/">Amcharts</a>
    </div></td>
    </tr>
    <tr>
    <td bgcolor="#FFFFFF"><div align="center"></div></td>
    </tr>
    </table>
    </div>
    
    
    
    <div id="layer7"><table width="400" height="40" border="0" cellpadding="1" cellspacing="1" id="Layer7" >
    <tr>
    <td bgcolor="#FFFFFF"><div align="center">
<?    
echo $pressure;
?>    
    </div></td>
    </tr>
    <tr>
    <td bgcolor="#FFFFFF"><div align="center">mbar</div></td>
    </tr>
    </table>
    </div>    
    
    <div id="layer8"><table width="400" height="40" border="0" cellpadding="0" cellspacing="0" id="Layer8" >
    <tr>
    <td bgcolor="#FFFFFF"><div align="center">Rain in last 2 weeks: 
<?    
echo $rain;
?> mm
    </div></td>
    </tr>
    <tr>
    <td bgcolor="#FFFFFF"><div align="center"></div></td>
    </tr>
    </table>
    </div> 
    
    <div id="layer9"><table width="400" height="40" border="0" cellpadding="0" cellspacing="0" id="Layer9" >
    <tr>
    <td bgcolor="#FFFFFF"><div align="center">
<?
echo "ID: ";
echo $id;
echo " on ";
echo $dayhourminutes;
?>
    </div></td>
    </tr>
    <tr>
    <td bgcolor="#FFFFFF"><div align="center"></div></td>
    </tr>
    </table>
    </div>      
        
    
    <div id="layer6"><table width="1000" height="500" border="0" cellpadding="2" cellspacing="2" id="Layer6" >
    <tr>
    <td bgcolor="#FFFFFF">

    <? include ("data/showdata.php"); ?>
 
    </td>
    </tr>
    </table>
    </div>  
      
    </body>
    </html>