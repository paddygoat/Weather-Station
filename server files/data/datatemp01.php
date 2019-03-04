<?php
 
$username = "*************";
$password = "*************";
$hostname = "localhost"; 
$databasetable = "*************";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("*************",$dbhandle) 
or die("Could not select database");

   $tempoutmax = -100;
   $tempoutmin = 100;
   $tempout = 0;
   $tempsoil = 0;
/////////////////////////////////////////////////////////////////////////////  
//////  Use the while loop to further sort the data as SELECT wont do it //// 
   $query3="SELECT * FROM ************* ORDER BY id DESC LIMIT 1008";
   $result3=mysql_query($query3);
while($row3=mysql_fetch_array($result3))
   {  
   if ($row3['tempout'] > $tempoutmax)
   { $tempoutmax = $row3['tempout']; }
   if (($row3['tempout'] < $tempoutmin) & ($row3['tempout']||0))
   { $tempoutmin = $row3['tempout']; }
   }
   
////////////////////////////////////////////////////////////////////////////   
////////////////////////////////////////////////////////////////////////////  
   $query1="SELECT * FROM ************* ORDER BY id DESC LIMIT 1";
   $result1=mysql_query($query1);
while($row1=mysql_fetch_array($result1))
   {  
   $tempout = $row1['tempout'];
   $tempsoil = $row1['tempsoil'];
   }
  
// Outputs are: $tempoutmin , $tempoutmax , $tempout , $tempsoil
// Print out row

$brown = '  "color": "#895900", ';
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
  echo $blue;
  echo '  "value": ' . $tempoutmin . '},{' . "\n";
  echo $red;  
  echo '  "value": ' . $tempoutmax . '},{' . "\n";
  echo $black;
  echo '  "value": ' . $tempout . '},{' . "\n";
  echo $brown;  
  echo $radius02;
  echo '  "value": ' . $tempsoil . '' . "\n";    
  echo " }";
  $prefix = ",\n";
//}
  echo "\n]";



// close MySQL connection 
//mysql_close();
 ?>