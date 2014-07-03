<!--
	function Validate(form)
	{
		var ret = true;
		if(document.mainform.nfname.value == "")
		{
			ret = false;
		}
		else if(document.mainform.nfname.value != "")
		{
			var fname = document.mainform.nfname.value;
			ret = true;
		}
		if(document.mainform.nlname.value == "")
		{
			ret = false;
		}
		else if(document.mainform.nlname.value != "")
		{
			var lname = document.mainform.nlname.value;
			ret = true;
		}
		if(document.mainform.nmemnum.value == "")
		{
			ret = false;
		}
		else if(document.mainform.nmemnum.value != "")
		{
			var memnum = document.mainform.nmemnum.value;
			ret = true;
		}
		if(document.mainform.naddrs.value == "")
		{
			ret = false;
		}
		else if(document.mainform.naddrs.value != "")
		{
			var addrs = document.mainform.naddrs.value;
			ret = true;
		}
		return ret;
	}

	function updateDay()
	{
		var input = document.getElementById('smdob');
		var update = document.getElementById('ifname');
		update.value = input.value;		
	}
-->
