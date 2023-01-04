ROOT="/tmp/git-playground/"
SRCDIR=`pwd`
export GIT_CONFIG_GLOBAL=/tmp/git-config-for-demo

if [ -e $GIT_CONFIG_GLOBAL ]; then
    rm $GIT_CONFIG_GLOBAL
fi

git config --global user.email "jesper.pedersen@kdab.com"
git config --global user.name "Jesper K. Pedersen"


__STEP__=0

function run() {
  CUR=$PWD/
  DIR=${CUR#"$ROOT"}

  if [ "$DIR" == "" ]; then
    DIR="/"
  fi

  let __STEP__++
  echo -n -e "\n$__STEP__ (\e[43m\e[30m$DIR\e[49m\e[97m) \e[07m$1\e[0m       "
  read dummy
  eval $1
}

function comment() {
  echo -e "\e[40\e[1;33m$1\e[0m"
}

# Don't ask, I googled like crazy to get this working :-)
function title() {
  termwidth="$(tput cols)"
  padding="$(printf '%0.1s' ' '={1..500})"
  printf '\n\n\e[44m\e[1;37m%*.*s %s %*.*s\e[0m\n' 0 "$(((termwidth-2-${#1})/2))" "$padding" "$1" 0 "$(((termwidth-1-${#1})/2))" "$padding"
}
