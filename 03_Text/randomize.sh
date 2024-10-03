#!/bin/sh

if [ -z $1 ]; then
    pause=0
else
    pause=$1
fi

tput clear
terminal_lines=$(tput lines)
terminal_cols=$(tput cols)

bytes=$(od -v -An -tx1)

cur_line=0
cur_col=0
num_lines=0
num_cols=0

for byte in $bytes; do
    if [ $byte != "0a" ]; then
        cur_col=$(($cur_col + 1))
    else
        cur_line=$(($cur_line + 1))
        cur_col=0
    fi
    if [ $cur_col -gt $num_cols ]; then
        num_cols=$cur_col
    fi
    if [ $cur_line -gt $num_lines ]; then
        num_lines=$cur_line
    fi
done

offset_cols=$((($terminal_cols - $num_cols) / 2))
offset_lines=$((($terminal_lines - $num_lines) / 2))

index=0
cur_line=0
cur_col=0
num_lines=0
num_cols=0

for byte in $bytes; do
    if [ $byte != "20" ]; then
        echo "$byte#$cur_line#$cur_col"
    fi
    if [ $byte != "0a" ]; then
        cur_col=$(($cur_col + 1))
    else
        cur_line=$(($cur_line + 1))
        cur_col=0
    fi
done | shuf | while read element; do
    byte=$(echo $element | cut -d '#' -f 1)
    char=$(/bin/echo -e "\x$byte")
    line=$(($offset_lines + $(echo $element | cut -d '#' -f 2)))
    col=$((offset_cols + $(echo $element | cut -d '#' -f 3)))
    tput cup $line $col
    echo $char

    tput cup $(($terminal_lines - 1)) 0
    if [ $pause != 0 ]; then
        sleep $pause
    fi
done
