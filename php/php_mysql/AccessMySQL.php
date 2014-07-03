<?php
	include('db_longin.php');
	$db_database='store';
	$db_host='192.168.1.2:3306';
	$db_username='root';
	$db_password='heed666~1';
	$connection = mysql_connect($db_host, $db_username, $db_password);
	if(!$connection) {
		die("Could not connect to the database: <br/>".mysql_error());
	}
	else {
		$db_select = mysql_select_db($db_database);
		if(!$db_select) {
			die("Could not select the database: <br/>".mysql_error());
		}
		else {
			$query = "SELECT * FROM books NATURAL JOIN authors";
			$result = mysql_query($query);
			if(!$result){
				die("Could not query the database: <br/>".mysql_error());
			}
			else {
				while($result_row = mysql_fetch_row(($result))){
					echo 'Title: '.$result_row[1].'<br/>';
					echo 'Author: '.$result_row[4].'<br/>';
					echo 'Pages: '.$result_row[2].'<br/><br/>';
				}
			}
		}
	}
	mysql_close($connection);
?>
