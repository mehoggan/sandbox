<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN""http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html>
	<head>
		<?php 
			include 'include.php';
		?>
		<title>GraphXYZ Membership Form</title>
		<link rel="stylesheet" type="text/css" href="css/memberform.css"/>
		<script type="text/javascript" src="js/member_reg_form.js"></script>
	</head>
	<body>
		<?php 
			function printvars()
			{
				echo "Attempting to insert into db <br/>";
				echo $email . " already in DB <br/>";
				echo "Form variables are: <br/>";
				$first_name = mysql_real_escape_string($_POST['nfname']);
				$last_name = mysql_real_escape_string($_POST['nlname']);
				$address = mysql_real_escape_string($_POST['naddrs']);
				$city_name = mysql_real_escape_string($_POST['ncity']);
				$state = mysql_real_escape_string($_POST['nstate']);
				$zip = mysql_real_escape_string($_POST['nzip']);
				$email = mysql_real_escape_string($_POST['nemail']);
				$company = mysql_real_escape_string($_POST['ncname']);
				$screen = mysql_real_escape_string($_POST['nscreen']);
				$password = mysql_real_escape_string($_POST['npsswd']);
				echo $first_name . "<br/>";
				echo $last_name . "<br/>";
				echo $address . "<br/>";
				echo $city_name . "<br/>";
				echo $state . "<br/>";
				echo $zip . "<br/>";
				echo $email . "<br/>";
				echo $company . "<br/>";
				echo $screen . "<br/>";
				echo $password . "<br/>";
			}
			
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
			
			function validate()
			{
				if(!eregi("^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$", $_POST['nemail']))
				{				
					print('<script type="text/javascript">alert("Please input valid email");</script>');				
					return false;
				}
				if($_POST['nemail'] == '' || $_POST['nemail'] == ' ')
				{
					print('<script type="text/javascript">alert("Please input valid email");</script>');
				}	
				if(!is_numeric($_POST['nzip']) && $_POST['nzip'] != "")
				{
					print('<script type="text/javascript">alert("Please input valid zip code");</script>');				
					return false;
				}
				if((strlen($_POST['nzip']) != 5 && strlen($_POST['nzip']) != 7) && $_POST['nzip'] != "")
				{
					print('<script type="text/javascript">alert("Please input valid zip code");</script>');				
					return false;
				}
				if(strlen($_POST['npsswd']) < 8)
				{
					print('<script type="text/javascript">alert("Password must be 8 or more characters long");</script>');		
					return false;
				}
				return true;
			}
		
			if(!validate())
			{
		?>
		<form name="mainform" id="mainfrm" method="post" action="member_form_submit.php" onSubmit="return Validate()">
			<div id="wraper" align="middle">
				<div id="title">
					Membership Form
				</div>
				<div id="main" align="left">
					<div id="firstLine">
						<p>
							First Name*: <input id="ifname" type="text" name="nfname" value="<?php echo $_POST['nfname']; ?>" maxlength="15" />				 
							Last Name*: <input id="ilname" type="text" name="nlname"  value="<?php echo $_POST['nlname']; ?>" maxlength="20" />
						</p>
						<p>
							Address: <input id="iaddrs" type="text" name="naddrs" value="<?php echo $_POST['naddrs']; ?>" maxlength="50" />
							City: <input id="icity" type="text" name="ncity" value="<?php echo $_POST['ncity']; ?>" maxlength="50" />
						</p>
						<p>
							State: <select id="sstate", value="<?php echo $_POST['nstate'];?>" name="nstate">
							<?php
									$states = array("ALABAMA" => "AL", "ALASKA" => "AK", "ARIZONA" => "AZ", "ARKANSAS" => "AR",
									"CALIFORNIA" => "CA", "COLORADO" => "CO", "CONNECTICUT" => CT, "DELAWARE" => "DE",
									"DISTRICT OF COLUMBIA" => "DC", "FLORIDA" => "FL", "GEORGIA" => "GA", "HAWAII" => "HI",
									"IDAHO" => "ID", "ILLINOIS" => "IL", "INDIANA" => "IN", "IOWA" => "IA", "KANSAS" => "KS",
									"KENTUCKY" => "KY", "LOUISIANA" => "LA", "MAINE" => "ME", "MARYLAND" => "MD",
									"MASSACHUSETTS" => "MA", "MICHIGAN" => "MI", "MINNESOTA" => "MN", "MISSISSIPPI" => "MS",
									"MISSOURI" => "MO", "MONTANA" => "MT", "NEBRASKA" => "NE", "NEVADA" => "NV",
									"NEW HAMPSHIRE" => "NH", "NEW JERSEY" => "NJ", "NEW MEXICO" => "NM", "NEW YORK" => "NY",
									"NORTH CAROLINA" => "NC", "NORTH DAKOTA" => "ND", "OHIO" => "OH", "OKLAHOMA" => "OK",
									"OREGON" => "OR", "PENNSYLVANIA" => "PA", "PUERTO RICO" => "PR", "RHODE ISLAND" => "RI",
									"SOUTH CAROLINA" => "SC", "SOUTH DAKOTA" => "SD", "TENNESSEE" => "TN", "TEXAS" => "TX", 
									"UTAH" => "UT", "VERMONT" => "VT", "VIRGIN ISLANDS" => "VI", "VIRGINIA" => "VA",
									"WASHINGTON" => "WA", "WEST VIRGINIA" => "WV", "WISCONSIN" => "WI", "WYOMING" => "WY");
									foreach($states as &$value)
									{
										echo '<option>' . $value . '</option>'; 
									}
								?>
						   </select>
							Zip: <input id="izip" type="text" name="nzip" value="<?php echo $_POST['nzip'];?>" maxlength="50" />
						</p>
						<p>
							Email*: <input id="iemail" type="text" name="nemail" value="<?php echo $_POST['nemail'];?>" maxlength="50" />
							Company Name: <input id="icname" type="text" name="ncname" value="<?php echo $_POST['ncname'];?>"  maxlength="50" />
						</p>
						<p>
							Desired Screen Name*: <input id="iscreen" type="text" name="nscreen" value="<?php echo $_POST['nscreen'];?>"  maxlength="50" />
						</p>
						<p>
							Desired Password*: <input id="ipsswd" type="password" name="npsswd" value="<?php echo $_POST['npsswd'];?>" maxlength="50" /> &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp
						</p>
						<p>
							<input type="submit" value="Submit" id="isubmit" />
							<br/>
							<div align="middle">
								<a href="index.php">cancel</a>
							</div>
						</p>
					</div>
				</div>
				Please fill in all spots with * next to them.
			</div>				
		</form>
	<?php
		} 
		else 
		{
			$dbhost = 'localhost';
			$dbuser = 'root';
			$dbpass = 'mysqlheed666~1';
			$conn = mysql_connect($dbhost, $dbuser, $dbpass) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
			
			$dbname = 'GraphXYZDB';
			mysql_select_db($dbname) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
			
			$table = 'members';
			$first_name = mysql_real_escape_string($_POST['nfname']);
			$last_name = mysql_real_escape_string($_POST['nlname']);
			$address = mysql_real_escape_string($_POST['naddrs']);
			$city_name = mysql_real_escape_string($_POST['ncity']);
			$state = mysql_real_escape_string($_POST['nstate']);
			$zip = mysql_real_escape_string($_POST['nzip']);
			$email = mysql_real_escape_string($_POST['nemail']);
			$company = mysql_real_escape_string($_POST['ncname']);
			$screen = mysql_real_escape_string($_POST['nscreen']);
			$password = mysql_real_escape_string($_POST['npsswd']);
			
			if(mysql_num_rows(mysql_query("SELECT * FROM " . $table . " WHERE email = '" . $email . "';")))
			{
				print('<script type="text/javascript">alert("Email already exists");</script>');
	?>
		<form name="mainform" id="mainfrm" method="post" action="member_form_submit.php" onSubmit="return Validate()">
			<div id="wraper" align="middle">
				<div id="title">
					Membership Form
				</div>
				<div id="main" align="left">
					<div id="firstLine">
						<p>
							First Name*: <input id="ifname" type="text" name="nfname" value="<?php echo $first_name; ?>" maxlength="15" />				 
							Last Name*: <input id="ilname" type="text" name="nlname"  value="<?php echo $last_name; ?>" maxlength="20" />
						</p>
						<p>
							Address: <input id="iaddrs" type="text" name="naddrs" value="<?php echo $address; ?>" maxlength="50" />
							City: <input id="icity" type="text" name="ncity" value="<?php echo $city_name; ?>" maxlength="50" />
						</p>
						<p>
							State: <select id="sstate", value="<?php echo $state;?>" name="nstate">
							<?php
									$states = array("ALABAMA" => "AL", "ALASKA" => "AK", "ARIZONA" => "AZ", "ARKANSAS" => "AR",
									"CALIFORNIA" => "CA", "COLORADO" => "CO", "CONNECTICUT" => CT, "DELAWARE" => "DE",
									"DISTRICT OF COLUMBIA" => "DC", "FLORIDA" => "FL", "GEORGIA" => "GA", "HAWAII" => "HI",
									"IDAHO" => "ID", "ILLINOIS" => "IL", "INDIANA" => "IN", "IOWA" => "IA", "KANSAS" => "KS",
									"KENTUCKY" => "KY", "LOUISIANA" => "LA", "MAINE" => "ME", "MARYLAND" => "MD",
									"MASSACHUSETTS" => "MA", "MICHIGAN" => "MI", "MINNESOTA" => "MN", "MISSISSIPPI" => "MS",
									"MISSOURI" => "MO", "MONTANA" => "MT", "NEBRASKA" => "NE", "NEVADA" => "NV",
									"NEW HAMPSHIRE" => "NH", "NEW JERSEY" => "NJ", "NEW MEXICO" => "NM", "NEW YORK" => "NY",
									"NORTH CAROLINA" => "NC", "NORTH DAKOTA" => "ND", "OHIO" => "OH", "OKLAHOMA" => "OK",
									"OREGON" => "OR", "PENNSYLVANIA" => "PA", "PUERTO RICO" => "PR", "RHODE ISLAND" => "RI",
									"SOUTH CAROLINA" => "SC", "SOUTH DAKOTA" => "SD", "TENNESSEE" => "TN", "TEXAS" => "TX", 
									"UTAH" => "UT", "VERMONT" => "VT", "VIRGIN ISLANDS" => "VI", "VIRGINIA" => "VA",
									"WASHINGTON" => "WA", "WEST VIRGINIA" => "WV", "WISCONSIN" => "WI", "WYOMING" => "WY");
									foreach($states as &$value)
									{
										echo '<option>' . $value . '</option>'; 
									}
								?>
						   </select>
							Zip: <input id="izip" type="text" name="nzip" value="<?php echo $zip;?>" maxlength="50" />
						</p>
						<p>
							Email*: <input id="iemail" type="text" name="nemail" value="" maxlength="50" />
							Company Name: <input id="icname" type="text" name="ncname" value="<?php echo $company;?>"  maxlength="50" />
						</p>
						<p>
							Desired Screen Name*: <input id="iscreen" type="text" name="nscreen" value="<?php echo $screen;?>"  maxlength="50" />
						</p>
						<p>
							Desired Password*: <input id="ipsswd" type="password" name="npsswd" value="<?php echo $password?>" maxlength="50" /> &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp
						</p>
						<p>
							<input type="submit" value="Submit" id="isubmit" />
							<br/>
							<div align="middle">
								<a href="index.php">cancel</a>
							</div>
						</p>
					</div>
				</div>
				Please fill in all spots with * next to them.
			</div>				
		</form>
	<?php 
			}
			else
			{
				//printvars();
				$password = encrypt($password, 'abc123def');
				$insert = "INSERT INTO " . $table . " VALUES ('" . $first_name . "', '" . $last_name . "', '" .  $address . "', '" .  $city_name . "', '" .  $state . "', '" .  $zip . "', '" . $email . "', '" .  $company . "', '" .  $screen . "', '" .  $password . "');";
				mysql_query($insert) or die("Error " . mysql_errno(  ) . " : " . mysql_error(  ));
				
				$to      = $email;
				$subject = 'Welcome to GraphXYZ';
				$message = 'This is to let you know that you have signed up on GraphXYZ please click the following linke to confirm your membership and activate your account http://192.168.1.1/confirm.php?email=' . $email;
				$headers = 'From: mehoggan@gmail.com' . "\r\n" . 'Reply-To: mehoggan@gmail.com' . "\r\n" . 'X-Mailer: PHP/' . phpversion();
				mail($to, $subject, $message, $headers);
				mysql_close($conn);
				header('Location: http://192.168.1.1/index.php?submit=1');			
			}  
		}
	?>
	</body>
</html>









































































