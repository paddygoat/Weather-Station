<?php
 
$username = "*************";
$password = "*************";
$hostname = "localhost"; 
$databasetable = "*************";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("*************",$dbhandle) 
or die("Could not select database");
   
////////////////////////////////////////////////////////////////////////////   
////////////////////////////////////////////////////////////////////////////  
   $query1="SELECT * FROM ************* ORDER BY id DESC LIMIT 1";
   $result1=mysql_query($query1);
while($rows=mysql_fetch_array($result1))
   {  
 
//if ($rows['windway'] == 1){$rows['windway'] = 0;}
//if ($rows['windway'] == 2){$rows['windway'] = 45;}
//if ($rows['windway'] == 3){$rows['windway'] = 90;}
//if ($rows['windway'] == 4){$rows['windway'] = 135;}
//if ($rows['windway'] == 5){$rows['windway'] = 180;}
//if ($rows['windway'] == 6){$rows['windway'] = 225;}
//if ($rows['windway'] == 7){$rows['windway'] = 270;}
//if ($rows['windway'] == 8){$rows['windway'] = 315;}

 $windway = $rows['windway'];
 // echo "Windway is:  "; echo $windway;
   }


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
  echo $black;  
  echo '  "value": ' . $windway . '' . "\n";    
  echo " }";
  $prefix = ",\n";
//}
  echo "\n]";



// close MySQL connection 
mysql_close();
 ?>