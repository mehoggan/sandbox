BASEPATH=/home/${USER}/rpmbuild/
PACKAGE="rapsde-ldap-config"
rpmbuild -ba ${BASEPATH}SPECS/${PACKAGE}.spec; 
sudo rpm -e ${PACKAGE}
sudo rpm -ivh ${BASEPATH}RPMS/x86_64/${PACKAGE}-2.0.0-1.x86_64.rpm
