Summary: Configures RapSDE systems for a specified project in LDAP
Name: rapsde-ldap-config
Version: 2.0.0
Release: 1%{?dist}
License: JPL site-license
Group: System Environment/Base
URL: http://jpl.nasa.gov
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
AutoReq: no

%description
Each given server will have a specified DN, the users of this RPM must configure 
their respective groups (and netgroups) inside LDAP at dir.jpl.nasa.gov before 
running this RPM. Once run this RPM will change the default LDAP configuration 
from how an SA configures it to system usable only by that task.

%prep
%setup -q

%build

%install
rm -rf %{buildroot}
%{__mkdir_p} %{buildroot}/etc/openldap/cacerts

#%{__cp} ./*.pem %{buildroot}/etc/openldap/cacerts/
#%{__cp} ./nsswitch.conf %{buildroot}/etc/

#%{__mkdir_p} %{buildroot}/etc/pam.d
#%{__cp} ./system-auth %{buildroot}/etc/pam.d/
#%{__cp} ./sshd %{buildroot}/etc/pam.d/

#mkdir -p %{buildroot}/etc/security/
#%{__cp} ./access.conf %{buildroot}/etc/security/access.conf

%clean
#rm -rf %{buildroot}

%post

CONTINUE="0";

date
if [ -f /usr/local/jpl/etc/ahs/rapsde.conf ]; then
	TASKNAME=`cat /usr/local/jpl/etc/ahs/rapsde.conf`
	if [ "${TASKNAME}" == "" ]; then
		echo "ERROR: Please input project name into /usr/local/jpl/etc/ahs/rapsde.conf";
	fi
	echo "Checking LDAP for ${TASKNAME}...";
	PROJECT_LDAP_ENTRY_COUNT=`ldapsearch -x -ZZ -h ldap.jpl.nasa.gov -b 'ou=projects,dc=dir,dc=jpl,dc=nasa,dc=gov' "ou=${TASKNAME}"|grep numEntries|awk '{print $3}'`;
	if [ "${PROJECT_LDAP_ENTRY_COUNT}" == "1" ]; then
        	GROUP_LDAP_ENTRY_COUNT=`ldapsearch -x -ZZ -h ldap.jpl.nasa.gov -b 'ou=rapsde,ou=projects,dc=dir,dc=jpl,dc=nasa,dc=gov' "cn=${TASKNAME}"|grep numEntries|awk '{print $3}'`;
	        if [ "${GROUP_LDAP_ENTRY_COUNT}" == "" ]; then
			echo "ERROR: both netgroup and POSIX group does not exist with same name as ${TASKNAME}";
        	elif [ "${GROUP_LDAP_ENTRY_COUNT}" == "1" ]; then
                	echo "ERROR: either netgroup or POSIX group does not exist with same name as ${TASKNAME}";
        	elif [ "${GROUP_LDAP_ENTRY_COUNT}" == "2" ]; then
                	echo "SUCESS: configuring server";
			CONTINUE="1";
        	fi
	elif [ "${PROJECT_LDAP_ENTRY_COUNT}" == "" ]; then
        	echo "ERROR: ${TASKNAME} does not exist in LDAP";
	else
        	echo "ERROR: Unknown";
	fi
elif [ ! -f /usr/localjpl/etc/ahs/rapsde.conf ]; then
	echo "Bad Job ${TASKNAME} Not Found"; 
fi

if [ "${CONTINUE}" == "1" ]; then
	echo "Modifying access.conf...";
	#sed "s/\+\:ALL\:[a-zA-Z0-9]/+:@"${TASKNAME}":ALL\n+:ALL:cron crond/g" /etc/security/access.conf > /etc/security/access.conf.tmp;
	#mv /etc/security/access.conf.tmp /etc/security/access.conf;
	#rm -f /etc/security/access.conf.tmp;
	echo "Running authconfig tool...";
	#authconfig 	--enableshadow --enablemd5 --disablenis --enableldap --enableldapauth --ldapserver=ldap.jpl.nasa.gov \ 
	#--ldapbasedn=ou=%{small_task_name},ou=projects,dc=dir,dc=jpl,dc=nasa,dc=gov --enableldaptls --disablekrb5 --enablemkhomedir --update \
elif [ "${CONTINUE}" != "1" ]; then
	echo "ERROR: LDAP Configuration not correct";
fi

%postun

%files 
#%defattr(644,root,root)
#/etc/openldap/cacerts/LMCA_ca.pem
#/etc/openldap/cacerts/self-signed_ca.pem
#/etc/openldap/cacerts/verisign_ca.pem
#/etc/openldap/cacerts/verisign_intermediate_ca.pem
#/etc/openldap/cacerts/verisign_intermediate_ca_new.pem
#/etc/pam.d/system-auth
#/etc/pam.d/sshd
#/etc/security/access.conf
#/etc/nsswitch.conf

%changelog
* Tue Jun 7 2011 Matthew Hoggan <matthew.e.hoggan@jpl.nasa.gov> - 2.0.0
- No longer depends on apache to give its task name, it now obtains data
- for project from /usr/local/jpl/ahs/rapsde.conf

* Thu May 14 2011 Matthew Hoggan <matthew.e.hoggan@jpl.nasa.gov> - 1.0.0
- Initial Release
