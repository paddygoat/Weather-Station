<?php
 
$username = "*************";
$password = "*************";
$hostname = "localhost"; 
$databasetable = "*************";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("*************",$dbhandle) 
or die("Could not select database");

   $humiditymax = -100;
   $humiditymin = 100;
   $humidity = 0;
/////////////////////////////////////////////////////////////////////////////  
//////  Use the while loop to further sort the data as SELECT wont do it //// 
   $query4="SELECT * FROM ************* ORDER BY id DESC LIMIT 144";
   $result4=mysql_query($query4);
while($row4=mysql_fetch_array($result4))
   {  
   if ($row4['humidity'] > $humiditymax)
   { $humiditymax = $row4['humidity']; }
   if ($row4['humidity'] < $humiditymin)
   { $humiditymin = $row4['humidity']; }
   }
   
////////////////////////////////////////////////////////////////////////////   
////////////////////////////////////////////////////////////////////////////  
   $query5="SELECT * FROM ************* ORDER BY id DESC LIMIT 1";
   $result5=mysql_query($query5);
while($row5=mysql_fetch_array($result5))
   {  
   $humidity = $row5['humidity'];
   }
  
// Outputs are: $humiditymin , $humiditymax , $humidity
// Print out row

$orange = '  "color": "#ffa500", ';
$red = '  "color": "#FF0000", ';
$blue =  '  "color": "#0000FF", ';
$green =  '  "color": "#008000", ';
$black =  '  "color": "#000000", ';
$radius01 = '  "radius": "90%", ';
$radius02 = '  "radius": "50%", ';

$prefix = '';
echo "[\n";
//while ( $row = mysql_fetch_assoc( $result ) ) {
  
  echo $prefix . " {\n";  
  echo $red;  
  echo '  "value": ' . $humiditymax . '},{' . "\n";
  echo $black;
  echo '  "value": ' . $humidity . '},{' . "\n";
  echo $blue;  
  echo '  "value": ' . $humiditymin . '' . "\n";    
  echo " }";
  $prefix = ",\n";
//}
  echo "\n]";



// close MySQL connection 
mysql_close();
 ?>