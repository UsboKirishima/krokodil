#!/usr/bin/sh sh

rm config/token.h 
touch config/token.h 
token=$(zenity --title="Krokodil" --text " Enter your token " --entry --width 330)
echo -e "#define DS_TOKEN \"$token\"" >> config/token.h \