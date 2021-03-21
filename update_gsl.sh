#!/bin/bash

echo "$(tput setaf 6)Update Guideline Support Library$(tput sgr 0)"

#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# GIT Version
#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

GIT_VER_TMP=$(git version)
echo $GIT_VER_TMP
GIT_VER_TMP1=$(echo $GIT_VER_TMP | cut -b 13)
GIT_VER_TMP2=$(echo $GIT_VER_TMP | cut -b 15-16)
GIT_VER=$(expr $GIT_VER_TMP1 \* "100" + $GIT_VER_TMP2)
echo "$(tput setaf 3)Git Version as Integer: $GIT_VER $(tput sgr 0)"

#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Test/Ensure target dir exists
#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

EXT_DIR="./external"

if test ! -d $EXT_DIR
then
  mkdir $EXT_DIR  
fi

cd $EXT_DIR
pwd

#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
# Fetch GSL from Github
#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

SRC_DIR="./GSL"

if [ ! -d $SRC_DIR ]
then
  echo "$(tput setaf 2)Cloning...$(tput sgr 0)"  
  git clone https://github.com/microsoft/GSL.git --branch main;  
else
  echo "$(tput setaf 2)Fetching...$(tput sgr 0)"    
  cd $SRC_DIR;
  pwd;  
  git fetch https://github.com/microsoft/GSL.git --tags --progress main;
  cd ..;
fi

#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

echo "$(tput setaf 2)Switch to Revision$(tput sgr 0)"
cd $SRC_DIR;
git switch --progress main
git checkout --detach tags/v3.1.0;
git branch -a
git status;
cd ..;

#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

cd ..;
