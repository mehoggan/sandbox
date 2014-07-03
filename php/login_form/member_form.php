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
				<form name="mainform" id="mainfrm" method="post" action="member_form_submit.php" onSubmit="return Validate()">
			<div id="wraper" align="middle">
				<div id="title">
					Membership Form
				</div>
				<div id="main" align="left">
					<div id="firstLine">
						<p>
							First Name*: <input id="ifname" type="text" name="nfname" value="<?php echo $_GET['nfname']; ?>" maxlength="15" />				 
							Last Name*: <input id="ilname" type="text" name="nlname"  value="<?php echo $_GET['nlname']; ?>" maxlength="20" />
						</p>
						<p>
							Address: <input id="iaddrs" type="text" name="naddrs" value="<?php echo $_GET['naddrs']; ?>" maxlength="50" />
							City: <input id="icity" type="text" name="ncity" value="<?php echo $_GET['ncity']; ?>" maxlength="50" />
						</p>
						<p>
							State: <select id="sstate", value="<?php echo $_GET['nstate'];?>" name="nstate">
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
							Zip: <input id="izip" type="text" name="nzip" value="<?php echo $_GET['nzip'];?>" maxlength="50" />
						</p>
						<p>
							Email*: <input id="iemail" type="text" name="nemail" value="<?php echo $_GET['nemail'];?>" maxlength="50" />
							Company Name: <input id="icname" type="text" name="ncname" value="<?php echo $_GET['ncname'];?>"  maxlength="50" />
						</p>
						<p>
							Desired Screen Name*: <input id="iscreen" type="text" name="nscreen" value="<?php echo $_GET['nscreen'];?>"  maxlength="50" />
						</p>
						<p>
							Desired Password*: <input id="ipsswd" type="password" name="npsswd" value="<?php echo $_GET['npsswd'];?>" maxlength="50" /> &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp
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
	</body>
</html>
