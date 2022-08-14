#! /bin/bash

# Load helper fns
source .tests/helpers.sh

total=0
status_ko=0
infile=.tests/infile
outfile_me=.tests/out.me
outfile_tester=.tests/out.tester

get_results() {
  describe "TEST RESULTS"
  cecho "NC"    "TOTAL: $total"
  cecho "GREEN" "OKs:   $(($total - $status_ko))"
  if [ $status_ko -gt 0 ]
  then
    cecho "RED"   "KOs:   $status_ko"
    exit 1
  fi
}

# Trap signal=EXIT and invoke get_results fn
trap get_results EXIT

rm_outfiles() {
  rm -rf $outfile_tester $outfile_me
}

test() {
  local cmd1=$1
  local cmd2=$2
  local task=$3
  local test_case=$(($total + 1))
  local diff_dest=.tests/test.$test_case.diff

  runIfTaskDefined() {
    if [[ "$task" != "" ]]
    then
      echo "Running task: $task"
      eval "$task"
    fi
  }

  cecho "BOLD" "Case #$test_case"

  echo "Tester: <$infile $cmd1 | $cmd2 > $outfile_tester"
  rm_outfiles
  runIfTaskDefined
  <$infile $cmd1 | $cmd2 > $outfile_tester 2>&1
  result_tester=$(cat $outfile_tester)
  echo "===TESTER===" > $diff_dest
  cat $outfile_tester >> $diff_dest

  echo "Pipex: ./pipex \"$infile\" \"$cmd1\" \"$cmd2\" \"$outfile_me\""
  rm_outfiles
  runIfTaskDefined
  ./pipex "$infile" "$cmd1" "$cmd2" "$outfile_me" 2>&1
  result_me=$(cat $outfile_me)
  echo "===PIPEX===" >> $diff_dest
  cat $outfile_me >> $diff_dest

  # We store file output on variables then create both files after user,tester executes
  echo -n "$result_me" | tee $outfile_me > /dev/null
  echo -n "$result_tester" | tee $outfile_tester > /dev/null
  echo "===DIFF===" >> $diff_dest
  diff $outfile_tester $outfile_me >> $diff_dest
  testdiff=$(diff $outfile_tester $outfile_me)
  echo -n "Result: "
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
test "cat" "ls -l" #1
test "ls -la" "cat" #2
test "" "" #3
test "ls" "" #4

describe "Void infile with file creation"
create_somefile="echo 'some content' > somefile"
create_many_mocks="touch {0..9}.mock"
test "rm -rf somefile" "echo -n 'void'" "$create_somefile" #5
test "rm -rf *.mock" "find . -name .mock" "$create_many_mocks" #6
test "find . -name .mock" "rm -rf *.mock" "$create_many_mocks" #7
test "tee .tempfile" "tee .tempfile.other" #8

describe "infile with content from /cat/passwd"
cat /etc/passwd > $infile
test "cat" "tee .tempfile" #9
test "cat" "cat" #10
test "grep #" "tee .tempfile" #11
test "grep -v #" "sed s/://g" #12
test "cat" "sed s/://" #13
test "tr ':' '_'" "wc -c" #14
test "wc -c" "awk {print\$1}" #15