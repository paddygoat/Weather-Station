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

/////////////////////////////////////////////////////////////////////////////////////////////////////  
   $query7="SELECT * FROM ************* WHERE DATE(time) = DATE(NOW())";
   $result7=mysql_query($query7);
while ( $row7 = mysql_fetch_assoc( $result7 ) ) 
{
   $rainday = $row7['rain'] + $rainday;
}
   $rainday = $rainday * 0.2794;
/////////////////////////////////////////////////////////////////////////////////////////////////////

   $query8="SELECT * FROM ************* LIMIT 1";
   $result8=mysql_query($query8);
  
//  $rainday = 2;

// Print out row .... NB Do not have any other echo commands.
$prefix = '';
echo "[\n";
while ( $row8 = mysql_fetch_assoc( $result8 ) ) {
  
  echo $prefix . " {\n";  
  echo '  "time": "' . Today . '",' . "\n";
  echo '  "rainday": ' . $rainday . '' . "\n";    
  echo " }";
  $prefix = ",\n";
}
echo "\n]";

// Close the connection
//mysql_close( $link );
?>