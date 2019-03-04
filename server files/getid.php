<?php
 
$username = "**************";
$password = "**************";
$hostname = "localhost"; 
$databasetable = "**************";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("**************",$dbhandle) 
or die("Could not select database");

   $voltsmax = -100;
   $voltsmin = 100;
   $volts = 0;
   $rain = 0;

////////////////////////////////////////////////////////////////////////////   
    $query13= "SELECT * FROM **************
     WHERE time > DATE_SUB(NOW(), INTERVAL 13 DAY)
     ORDER BY id DESC";



 //  $query13="SELECT * FROM ************** ORDER BY id DESC LIMIT 2016";
   $result13=mysql_query($query13);
while($row13=mysql_fetch_array($result13))
   {  
   $rain = ($row13['rain']*0.2794)+$rain;
   }
   $rain = number_format($rain,2);
   //echo $rain;
////////////////////////////////////////////////////////////////////////////  
   $query12="SELECT * FROM ************** ORDER BY id DESC LIMIT 1";
   $result12=mysql_query($query12);
while($row12=mysql_fetch_array($result12))
   {  
   $id = $row12['id'];
   $timestamp = $row12['time'];
   $pressure = $row12['pressure'];
   }
   // Parse timestamp:  
      
      $epochtime = strtotime($timestamp);   
      $dayhourminutes = date("D M j H:i", $epochtime);
      $day = date("l", $epochtime);
      $hourminutes = date("H:i", $epochtime);
  
// Outputs are: $id and $dayhourminutes

// close MySQL connection 
mysql_close();
 ?>