<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Server Provisionment</title>
<link rel="stylesheet" type="text/css" href="/css/view.css" media="all">
<script type="text/javascript" src="/js/view.js"></script>

</head>
<body id="main_body" >
	<img id="top" src="/images/top.png" alt="">
	<div id="form_container">
	
		<h1><a>Server Provisionment</a></h1>
		<form id="form_111747" class="appnitro"  method="post" action="index.php">
					<div class="form_description">
			<h2>Server Provisionment</h2>
			<p>SA Custom RPM Build Interface.</p>
		</div>						
			<ul >
			
					<li id="li_1" >
		<label class="description" for="element_1">Project Name </label>
		<div>
			<input id="element_1" name="element_1" class="element text medium" type="text" maxlength="255" value=""/> 
		</div> 
		<label class="description" for="email">Email Address </label>
		<div>
			<input id="element_2" name="email" class="element text medium" type="text" maxlength="255" value=""/> 
		</div>
		</li>		<li id="li_2" >
		</li>		<li id="li_3" >
		<label class="description" for="element_3">Check if SSCAE Software Purchased </label>
		<span>
			<input id="element_3_1" name="element_3_1" class="element checkbox" type="checkbox" value="1" />
			<label class="choice" for="element_3_1">SSCAE Software Included</label>
		</span> 
		</li>
			
					<li class="buttons">
			    <input type="hidden" name="form_id" value="111747" />
			    
				<input id="saveForm" class="button_text" type="submit" name="submit" value="Submit" />
		</li>
			</ul>
		</form>	
	</div>
	<img id="bottom" src="/images/bottom.png" alt="">
	
	<?php
		if(isset($_POST['element_1']) && $_POST['element_1'] != '^&^&^') {
	        	function microtime_float() {
	               		list($usec, $sec) = explode(" ", microtime());
	        	        return ((float)$usec + (float)$sec);
		        }
		        function print_values(&$packages, &$versions) {
		                $count = 0;
		                foreach($packages as $var) {
	        	                echo $var;
	                	        $pass = 0;
	                       		foreach($versions as $ver) {
	                                	if($pass == $count) {
	                                        	echo " ".$ver;
		                                }
		                                $pass++;
		                        }
		                        $count++;
					echo "</br>";
		                }
		        }
			function recurse_copy($src,$dst) { 
 				$dir = opendir($src); 
				@mkdir($dst); 
				while(false !== ( $file = readdir($dir)) ) { 
					if (( $file != '.' ) && ( $file != '..' )) { 
						if ( is_dir($src . '/' . $file) ) { 
							recurse_copy($src . '/' . $file,$dst . '/' . $file); 
						} 
						else { 
							copy($src . '/' . $file,$dst . '/' . $file); 
						} 
					} 
				} 
    				closedir($dir); 
			}

		        $build_with_sscae = 0;

		        if(isset($_POST['element_3_1'])) {
		                $build_with_sscae = 1;
		        } else {
		                $build_with_sscae = 0;
		        }

        		$task_name = $_POST['element_1'];
		        $task_name = strtolower($task_name);

			$recipient = $_POST['email'];
			echo "Email is: ".$recipient."</br>";
			
		        echo "<br>Future Version Will Check if Project Name: ".$task_name." is in LDAP</br>";
			
			$input_verified = 1;
			
			$email_regex = '[a-z]+';
			trim($recipient);
			strtolower($recipient);

			#$regexp = "/^[^0-9][A-z0-9_]+([.][A-z0-9_]+)*[@][A-z0-9_]+([.][A-z0-9_]+)*[.][A-z]{2,4}$/";
			$regexp = "/^[^0-9][A-z0-9_]+([.][A-z0-9_]+)*[@][j][p][l][.][n][a][s][a][.][g][o][v]$/";
			if (!preg_match($regexp, $recipient)) {
				$input_verified = 0;
			}
		        if(strlen(preg_replace('/\s+/u','',$task_name)) == 0) {
	        	        //die("You Must Input a Task Name");
				$input_verified = 0;
		        }
		        if(strlen(preg_replace('/[a-zA-Z0-9]/u','',$task_name)) != 0) {
		                //die("Spaces are not permited");
				$input_verified = 0;
		        }
			if($input_verified == 0) {
				$_POST['element_1'] = '^&^&^';	//This string will keep script from re-running on invalid input
				die("Input Not Valid");
			}			

			die("TEST");

		        /************************************************************************/
		        /*      THIS ARRAY CONTAINS ALL RPMS THAT HAVE TO BE CONFIGURED AROUND  */
		        /*      THE TASK NAME THEY CANNOT BE INSTALLED TILL AFTER THE PROJECT   */
		        /*      NAME IS IN LDAP                                                 */
		        /************************************************************************/
		        $index = 0;

		        if($build_with_sscae == 1) {
		                $array_of_packages = array      (
		                                                        "0"=>"codesonar",
	        	                                                "1"=>"coverity-P10",
	                	                                        "2"=>"coverity",
	                        	                                "3"=>"eclipse",
		                                                        "4"=>"findbugs",
		                                                        "5"=>"rapsde-sdf-format",
		                                                        "6"=>"slic",
	        	                                                "7"=>"rapsde-ldap-config",
		                                                        "8"=>"rapsde-yum-repo",
		                                                        "9"=>"shell_environments"
        		                                        );
                		$version_of_packages = array    (
	                        	                                "0"=>"3.5-p0",
	                                                        	"1"=>"5.2.0-1",
		                                                        "2"=>"5.2.0-1",
        	                                                	"3"=>"3.6.1-0.0",
		                                                        "4"=>"1.3.9-0.0",
		                                                        "5"=>"1.0-0",
		                                                        "6"=>"4.0-0.0",
		                                                        "7"=>"1.0.0-1",
		                                                        "8"=>"1.0-0.0",
		                                                        "9"=>"1.0-0"
	        	                                        );

		                echo "<br>SS-CAE Software Selected Building Following Packages</br>";
	        	        print_values($array_of_packages,$version_of_packages);
		        } else if($build_with_sscae == 0) {
		                $array_of_packages = array      (
	        	                                                "0"=>"eclipse",
	                	                                        "1"=>"findbugs",
	                        	                                "2"=>"rapsde-sdf-format",
	                                	                        "3"=>"slic",
		                                                        "4"=>"rapsde-ldap-config",
		                                                        "5"=>"rapsde-yum-repo",
	        	                                                "0"=>"shell_environments"
		                                                );
		                $version_of_packages = array    (
        	        	                                        "0"=>"3.6.1-0.0",
        		                                                "1"=>"1.3.9-0.0",
	                      		                                "2"=>"1.0-0",
	                        	                                "3"=>"4.0-0.0",
	                                	                        "4"=>"1.0.0-1",
		                                                        "5"=>"1.0-0.0",
		                                                        "0"=>"1.0-0"
	        	                                        );
        	        	echo "<br>SS-CAE Software NOT Selected Building Following Packages</br>";
	        	        print_values($array_of_packages,$version_of_packages);
	        	}
			//TIME HOW LONG IT TAKES TO BUILD RPMS		
        		$time_start = microtime_float();

			$top_dir = "/var/www/html/".$task_name."/rpmbuild";
			mkdir('/var/www/html/'.$task_name,0755);
			mkdir($top_dir, 0755);			

			$forward_dir = "/var/www/html/RPMS_TO_EMAIL/".$task_name;
		        mkdir($forward_dir, 0755);
			
			$template_dir = "/var/www/html/rpmbuild";

			recurse_copy($template_dir,$top_dir);

		        foreach($array_of_packages as $var){
	        	        $file = $top_dir."/SPECS/".$var.".spec.template";
		                $file_out = $top_dir."/SPECS/".$var.".spec";
		                $fp = fopen($file, "r");
		                $fp_out = fopen($file_out, "w+");
			        if(!$fp || !$fp_out) {
					die( "<br>ERROR: Could not open ".$file." or ".$file_out."</br>");
		                }else {
	        	                $text = fread($fp,filesize($file));
        	        	        $new_text = substr_replace($text,$task_name,24,41);
		                        $bytes_writen = fwrite($fp_out,$new_text,strlen($new_text));
		                        fclose($fp);
		                        fclose($fp_out);
		                        $rpmbuild_out=shell_exec("rpmbuild -ba --define '_topdir ".$top_dir."' ".$top_dir."/SPECS/".$var.".spec");
		                        $oldname=$top_dir."/RPMS/x86_64/".$var."-".$version_of_packages[$index].".x86_64.rpm";
		                        $newname=$forward_dir."/".$var."-".$version_of_packages[$index].".x86_64.rpm";
		                        if(!rename($oldname,$newname)) {
	                	                die("ERROR: Could not rename file </br<");
	                        	}
	        	        }	
        	        	$index++;
	        	}	

	        	$time_end = microtime_float();
		        $time = $time_end - $time_start;
	        	echo "All RPMs Built in ".$time." Seconds</br>";

		        $to = $recipient;
		        $subject = $task_name." RPMs Complete";
		        $random_hash = md5(date('r', time()));
		        $headers = "From: mehoggan@gmail.com\r\nReply-To: mehoggan@gmail.com";
		        ob_start(); //Turn on output buffering
		?>
			To Whom It May Concern

			The rpms are ready for the server you are building. Please go back to the webpage and click on the button for a direct link
			to the packages.
		<?php
	        	$message = ob_get_clean();
		        $mail_sent = @mail( $to, $subject, $message, $headers );
	        	echo $mail_sent ? "Mail sent" : "Mail failed";
		?>

			<img id="top" src="/images/top.png" alt="">
			<div id="form_container">
				<div>
		<?php
			echo '<a href="http://rpmdevelopmentserver.jpl.nasa.gov/RPMS_TO_EMAIL/'.$task_name.'"><img src="/images/click_here_button.jpg" alt="crap_button" /></a>'
		?>
				</div>
        		</div>
		        <img id="bottom" src="/images/bottom.png" alt="">
		<?php
		}     
	?>
</body>
</html>
