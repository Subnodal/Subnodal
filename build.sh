#!/bin/bash

mkdir -p rootfs

find rootsrc -type f | while read -r sourcePath; do
    relativePath=${sourcePath#rootsrc}
    destinationPath=rootfs$relativePath

    mkdir -p $(dirname $destinationPath)

    echo "$sourcePath -> $destinationPath"

    minify --html $sourcePath

    case ${sourcePath##*.} in
        html|css|js) minify $sourcePath > $destinationPath ;;
        *) cp $sourcePath $destinationPath ;;
    esac
done

pio run --target upload
pio run --target uploadfs