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
  local cmd1=$1
  local cmd2=$2
  local task=$3

  runIfTaskDefined() {
    if [[ "$task" != "" ]]
    then
      echo "Running task: $task"
      eval "$task"
    fi
  }

  echo "Tester: <$infile $cmd1 | $cmd2 > $outfile_tester"
  rm_outfiles
  runIfTaskDefined
  <$infile $cmd1 | $cmd2 > $outfile_tester 2>&1
  result_tester=$(cat $outfile_tester)

  echo "Pipex: ./pipex \"$infile\" \"$cmd1\" \"$cmd2\" \"$outfile_me\""
  rm_outfiles
  runIfTaskDefined
  ./pipex "$infile" "$cmd1" "$cmd2" "$outfile_me" 2>&1
  result_me=$(cat $outfile_me)

  # We store file output on variables then create both files after user,tester executes
  echo -n "$result_me" | tee $outfile_me > /dev/null
  echo -n "$result_tester" | tee $outfile_tester > /dev/null
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

describe "Test Void infile content"
test "cat" "ls -l"
test "ls -la" "cat"
test "" ""
test "ls" ""

describe "Void infile with file creation"
create_somefile="echo 'some content' > somefile"
create_many_mocks="touch {0..9}.mock"
test "rm -rf somefile" "echo -n 'void'" "$create_somefile"
test "rm -rf *.mock" "ls *.mock" "$create_many_mocks"
test "find . -name .mock" "rm -rf *.mock" "$create_many_mocks"
test "tee .tempfile" "tee .tempfile.other" 

describe "infile with content from /cat/passwd"
cat /etc/passwd > $infile
test "cat" "tee .tempfile"
test "cat" "cat"
test "grep #" "tee .tempfile"
test "grep -v #" "sed 's/://g'"
test "cat" "sed 's/://'"
test "tr ':' '_'" "wc -c"
test "wc -c" "awk '{print \$1}'"