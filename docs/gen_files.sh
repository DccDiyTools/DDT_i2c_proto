#!/bin/sh

for ext in excalidraw plantuml
do
    #echo testing $ext
    for fileFound in img_src/*.$ext
    do
        if [ -f $fileFound ]; then
            #echo found $fileFound
            filename=$(basename -- "$fileFound")
            extension="${filename##*.}"
            filename="${filename%.*}"
            echo file $filename
            wget https://kroki.io/$ext/png/ --post-file $fileFound -O images/$filename.png
            #echo ext $extension
        fi
    done
done