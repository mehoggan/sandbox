<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN""http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html>
	<title>Matt Intro to Forms</title>
	<head>
		<link rel="stylesheet" type="text/css" href="http://192.168.1.3/css/main.css"/>
		<script type="text/javascript" src="http://192.168.1.3/javascript/main.js"></script>
	</head>
	<body>
		<form name="mainform" id="mainfrm" method="post" action="http://www.geoginfo.com" onSubmit="return Validate(this)">
			<div id="wraper">
				<div id="title">
					Membership Form
				</div>
				<div id="main">
					<div id="firstLine">
						<label for="ifname" id="lfname">First Name</label>
						<label for="iminitial" id="lminitial">Mid Init</label>
						<label for="ilname" id="llname">Last Name</label>
						<input id="ifname" type="text" name="nfname" maxlength="15">					
						<input id="iminitial" type="text" name="nminitial" maxlength="4"> 
						<input id="ilname" type="text" name="nlname" maxlength="20">
						<br><br><br>

						<label for="imemnum" id="lmemnum">Membership Number</label>
						<input id="imemnum" type="text" name="nmemnum" maxlength="13">
						<div id="memnumber">	
							<label id="lmemnumber">11 Numbers (xxx-xxxx-xxxx)</label>
						</div><br>

						<label for="iaddrs" id="laddrs">Address</label>
						<label for="ssttype" id="lsttype">St. Type</label>
						<label for="iaptnum" id="laptnum">Apt #</label>
						<input id="iaddrs" type="text" name="naddrs" maxlength="20">
						<select id="ssttype" name="nsttype" value="">
							<?php
								include('db_longin.php');
								$db_database='member_form';
								$db_host='192.168.1.2:3306';
								$db_username='root';
								$db_password='heed666~1';
								$connection = mysql_connect($db_host, $db_username, $db_password);
								if(!$connection) 
								{
									die("Could not connect to the database: <br/>".mysql_error());
								}
								else {
									$db_select = mysql_select_db($db_database);
									if(!$db_select) 
									{
										die("Could not select the database: <br/>".mysql_error());
									}
									else 
									{
										$query = "SELECT * FROM street_type";
										$result = mysql_query($query);
										if(!$result)
										{
											die("Could not query the database: <br/>".mysql_error());
										}
										else 
										{
											while($result_row = mysql_fetch_row(($result))){
												if($result_row[0] == 'ST')
												{
													echo '<option selected=\"selected\">'.$result_row[0].'</option>';
												}
												else
												{
													echo '<option>'.$result_row[0].'</option>';
												}
											}
										}
									}
								}
								mysql_close($connection);
							?>
						</select>
						<input id="iaptnum" type="text" name="naptnum" maxlength="4">
						
						<div id="adrsinstr">	
							<label id="ladrsinstr">*Do NOT include St or Street, Ave or Avenue, etc.</label>
						</div><br>

						<script type="text/javascript">
								window.onload=adjust();	
										
								function adjust()
								{
									var browser = navigator.appName;
									
									if(browser == "Netscape")
									{
										document.writeln("<br>");
									}
								}
						</script>
						
						<label for="sdob" id="ldob">Date of Birth</label>
						<label for="ssex" id="lsex">Sex</label>

						<select id="smdob" name="nmdob" onChange="updateDay()">
							<?php
								include('db_longin.php');
								$db_database='member_form';
								$db_host='192.168.1.2:3306';
								$db_username='root';
								$db_password='heed666~1';
								$connection = mysql_connect($db_host, $db_username, $db_password);
								if(!$connection) 
								{
									die("Could not connect to the database: <br/>".mysql_error());
								}
								else {
									$db_select = mysql_select_db($db_database);
									if(!$db_select) 
									{
										die("Could not select the database: <br/>".mysql_error());
									}
									else 
									{
										$query = "SELECT * FROM month";
										$result = mysql_query($query);
										if(!$result)
										{
											die("Could not query the database: <br/>".mysql_error());
										}
										else 
										{
											while($result_row = mysql_fetch_row(($result))){
												echo '<option>'.$result_row[0].'</option>';
											}
										}
									}
								}
								mysql_close($connection);
							?>
						</select>

						<select id="sddob" name="nddob">
							<?php
								for($x = 1; $x <= 31; $x++)
								{
									echo '<option>'.$x.'</option>';
								}
							?>
						</select>
						<select id="sydob" name="nydob">
							<?php
								include('db_longin.php');
								$db_database='member_form';
								$db_host='192.168.1.2:3306';
								$db_username='root';
								$db_password='heed666~1';
								$connection = mysql_connect($db_host, $db_username, $db_password);
								if(!$connection) 
								{
									die("Could not connect to the database: <br/>".mysql_error());
								}
								else {
									$db_select = mysql_select_db($db_database);
									if(!$db_select) 
									{
										die("Could not select the database: <br/>".mysql_error());
									}
									else 
									{
										$query = "SELECT * FROM year";
										$result = mysql_query($query);
										if(!$result)
										{
											die("Could not query the database: <br/>".mysql_error());
										}
										else 
										{
											while($result_row = mysql_fetch_row(($result))){
												echo '<option>'.$result_row[0].'</option>';
											}
										}
									}
								}
								mysql_close($connection);
							?>
						</select>
						<select id="ssex">
							<?php
								echo '<option>'.'male'.'</option>';
								echo '<option>'.'female'.'</option>';
							?>
						</select><br>
						<div id="yearlabels">	
							<label id="lmonth">Month</label>
							<label id="lday">Day</label>
							<label id="lyear">Year</label>
						</div><br>
						<script type="text/javascript">
								window.onload=adjust2();	
										
								function adjust2()
								{
									var browser = navigator.appName;
									
									if(browser == "Netscape")
									{
										document.writeln("<br>");
									}
								}
						</script>
						<input type="submit" value="Submit" id="button">
					</div>
				</div>
			</div>
			<script type="text/javascript">
					var browser = navigator.appName;
					var app = navigator.appCodeName;
					var userAgent = navigator.userAgent;

					var label1 = document.getElementById("lminitial");
					var label2 = document.getElementById("llname");
					var label3 = document.getElementById("lsttype");
					var label4 = document.getElementById("laptnum");
					var label5 = document.getElementById("lsex");

					if(browser == "Microsoft Internet Explorer")
					{
						label1.style.marginLeft = "95px";
						label2.style.marginLeft = "15px";
						label3.style.marginLeft = "170px";
						label4.style.marginLeft = "13px";
						label5.style.marginLeft = "210px";
					}
					
					var div1 = document.getElementById("adrsinstr");
					
					if(userAgent == "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.5) Gecko/2008120122 Firefox/3.0.5")
					{
						div1.style.fontSize = "9px";
						label1.style.marginLeft = "95px";
						label2.style.marginLeft = "15px";
						label3.style.marginLeft = "170px";
						label4.style.marginLeft = "13px";
						label5.style.marginLeft = "210px";
					}
					if(userAgent == "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.6) Gecko/20050225 Firefox/1.0.1")
					{
						div1.style.fontSize = "9px";
						label1.style.marginLeft = "95px";
						label2.style.marginLeft = "15px";
						label3.style.marginLeft = "170px";
						label4.style.marginLeft = "13px";
						label5.style.marginLeft = "210px";
					}
			</script>				
		</form>
	</body>
</html>
