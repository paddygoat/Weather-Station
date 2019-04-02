<?php
include 'settings.php';
// include 'ferret.php';
settings();
// Create connection
$username = "#############";
$password = "#############";
$hostname = "localhost"; 
$databasetable = "#############";

$dbhandle = mysql_connect($hostname, $username, $password) 
or die("Unable to connect to MySQL");

$selected = mysql_select_db("paddygoa_weather",$dbhandle) 
or die("Could not select database");

///////////////////////////////////////////////////////////////////////////////
// Get the current data:
   $query5="SELECT * FROM weather2017 ORDER BY id DESC LIMIT 1";
   $result5=mysql_query($query5);
while($row5=mysql_fetch_array($result5))
   { 
   $last = $row5['id']; 
   $WINDSPEED = $row5['windspeed']; 
   $TEMPOUT = $row5['tempout']; 
   $HUMIDITY = $row5['humidity'];
   $Gtemp = $row5['Gtemp']; 
   $Gmoisture = $row5['Gmoisture'];
   }
//echo "Glasshouse soil moisture= ";  
//echo $Gmoisture;
//echo " %  ";
//echo "Glasshouse temperature = ";
//echo $Gtemp;
//echo "Last ID was: ";
//echo $last;

///////////////////////////////////////////////////////////////////////////////////
// the message
$a = "Glasshouse temperature= ";
$b = ", Glasshouse soil moisture= ";
$c = " %";

$msg = $a.$Gtemp.$b.$Gmoisture.$c;

// use wordwrap() if lines are longer than 70 characters
//$msg = wordwrap($msg,70);

// send email
if ( ($Gmoisture<60) && ($Gmoisture>0) )
{
  mail("paddy@goatindustries.co.uk","Glasshouse needs watering",$msg);
}
if ( ($Gtemp>40) || ($Gtemp<0) )
{
  mail("#############","Glasshouse temperature is bad",$msg);
}

/////////////////////////////////////////////////////////////////////////////////
// Look for errors in previous data row and delete it if it is bad:

if (  ($WINDSPEED>200) || ($HUMIDITY<1) || ($TEMPOUT<-100)  )
{
  $query6="DELETE FROM weather2017 WHERE ID=$last";
  $result6=mysql_query($query6);
}

////////////////////////////////////////////////////////////////////////////////

$result = mysql_query("INSERT INTO $databasetable(windspeed,windgust,windway,tempout,tempsoil,rain,humidity,pressure,volts,moisture,tempint,Gmoisture,Gtemp) VALUES (
'" . $_GET[windspeed] . "',
'" . $_GET[windgust] . "',
'" . $_GET[windway] . "',
'" . $_GET[tempout] . "',
'" . $_GET[tempsoil] . "',
'" . $_GET[rain] . "',
'" . $_GET[humidity] . "',
'" . $_GET[pressure] . "',
'" . $_GET[volts] . "',
'" . $_GET[moisture] . "'-0,
'" . $_GET[tempint] . "',
'" . $_GET[Gmoisture] . "'-0,
'" . $_GET[Gtemp] . "')",
$dbhandle);

//echo "<html>";
//echo "<head><Title> ... Success! ... </title>";
//echo "</head>";
//echo "<body>";
//echo "</body>";
//echo "</html>";
echo " ... Success! ... ";
print ($msg);

mysql_close($dbhandle);
?>
