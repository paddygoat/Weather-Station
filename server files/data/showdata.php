<?php

$host="localhost"; // Host name 
$username="*************"; // Mysql username 
$password="*************"; // Mysql password 
$db_name="*************"; // Database name 
$tbl_name="*************"; // Table name

// Connect to server and select database.
mysql_connect("$host", "$username", "$password")or die("cannot connect"); 
mysql_select_db("$db_name")or die("cannot select DB");

// Retrieve data from database 
 
$sql2="SELECT * FROM *************  ORDER BY id DESC LIMIT 60";
$result2=mysql_query($sql2);
 
 ?>
<html>
   <style type="text/css">
<!--
.style1 {font-size: 12px}  <!-- Data font size -->
-->
   </style>
   <head>
      <title>Show Weather Station Raw Data</title>
</head>
<body>
<table width="1000" border="1" cellspacing="0" cellpadding="0">
  <tr>
    <td colspan="13"><h1 align="center">Weather Station Raw Data</h1></td>
  </tr>
  <tr>
    <td width="6%"><div align="center">Id </div></td>
    <td width="12%"><div align="center">Time Stamp </div></td>
    <td width="9%"><div align="center">Wind Speed </div></td>
    <td width="8%"><div align="center">Wind Gust </div></td>
    <td width="7%"><div align="center">Wind Dir </div></td>
    <td width="7%"><div align="center">Temp out </div></td>
    <td width="5%"><div align="center">Volts </div></td>
    <td width="5%"><div align="center">Rain </div></td>
    <td width="7%"><div align="center">Humidity </div></td>
    <td width="8%"><div align="center">Pressure </div></td>
    <td width="8%"><div align="center">Soil Temp </div></td>
    <td width="7%"><div align="center">Moisture </div></td>
    <td width="7%"><div align="center">Temp int </div></td>    	
  </tr>
</table>
 <table width="1000" border="1" cellspacing="0" cellpadding="0"> 
 
<?php

// Start looping rows in mysql database.
 while($rows=mysql_fetch_array($result2)){
 
//if ($rows['windway'] == 1){$rows['windway'] = 0;}
//if ($rows['windway'] == 2){$rows['windway'] = 45;}
//if ($rows['windway'] == 3){$rows['windway'] = 90;}
//if ($rows['windway'] == 4){$rows['windway'] = 135;}
//if ($rows['windway'] == 5){$rows['windway'] = 180;}
//if ($rows['windway'] == 6){$rows['windway'] = 225;}
//if ($rows['windway'] == 7){$rows['windway'] = 270;}
//if ($rows['windway'] == 8){$rows['windway'] = 315;}
 
 ?>

 <tr>

 <td bgcolor="#cce2ff" width="6%"><div align="center"><span class="style1"><? echo $rows['id']; ?></span></td>
 <td bgcolor="#FFFFCC" width="12%"><div align="center"><span class="style1"><? echo $rows['time']; ?></span></td>
 <td bgcolor="#ccffcd" width="9%"><div align="center"><span class="style1"><? echo $rows['windspeed']; ?></span></td>
 <td bgcolor="#ffccd9" width="8%"><div align="center"><span class="style1"><? echo $rows['windgust']; ?></span></td>
 <td bgcolor="#cce2ff" width="7%"><div align="center"><span class="style1"><? echo $rows['windway']; ?></span></td>
 <td bgcolor="#FFFFCC" width="7%"><div align="center"><span class="style1"><? echo $rows['tempout']; ?></span></td>
 <td bgcolor="#ccffcd" width="5%"><div align="center"><span class="style1"><? echo $rows['volts']; ?></span></td> 
 <td bgcolor="#ffccd9" width="5%"><div align="center"><span class="style1"><? echo $rows['rain']*0.2794; ?></span></td>
 <td bgcolor="#cce2ff" width="7%"><div align="center"><span class="style1"><? echo $rows['humidity']; ?></span></td>  
 <td bgcolor="#FFFFCC" width="8%"><div align="center"><span class="style1"><? echo $rows['pressure']; ?></span></td> 
 <td bgcolor="#ccffcd" width="8%"><div align="center"><span class="style1"><? echo $rows['tempsoil']; ?></span></td>  
 <td bgcolor="#ffccd9" width="7%"><div align="center"><span class="style1"><? echo $rows['moisture']; ?></span></td>  
 <td bgcolor="#cce2ff" width="7%"><div align="center"><span class="style1"><? echo $rows['tempint']; ?></span></td>        
 </tr>
 


<?php
// close while loop 
}

?>
</table>
</body>
</html>

<?php
// close MySQL connection 
mysql_close();
 ?>