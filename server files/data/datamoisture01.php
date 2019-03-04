<?php
 
$username = "*************";
$password = "*************";
$hostname = "localhost"; 
$databasetable = "*************";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("*************",$dbhandle) 
or die("Could not select database");

   $moisturemax = -100;
   $moisturemin = 100;
   $moisture = 0;
/////////////////////////////////////////////////////////////////////////////  
//////  Use the while loop to further sort the data as SELECT wont do it //// 
   $query4="SELECT * FROM ************* ORDER BY id DESC LIMIT 1000";
   $result4=mysql_query($query4);
while($row4=mysql_fetch_array($result4))
   {  
   if ($row4['moisture'] > $moisturemax)
   { $moisturemax = $row4['moisture']; }
   if (($row4['moisture'] < $moisturemin) & ($row4['moisture']||0))
   { $moisturemin = $row4['moisture']; }
   }
   
////////////////////////////////////////////////////////////////////////////   
////////////////////////////////////////////////////////////////////////////  
   $query5="SELECT * FROM ************* ORDER BY id DESC LIMIT 1";
   $result5=mysql_query($query5);
while($row5=mysql_fetch_array($result5))
   {  
   $moisture = $row5['moisture'];
   }
   
$orange = '  "color": "#ffa500", ';
$red = '  "color": "#FF0000", ';
$blue =  '  "color": "#0000FF", ';
$green =  '  "color": "#008000", ';
$black =  '  "color": "#000000", ';
$radius01 = '  "radius": "90%", ';
$radius02 = '  "radius": "50%", ';

$moisturemax = $moisturemax -1;
$moisture = $moisture -1;
$moisturemin = $moisturemin -1;

$prefix = '';
echo "[\n";
//while ( $row = mysql_fetch_assoc( $result ) ) {
  
  echo $prefix . " {\n";  
  echo $red;  
  echo '  "value": ' . $moisturemax . '},{' . "\n";
  echo $black;
  echo '  "value": ' . $moisture . '},{' . "\n";
  echo $blue;  
  echo '  "value": ' . $moisturemin . '' . "\n";    
  echo " }";
  $prefix = ",\n";
//}
  echo "\n]";   

// close MySQL connection 
mysql_close();
 ?>