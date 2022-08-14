#! /bin/bash

HR="----------------------------------------"

cecho() {
  RED="\033[0;31m"
  GREEN="\033[0;32m"
  YELLOW="\033[1;33m"
  CYAN="\033[0;36m"
  NC="\033[0m"
  BOLD="\033[1m"
  NORMAL="\033[22m"
  printf "${!1}${BOLD}${2}${NORMAL}${NC}\n"
}

describe() {
  cecho "CYAN" $HR
  cecho "CYAN" "$1"
  cecho "CYAN" $HR
}
