export array1=("depcomp" "install-sh" "missing" "COPYING" "INSTALL" "config.sub" "config.guess");
for i in "${array1[@]}";
do
    cp "/usr/share/automake-1.11/"${i} ./
done

cp "/usr/share/libtool/config/ltmain.sh" ./

export array2=(NEWS README AUTHORS ChangeLog);
for i in "${array2[@]}";
do
    touch ${i};
done
