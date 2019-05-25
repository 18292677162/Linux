#!/bin/bash
dir=$1
#ls -ld ./$dir
backup()
{
  tar -cvf /tmp/$dir.tar ./$dir
}
restore()
{
  tar -xvf /tmp/$dir ./$dir
}
testdir()
{
  if test ! -d $dir;then
    echo "this isn't dir"
    #exit 0
  fi
}
testdir

while true;do
  select opt in 'BackUp Dir' 'Restore Dir' 'Exit' ;do
    case $opt in
      'BackUp Dir')#there isn't number
        backup
        ;;
      'Restore Dir')
        restore
        ;;
      *)
        exit 0
        ;;
    esac
  done
done
