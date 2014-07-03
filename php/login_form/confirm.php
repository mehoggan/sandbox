<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN""http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html>
	<head>
		<?php 
			include 'include.php';
		?>
		<title>GraphXYZ Confirm Membership</title>
	</head>
	<body>
		<?php 
			$email = mysql_real_escape_string($_GET['email']);
			if($email != "")
			{
				$dbhost = 'localhost';
				$dbuser = 'root';
				$dbpass = 'mysqlheed666~1';
				$conn = mysql_connect($dbhost, $dbuser, $dbpass) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
				$dbname = 'GraphXYZDB';
				mysql_select_db($dbname) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
				$table = 'members';
				if((mysql_num_rows(mysql_query("SELECT * FROM " . $table . " WHERE email = '" . $email . "';"))) == 0)
				{
					print('<script type="text/javascript">alert("Do not try and hack my site asssnatch");</script>');
					exit(0);
				}
				$response_id = mysql_query("SELECT * FROM " . $table . " WHERE email = '" . $email . "';");
				/*
				$column_count = mysql_num_fields($response_id);
				print('<TABLE border="1">');
				print("<TR>");
				$row = mysql_fetch_row($response_id);
				for ($column_num = 0; $column_num < $column_count - 1; $column_num++)
				{
					print("<TD>" . $row[$column_num] . "</TD>");
				}
				print("</TR>");
				print("</TABLE>");
				*/
				mysql_close($conn);
				$dbhost = 'localhost';
				$dbuser = 'root';
				$dbpass = 'mysqlheed666~1';
				$conn = mysql_connect($dbhost, $dbuser, $dbpass) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
				$dbname = 'GraphXYZDB';
				mysql_select_db($dbname) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
				$table2 = 'login';
				$table1 = 'members';
				if(mysql_num_rows(mysql_query("SELECT * FROM " . $table2 . " WHERE email = '" . $email . "';")))
				{
					print('<script type="text/javascript">alert("Email already registered");</script>');
					print('<div align="middle"><h1>Please Click the Link Below to Login</h1><br/>');
					print('<a href="http://192.168.1.1/index.php">Login</a></div>');
				}
				else
				{
					$query = "INSERT INTO " . $table2 . " SELECT * FROM " . $table1 . " WHERE email = '" . $email . "';";
					mysql_query($query) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
					print('<div align="middle"><h1>Welcome Please Click the Link Below to Login</h1><br/>');
					print('<a href="http://192.168.1.1/index.php?registered=1">Login</a></div>');
				}
			}
			else
			{
				print('<script type="text/javascript">alert("Dude you really need to learn how to hack");</script>');
			}
		?>
	</body>
</html>









































































