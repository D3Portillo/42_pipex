#! /bin/bash

HR="----------------------------------------"
total=0
status_ko=0

infile=.tests/infile
outfile_me=.tests/out.me
outfile_tester=.tests/out.tester

cecho () {
  RED="\033[0;31m"
  GREEN="\033[0;32m"
  YELLOW="\033[1;33m"
  CYAN="\033[0;36m"
  NC="\033[0m"
  BOLD="\033[1m"
  NORMAL="\033[22m"
  printf "${!1}${BOLD}${2}${NORMAL}${NC}\n"
}

describe () {
  cecho "CYAN" $HR
  cecho "CYAN" "$1"
  cecho "CYAN" $HR
}

get_results () {
  describe "TEST RESULTS"
  cecho "NC"    "TOTAL: $total"
  cecho "GREEN" "OKs:   $(($total - $status_ko))"
  if [ $status_ko -gt 0 ]
  then
    cecho "RED"   "KOs:   $status_ko"
    exit 1
  fi
}

rm_outfiles() {
  rm -rf $outfile_tester $outfile_me
}

trap get_results EXIT

test () {
  cmd1=$1
  cmd2=$2

  echo "Tester: <$infile $cmd1 | $cmd2 > $outfile_tester"
  rm_outfiles
  <$infile $cmd1 | $cmd2 > $outfile_tester 2>/dev/null
  result_tester=$(cat $outfile_tester)

  echo "Pipex: ./pipex \"$infile\" \"$cmd1\" \"$cmd2\" \"$outfile_me\""
  rm_outfiles
  ./pipex "$infile" "$cmd1" "$cmd2" "$outfile_me" 2>/dev/null
  result_me=$(cat $outfile_me)

  # We store file output on variables then create both files after user,tester executes
  cat "$result_me" | tee $outfile_me > /dev/null
  cat "$result_tester" | tee $outfile_tester > /dev/null
  testdiff=$(diff $outfile_tester $outfile_me || echo "ERROR")
  echo -n "Status: "
  ((total++))
  # Diff for both user,tester out filess should be NONE. Zero
  if [[ "$testdiff" == "" ]]
  then
    cecho "GREEN" "OK"
  else
    cecho "RED" "KO"
    ((status_ko++))
  fi
  echo
}

describe "MAKEFILE"
make re

describe "Void infile"
test "cat" "ls -l"
test "ls -la" "cat"
test "" ""
test "ls" ""
cat "some content" > somefile
test "rm -rf somefile" "echo -n 'void'"