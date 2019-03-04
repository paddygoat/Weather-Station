<?php
// we need this so that PHP does not complain about deprectaed functions
error_reporting( 0 );

// Connect to MySQL
$link = mysql_connect( 'localhost', '*************', 'whales' );
if ( !$link ) {
  die( 'Could not connect: ' . mysql_error() );
}

// Select the data base
$db = mysql_select_db( '*************', $link );
if ( !$db ) {
  die ( 'Error selecting database \'test\' : ' . mysql_error() );
}
   
   $rainday = 0;
//////////////////////////////////////////////////////////////////////////////////////////////////////
     $query9= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 1 DAY)
     ORDER BY id DESC";
	 $result9=mysql_query($query9);
     while ( $row9 = mysql_fetch_array( $result9 ) ) 
     {
     $rainday = $row9['rain']*0.2794 + $rainday;
     $timestamp = $row9['time'];
     } 
	 $rainday1 = $rainday;
   
   $epochtime = strtotime($timestamp);   
   $day2 = date("D", $epochtime);
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query10= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 2 DAY)
     ORDER BY id DESC";
	 $result10=mysql_query($query10);
	 $rainday = 0;
     while ( $row10 = mysql_fetch_array( $result10 ) ) 
     {
     $rainday = $row10['rain']*0.2794 + $rainday;
     $timestamp = $row10['time'];
     } 
	 $rainday2 = $rainday - $rainday1;
	 
   $epochtime = strtotime($timestamp);   
   $day3 = date("D", $epochtime);
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query11= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 3 DAY)
     ORDER BY id DESC";
	 $result11=mysql_query($query11);
	 $rainday = 0;
     while ( $row11 = mysql_fetch_array( $result11 ) ) 
     {
     $rainday = $row11['rain']*0.2794 + $rainday;
     $timestamp = $row11['time'];
     } 
	 $rainday3 = $rainday - $rainday2 - $rainday1;

   $epochtime = strtotime($timestamp);   
   $day4 = date("D", $epochtime);	 	  
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query12= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 4 DAY)
     ORDER BY id DESC";
	 $result12=mysql_query($query12);
	 $rainday = 0;
     while ( $row12 = mysql_fetch_array( $result12 ) ) 
     {
     $rainday = $row12['rain']*0.2794 + $rainday;
     $timestamp = $row12['time'];
     } 
	 $rainday4 = $rainday - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day5 = date("D", $epochtime);	 	
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query13= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 5 DAY)
     ORDER BY id DESC";
	 $result13=mysql_query($query13);
	 $rainday = 0;
     while ( $row13 = mysql_fetch_array( $result13 ) ) 
     {
     $rainday = $row13['rain']*0.2794 + $rainday;
     $timestamp = $row13['time'];
     } 
	 $rainday5 = $rainday - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day6 = date("D", $epochtime);	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query14= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 6 DAY)
     ORDER BY id DESC";
	 $result14=mysql_query($query14);
	 $rainday = 0;
     while ( $row14 = mysql_fetch_array( $result14 ) ) 
     {
     $rainday = $row14['rain']*0.2794 + $rainday;
     $timestamp = $row14['time'];
     } 
	 $rainday6 = $rainday - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day7 = date("D", $epochtime);	 	
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query15= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 7 DAY)
     ORDER BY id DESC";
	 $result15=mysql_query($query15);
	 $rainday = 0;
     while ( $row15 = mysql_fetch_array( $result15 ) ) 
     {
     $rainday = $row15['rain']*0.2794 + $rainday;
     $timestamp = $row15['time'];
     } 
	 $rainday7 = $rainday - $rainday6 - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day8 = date("D", $epochtime);	 	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query16= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 8 DAY)
     ORDER BY id DESC";
	 $result16=mysql_query($query16);
	 $rainday = 0;
     while ( $row16 = mysql_fetch_array( $result16 ) ) 
     {
     $rainday = $row16['rain']*0.2794 + $rainday;
     $timestamp = $row16['time'];
     } 
	 $rainday8 = $rainday - $rainday7 - $rainday6 - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day9 = date("D", $epochtime);	 	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query17= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 9 DAY)
     ORDER BY id DESC";
	 $result17=mysql_query($query17);
	 $rainday = 0;
     while ( $row17 = mysql_fetch_array( $result17 ) ) 
     {
     $rainday = $row17['rain']*0.2794 + $rainday;
     $timestamp = $row17['time'];
     } 
	 $rainday9 = $rainday - $rainday8 - $rainday7 - $rainday6 - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day10 = date("D", $epochtime);	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query18= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 10 DAY)
     ORDER BY id DESC";
	 $result18=mysql_query($query18);
	 $rainday = 0;
     while ( $row18 = mysql_fetch_array( $result18 ) ) 
     {
     $rainday = $row18['rain']*0.2794 + $rainday;
     $timestamp = $row18['time'];
     } 
	 $rainday10 = $rainday - $rainday9 - $rainday8 - $rainday7 - $rainday6 - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day11 = date("D", $epochtime);	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query19= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 11 DAY)
     ORDER BY id DESC";
	 $result19=mysql_query($query19);
	 $rainday = 0;
     while ( $row19 = mysql_fetch_array( $result19 ) ) 
     {
     $rainday = $row19['rain']*0.2794 + $rainday;
     $timestamp = $row19['time'];
     } 
	 $rainday11 = $rainday - $rainday10 - $rainday9 - $rainday8 - $rainday7 - $rainday6 - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day12 = date("D", $epochtime);	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query20= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 12 DAY)
     ORDER BY id DESC";
	 $result20=mysql_query($query20);
	 $rainday = 0;
     while ( $row20 = mysql_fetch_array( $result20 ) ) 
     {
     $rainday = $row20['rain']*0.2794 + $rainday;
     $timestamp = $row20['time'];
     } 
	 $rainday12 = $rainday - $rainday11 - $rainday10 - $rainday9 - $rainday8 - $rainday7 - $rainday6 - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day13 = date("D", $epochtime);	 	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query21= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 13 DAY)
     ORDER BY id DESC";
	 $result21=mysql_query($query21);
	 $rainday = 0;
     while ( $row21 = mysql_fetch_array( $result21 ) ) 
     {
     $rainday = $row21['rain']*0.2794 + $rainday;
     $timestamp = $row21['time'];
     } 
	 $rainday13 = $rainday - $rainday12 - $rainday11 - $rainday10 - $rainday9 - $rainday8 - $rainday7 - $rainday6 - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day14 = date("D", $epochtime);	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
     $query22= "SELECT * FROM *************
     WHERE time > DATE_SUB(NOW(), INTERVAL 14 DAY)
     ORDER BY id DESC";
	 $result22=mysql_query($query22);
	 $rainday = 0;
     while ( $row22 = mysql_fetch_array( $result22 ) ) 
     {
     $rainday = $row22['rain']*0.2794 + $rainday;
     $timestamp = $row22['time'];
     } 
	 $rainday14 = $rainday - $rainday13 - $rainday12 - $rainday11 - $rainday10 - $rainday9 - $rainday8 - $rainday7 - $rainday6 - $rainday5 - $rainday4 - $rainday3 - $rainday2 - $rainday1;
   $epochtime = strtotime($timestamp);   
   $day15 = date("D", $epochtime);	 
/////////////////////////////////////////////////////////////////////////////////////////////////////
   $query16="SELECT * FROM ************* LIMIT 1";
   $result16=mysql_query($query16);
  
//  $rainday = 2;

// Print out row .... NB Do not have any other echo commands.
$prefix = '';
echo "[\n";
while ( $row16 = mysql_fetch_assoc( $result16 ) ) {
  
  echo $prefix . " {\n";  
  echo '  "day": "' . 24 . '",' . "\n";
  echo '  "rainday": ' . $rainday1 . '' . "\n";    
  echo " },";
  echo $prefix . " {\n";  
  echo '  "day": "' . $day2 . '",' . "\n";
  echo '  "rainday": ' . $rainday2 . '' . "\n";    
  echo " },";  
  echo $prefix . " {\n";  
  echo '  "day": "' . $day3 . '",' . "\n";
  echo '  "rainday": ' . $rainday3 . '' . "\n";    
  echo " },";  
  echo $prefix . " {\n";  
  echo '  "day": "' . $day4 . '",' . "\n";
  echo '  "rainday": ' . $rainday4 . '' . "\n";    
  echo " },"; 
  echo $prefix . " {\n";  
  echo '  "day": "' . $day5 . '",' . "\n";
  echo '  "rainday": ' . $rainday5 . '' . "\n";    
  echo " },"; 
  echo $prefix . " {\n";  
  echo '  "day": "' . $day6 . '",' . "\n";
  echo '  "rainday": ' . $rainday6 . '' . "\n";    
  echo " },"; 
  
  echo $prefix . " {\n";  
  echo '  "day": "' . $day7 . '",' . "\n";
  echo '  "rainday": ' . $rainday7 . '' . "\n";    
  echo " },"; 
  
  echo $prefix . " {\n";  
  echo '  "day": "' . $day8 . '",' . "\n";
  echo '  "rainday": ' . $rainday8 . '' . "\n";    
  echo " },"; 
  
  
  echo $prefix . " {\n";  
  echo '  "day": "' . $day9 . '",' . "\n";
  echo '  "rainday": ' . $rainday9 . '' . "\n";    
  echo " },";  
  
  echo $prefix . " {\n";  
  echo '  "day": "' . $day10 . '",' . "\n";
  echo '  "rainday": ' . $rainday10 . '' . "\n";    
  echo " },";  
  
  echo $prefix . " {\n";  
  echo '  "day": "' . $day11 . '",' . "\n";
  echo '  "rainday": ' . $rainday11 . '' . "\n";    
  echo " },";  
   
  echo $prefix . " {\n";  
  echo '  "day": "' . $day12 . '",' . "\n";
  echo '  "rainday": ' . $rainday12 . '' . "\n";    
  echo " },"; 
    
  echo $prefix . " {\n";  
  echo '  "day": "' . $day13 . '",' . "\n";
  echo '  "rainday": ' . $rainday13 . '' . "\n";    
  echo " },"; 
             
  echo $prefix . " {\n";  
  echo '  "day": "' . $day14 . '",' . "\n";
  echo '  "rainday": ' . $rainday14 . '' . "\n";    
  echo " }"; 


          
  $prefix = ",\n";
}
echo "\n]";

// Close the connection
mysql_close( $link );
?>
