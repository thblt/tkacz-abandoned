make clean
qmake -project -o Tkacz.pri
qmake Tkacz.pro
if ./builders/tzuic.py xml/ build/tz_uibase.h
    then if  ./builders/dir2qrc.py -multi build resources/qrc 
        then if  qmake Tkacz.pro 
            then  make 
        fi
    fi
fi
