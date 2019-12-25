if [ "$#" -ne 2 ] ; then
	echo "Usage: (Target file) (Destination folder)"
	echo Example: somedir/myfile.txt mydestination
	exit
fi

TARGET_FILE=$1
TARGET_FILENAME=`basename $1`
TARGET_FILENAME_EXTENSIONLESS=`echo $TARGET_FILENAME | sed -e 's/\./_/'`_transpiled
TARGET_DIR=`dirname $1`
HEADERS_DESTINATION=$2

COMMENT="//(AUTO-GENERATED FROM \""$TARGET_FILE"\", DO NOT EDIT THIS FILE)"
CONSTANT_NAME=`echo $TARGET_FILENAME_EXTENSIONLESS | sed 's/./\U&/g'`

DESTINATION_HEADER=$HEADERS_DESTINATION/$TARGET_FILENAME_EXTENSIONLESS.h
touch $DESTINATION_HEADER

echo $COMMENT > $DESTINATION_HEADER
echo "extern const char* "$CONSTANT_NAME";" >> $DESTINATION_HEADER

DESTINATION_SOURCE=$HEADERS_DESTINATION/$TARGET_FILENAME_EXTENSIONLESS.cpp
touch $DESTINATION_SOURCE

echo $COMMENT > $DESTINATION_SOURCE
echo "#include \"$TARGET_FILENAME_EXTENSIONLESS.h\"" >> $DESTINATION_SOURCE
echo "const char* "$CONSTANT_NAME" =" >> $DESTINATION_SOURCE
cat $TARGET_FILE \
| sed 's/\\/\\\\/g' \
| sed 's/"/\\"/g' \
| sed 's/^/"/' \
| sed 's/$/\\n"/' \
>> $DESTINATION_SOURCE
echo ";" >> $DESTINATION_SOURCE
