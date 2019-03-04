<?php
 
$username = "*************";
$password = "*************";
$hostname = "localhost"; 
$databasetable = "*************";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("*************",$dbhandle) 
or die("Could not select database");
///////////////////////////////////////////////////////////////////////////////////////

   $query6="SELECT `windgust` FROM ************* ORDER BY id DESC LIMIT 144";
   $result6=mysql_query($query6);
   $runningrow6 = 0;
   
while ( $row6 = mysql_fetch_assoc( $result6 ) ) 
{
if ($row6['windgust'] > $runningrow6)
    {
    $runningrow6 = $row6['windgust'];   
    }
}
$windgust = $runningrow6;
// echo $windgust;


////////////////////////////////////////////////////////////////////////////////////////
   $query6="SELECT * FROM ************* ORDER BY id DESC LIMIT 1";
   $result6=mysql_query($query6);
  
// Print out row

$orange = '  "color": "#FFA500", ';
$red = '  "color": "#FF0000", ';
$blue =  '  "color": "#0000FF", ';
$green =  '  "color": "#008000", ';
$black =  '  "color": "#000000", ';
$radius01 = '  "radius": "70%", ';
$radius02 = '  "radius": "50%", ';

$prefix = '';
echo "[\n";
while ( $row6 = mysql_fetch_assoc( $result6 ) ) {
  
  echo $prefix . " {\n";  
  echo $red;
  echo $radius01;
  //Knots to MPH multiply by 1.15077944802
  echo '  "value": ' . $windgust*1.15077944802 . '},{' . "\n";
  echo $black;  
  echo $radius02;  
  echo '  "value": ' . $row6['windspeed']*1.15077944802 . '' . "\n";    
  echo " }";
  $prefix = ",\n";
}
echo "\n]";



// close MySQL connection 
//mysql_close();
 ?>