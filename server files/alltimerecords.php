<?php

 Header("Cache-Control: must-revalidate");
 $offset = 60;
 $ExpStr = "Expires: " . gmdate("D, d M Y H:i:s", time() - $offset) . " GMT";
 Header($ExpStr);

//echo("The current time is:");echo date("h i a");  
//echo(". The current day is:");echo date("d"); 
//echo(". The current month is:");echo date("m"); 
//echo(". Zero indicates not a leap year:");echo date("L"); 

$nowmonth = date("m"); 
$nowday = date("d");

include ("getid.php");
$host="localhost"; // Host name 
$username="**************"; // Mysql username 
$password="**************"; // Mysql password 
$db_name="**************"; // Database name 
$tbl_name="**************"; // Table name

   $query12="SELECT * FROM ************** ORDER BY id DESC LIMIT 1";
   $result12=mysql_query($query12);
while($row12=mysql_fetch_array($result12))
   {  
   $timestamp = $row12['time'];
   }
   
      $epochtime = strtotime($timestamp);   
      $timestamp = date("l, d F Y", $epochtime);

// Connect to server and select database.
mysql_connect("$host", "$username", "$password")or die("cannot connect"); 
mysql_select_db("$db_name")or die("cannot select DB");
//////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////  
   $tempoutmax = -100;
   $tempoutmin = 100;
   $tempout = 0;
   $tempsoil = 0;
   $windgustmax = -100;
   $windgustmin = 100;
   
   $maxGustDate = 0;
   $maxTempDate = 0;
   $minTempDate = 0;


   $query3="SELECT * FROM ************** ORDER BY id";
   $result3=mysql_query($query3);
   while($row3=mysql_fetch_array($result3))
   {  
   
   if ($row3['tempout'] > $tempoutmax)
   { $tempoutmax = $row3['tempout']; $maxTempDate = $row3['time'];}
   
   if ($row3['tempout'] < $tempoutmin)
   { $tempoutmin = $row3['tempout']; $minTempDate = $row3['time'];}
   
   if ($row3['windgust'] > $windgustmax)
   { $windgustmax = $row3['windgust']; $maxWindDate = $row3['time'];}  
   
   }
   
      // Parse timestamps:  
      
      $epochtime = strtotime($maxTempDate);   
      $maxTempDate = date("l, d F Y", $epochtime);
      $day = date("l", $epochtime);
      
      $epochtime = strtotime($minTempDate);   
      $minTempDate = date("l, d F Y", $epochtime);
      $day = date("l", $epochtime);
      
      $epochtime = strtotime($maxWindDate);   
      $maxWindDate = date("l, d F Y", $epochtime);
      $day = date("l", $epochtime);            

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////  
// Retrieve data from database 
 
$sql2="SELECT * FROM **************  ORDER BY id DESC LIMIT 1";
$result2=mysql_query($sql2);


  //Knots to MPH multiply by 1.15077944802
 while($rows=mysql_fetch_array($result2))
{

 print "The current time is "; echo date("h i a");
 print "<br>";
 print "The last readings were on "; echo $timestamp; 
 print " at "; echo $hourminutes; print " hours"; 
 print "<br>"; print "<br>";
 print "Maximum gust of "; echo round($windgustmax*1.15,1); print " MPH on "; echo $maxWindDate; 
 print "<br>"; print "<br>";
 print "Minimum temperature of "; echo round($tempoutmin,1); print " Degrees C on "; echo $minTempDate; 
 print "<br>"; 
 print "Maximum temperature of "; echo round($tempoutmax,1); print " Degrees C on "; echo $maxTempDate; 
 print "<br>"; 
 


}

// close MySQL connection 
mysql_close();
 ?>