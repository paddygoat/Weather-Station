<?php
 
$username = "*************";
$password = "*************";
$hostname = "localhost"; 
$databasetable = "*************";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("*************",$dbhandle) 
or die("Could not select database");

   $voltsmax = -100;
   $voltsmin = 100;
   $volts = 0;
/////////////////////////////////////////////////////////////////////////////  
//////  Use the while loop to further sort the data as SELECT wont do it //// 
   $query3="SELECT * FROM ************* ORDER BY id DESC LIMIT 144";
   $result3=mysql_query($query3);
while($row3=mysql_fetch_array($result3))
   {  
   if ($row3['volts'] > $voltsmax)
   { $voltsmax = $row3['volts']; }
   if (($row3['volts'] < $voltsmin) & ($row3['volts']||0))
   { $voltsmin = $row3['volts']; }
   }
   
////////////////////////////////////////////////////////////////////////////   
////////////////////////////////////////////////////////////////////////////  
   $query1="SELECT * FROM ************* ORDER BY id DESC LIMIT 1";
   $result1=mysql_query($query1);
while($row1=mysql_fetch_array($result1))
   {  
   $volts = $row1['volts'];
   }
  
// Outputs are: $voltsmin , $voltsmax , $volts
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
  echo '  "value": ' . $voltsmax . '},{' . "\n";
  echo $black;
  echo '  "value": ' . $volts . '},{' . "\n";
  echo $blue;  
  echo '  "value": ' . $voltsmin . '' . "\n";    
  echo " }";
  $prefix = ",\n";
//}
  echo "\n]";



// close MySQL connection 
mysql_close();
 ?>