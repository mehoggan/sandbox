export array1=("depcomp" "install-sh" "missing" "COPYING" "INSTALL")
for i in "${array1[@]}";
do
    cp "/usr/share/automake-1.11/"${i} ./;
done

export array2=(NEWS README AUTHORS ChangeLog)
for i in "${array2[@]}";
do
    touch ${i};
done

