<!DOCTYPE html>
<html lang="en">
<head>
	<?php 
		include 'include.php';
	?>
	
	<meta charset="utf-8">
	<title>GraphXYZ Home</title>

	<!-- meta tags -->
	<meta name="keywords" content="">
	<meta name="description" content="">

	<!-- stylesheets -->
	<link rel="stylesheet" href="css/layout.css" type="text/css">
	<link rel="stylesheet" href="css/login.css" type="text/css">

	<!-- javascript -->
	<script src="js/main.js"></script>
	<script src="js/login.js"></script>

</head>
<body class="home">
	<?php
		function encrypt($str, $ky='')
		{
			if($ky=='')
			{
				return $str;
			} 
			$ky=str_replace(chr(32),'',$ky); 
			if(strlen($ky)<8)
			{
				exit('key error');
			} 
			$kl=strlen($ky)<32?strlen($ky):32; 
			$k=array();
			for($i=0;$i<$kl;$i++)
			{ 
				$k[$i]=ord($ky{$i})&0x1F;
			} 
			$j=0;
			for($i=0;$i<strlen($str);$i++)
			{ 
				$e=ord($str{$i}); 
				$str{$i}=$e&0xE0?chr($e^$k[$j]):chr($e); 
				$j++;
				$j = $j == $kl?0:$j;
			} 
			return $str; 
		}
		
		if(isset($_POST['username']) && isset($_POST['password']))
		{
			$fail = false;
			$dbhost = 'localhost';
			$dbuser = 'root';
			$dbpass = 'mysqlheed666~1';
			$conn = mysql_connect($dbhost, $dbuser, $dbpass) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
			
			$dbname = 'GraphXYZDB';
			mysql_select_db($dbname) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
			
			$table = 'login';
			
			$password = encrypt($_POST['password'], $ky='abc123def');
			if((mysql_num_rows(mysql_query("SELECT * FROM " . $table . " WHERE screenName = '" . $_POST['username'] . "' AND password = '" . $password. "';"))) == 0)
			{
				$fail = true;
			}			
	?>
	<div id="container">
		<div id="popupbox"> <!--Start login box-->
			<form name="login" action="login.php" method="post">
				<center>Username:</center>
				<center><input name="username" size="14" /></center>
				<center>Password:</center>
				<center><input name="password" type="password" size="14" /></center>
				<center><input type="submit" name="submit" value="login" /></center>
			</form>
			<center><a href="member_form.php">register</a> &nbsp <a href="javascript:login('hide');">close</a></center>
		</div>
		<div style="position: absolute; left: 1130px; z-index: 8">
			<a href="javascript:login('show');">login</a>
		</div>
		<div style="position: absolute; left: 1060px; z-index: 8">
			<a href="member_form.php">register</a>
		</div>
		
		<div id="side-bar">
			<div id="seach-bar">
				<form id="search-form">
					Search Site: <input type="text" name="search" id="search" /><br/><p></p>
					<input type="submit" name="searchb" value="search" style="margin-left: 222px;" />
				</form>
			</div><br/><br/>
			<div id="login-bar">
				<form id="login-form" action="login.php" method="post">
					User Name:<p></p><input type="text" name="username" id="uname" />
					Password:<p></p><input type="password" name="password" id="passwd" /><br/>
					<input type="submit" name="submit2" value="login" style="margin-left: 235px;" />
				</form>
			</div><br/>
		</div>
		<div id="content">
	<?php 	
			if($fail == true)
			{
				echo "<center>Invalid User Name and Password</center>";
			}
			else
			{
				$_SESSION['user'] = $_POST['username'];
				header('Location: http://192.168.1.1/index.php');
	?>
	
	<?php 
			}
			mysql_close($conn);
	?> 
		</div>
	</div>
	<?php
		}
	?>
</body>
</html>
