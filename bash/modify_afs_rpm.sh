if [ -d "/usr/vice/cache" ]; then
	OUTPUT=`df -h /usr/vice/cache/ | grep /usr/vice/cache | awk '{print $2}'`; echo $OUTPUT;
	echo "${OUTPUT}" > tmp.file;
	sed s/M// tmp.file > tmp.file.cp
	cat tmp.file.cp > tmp.file;
	VALUE=`cat tmp.file`;
	rm tmp.file tmp.file.cp;
	
	let PRODUCT=$VALUE*1024*90/100;
	
	sed s/100000/${PRODUCT}/ /usr/vice/etc/cacheinfo > ./tmp.txt;
	cat ./tmp.txt;
	cp /usr/vice/etc/cacheinfo /usr/vice/etc/cacheinfo.backup
	cat ./tmp.txt /usr/vice/etc/cacheinfo
	rm ./tmp.txt
fi
