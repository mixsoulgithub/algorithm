LAST=$SECONDS
COMMAND="echo hello"
WAITTIME=1

while getopts "c:h:t:" flag
do
 case $flag in
    c) COMMAND=$OPTARG 
    ;;
    h) echo "-h help -c command -t wait time" 
    ;;
    t) WAITTIME=$OPTARG 
     echo WAITTIME=$WAITTIME
    ;; 
 esac
done

echo LAST=$LAST

inotifywait -m -r . -e modify |\
while read event
do 
    if (($SECONDS - $LAST < $WAITTIME))
    then 
     continue
    fi
    LAST=$SECONDS
    ${COMMAND}

done