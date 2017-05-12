#!/bin/bash
SAVE_DIR=".makefile_saves"
mkdir -p $SAVE_DIR
SAVE_NAME=`date +"%Y-%m-%d_%T"`
LAST_SAVE=`find $SAVE_DIR | sort -r | head -n1`
CUR_FILE="$SAVE_DIR/$SAVE_NAME"
CREATED_SAVE=false

if [[ $LAST_SAVE == $SAVE_DIR || `diff $1 $LAST_SAVE` ]]; then
	CREATED_SAVE=true
	cat $1 > "$CUR_FILE"
elif [[ ! $LAST_SAVE == $SAVE_DIR ]]; then
	if [[ ! $LAST_SAVE == $CUR_FILE ]]; then
		mv $LAST_SAVE $CUR_FILE
	fi
fi

while [[ ! LINE=$(line) ]]; do
	# if [[ $LINE == "FILES"* ]]; then
	# 	echo -ne "FILES="
	# 	SED_EXP="s\\srcs/\\\\g"
	# 	FILES="find srcs -name *.cpp -o -name *.c"
	# 	FIRST_LINE=`$FILES | head -n1 | sed $SED_EXP`
	# 	LAST_LINE=`$FILES | tail -n1 | sed $SED_EXP`
	# 	for FILE in `$FILES | sed $SED_EXP`; do
	# 		TABS="\t\t"
	# 		if [[ $FILE == $FIRST_LINE ]]; then
	# 			TABS="\t"
	# 		fi
	# 		if [[ $FILE == $LAST_LINE ]]; then
	# 			echo -e $TABS$FILE
	# 		else
	# 			echo -e $TABS$FILE"\\"
	# 		fi
	# 	done
	# else
		echo -e $LINE
	# fi
done < $1

if $CREATED_SAVE; then
	printf "\033[7;49;32mSave created at: ./$CUR_FILE\033[m\n"
fi
printf "\033[7;49;34mSuccessfully updated the Makefile !\033[m\n"
