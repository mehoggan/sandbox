export array1=("depcomp" "install-sh" "missing" "COPYING" "INSTALL" "aclocal.m4" "autom4te.cache")
for i in "${array1[@]}";
do
    rm -rf ${i};
done

export array2=(NEWS README AUTHORS ChangeLog)
for i in "${array2[@]}";
do
    rm -rf ${i};
done

