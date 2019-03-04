<?php
 
$username = "*************";
$password = "*************";
$hostname = "localhost"; 
$databasetable = "*************";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("*************",$dbhandle) 
or die("Could not select database");

   $pressure = 0;
   $n=0;
   $pressureChange = 0; 
  
/////////////////////////////////////////////////////////////////////////////  

   $query4="SELECT * FROM *************ORDER BY id DESC LIMIT 6";
   $result4=mysql_query($query4);
   
while($row4=mysql_fetch_array($result4))
   {
   $n=$n+1;
   $age[$n] = $row4['pressure'];  
   }  
////////////////////////////////////////////////////////////////////////////////  
              
     $pressureChange = $age[1] - $age[6];
     $pressureChange = number_format($pressureChange,3)/100;
 //    echo $pressureChange;
   
////////////////////////////////////////////////////////////////////////////   
////////////////////////////////////////////////////////////////////////////  
   $query5="SELECT * FROM ************* ORDER BY id DESC LIMIT 1";
   $result5=mysql_query($query5);
while($row5=mysql_fetch_array($result5))
   {  
   $pressure = $row5['pressure'];
   }

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
  echo $green;  
  echo '  "value": ' . $pressureChange . '' . "\n";    
  echo " }";
  $prefix = ",\n";
//}
  echo "\n]";



// close MySQL connection 
mysql_close();
 ?>