CURRENT=$1
if [ -e "$CURRENT" ] && [ ! -z "$CURRENT" ]; then
	SAVE_DIR=".makefile_saves"
	mkdir -p $SAVE_DIR
	SAVE_NAME=`date +"%Y-%m-%d_%T"`
	LAST_SAVE=`find $SAVE_DIR | sort -r | head -n1`
	CUR_FILE="$SAVE_DIR/$SAVE_NAME"

	if [[ $LAST_SAVE == $SAVE_DIR || `diff $CURRENT $LAST_SAVE` ]]; then
		cat $CURRENT > "$CUR_FILE"
		printf "\033[7;49;34mSave created at: $CUR_FILE\033[m\n"
	elif [[ ! $LAST_SAVE == $SAVE_DIR ]]; then
		if [[ ! $LAST_SAVE == $CUR_FILE ]]; then
			mv $LAST_SAVE $CUR_FILE
		fi
	fi

	sed '/^FILES/,/\Z/d' $CUR_FILE > $CURRENT
	echo "FILES =\\" >> $CURRENT
	find srcs -name *.cpp -o -name *.c | sed 's/srcs\///g' | sed 's/$/\\/g' | sed 's/\Z//g' | sed '$ s/.$//' >> $CURRENT
	echo "" >> $CURRENT
	sed -n '/SRC/,$p' $CUR_FILE >> $CURRENT
	printf "\033[7;49;34mSuccessfully updated the Makefile !\033[m\n"
else
	printf "\033[7;49;31mInvalid file !\033[m\n"
fi
