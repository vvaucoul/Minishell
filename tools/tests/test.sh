#!/bin/sh
# MINISHELL TESTER 42
# Made by vvaucoul

# COLORS

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# CONFIG

clear

printf "$BOLDWHITE\t[CONFIG]\n\n$RESET"
SHOW_OUTPUT=0

if [ -z $1 ]
then
	sleep 0.01
else
	if [ $1 == "--show-output" ]
	then
		SHOW_OUTPUT=1
	else
		SHOW_OUTPUT=0
	fi
	printf "$BOLDBLUE\t- SHOW OUTPUT : [%s]$RESET\n" "$SHOW_OUTPUT"
	sleep .4
fi

# Change this path to your project path
# This test is to use with Linux OS. MAC OS use differents return and errors values
# Compile (default path = ../)

PPATH=../../

printf "$BOLDBLUE\n\t- Enter Project Path $BOLDYELLOW(default is ../../)$BOLDBLUE: $RESET"
read PPATH

if [ -z $PPATH ]
then
	PPATH=../../
fi
printf "$BOLDBLUE\t- Project Path : [%s]$RESET\n\n" "$PPATH"
sleep .4

printf "$BOLDGREEN\t%s$RESET\n" "MINISHELL TESTER"
cd $PPATH > /dev/null ; make fclean > /dev/null ; cd - > /dev/null
rm -f minishell
sleep 0.4

printf "\n$BOLDYELLOW%s$RESET " "Compilation en cours..."
cd ../../ > /dev/null
make re > /dev/null
cd - > /dev/null

if [ $? != "0" ]
then
	printf "$BOLDRED[%s]$RESET\n" "Makefile Error"
	exit
fi

cp ../../minishell . > /dev/null

if [ $? == "1" ]
then
	printf "$BOLDRED[%s]$RESET\n" "minishell not found"
	exit
fi

chmod 755 minishell

# START CMD to bash
unset OLDPWD
export OLDPWD=$PWD

function exec_test()
{
	sleep 0.02
	if [ $SHOW_OUTPUT == "1" ]
	then
		TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
		ES_1=$?
		sleep 0.02
		TEST2=$(echo $@ "; exit" | bash --posix 2>&-)
		ES_2=$?
	else
		TEST1=$(echo $@ "; exit" | ./minishell 2>&- > /dev/null)
		ES_1=$?
		sleep 0.02
		TEST2=$(echo $@ "; exit" | bash --posix 2>&- > /dev/null)
		ES_2=$?
	fi
	sleep 0.02

	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
		printf " $BOLDGREEN[%d]$RESET" "$ES_1"
	else
		printf " $BOLDRED%s$RESET" "✗ "
		printf " $BOLDRED[%d]$RESET" "$ES_1"
	fi
	printf "$BOLDBLUE \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

# BUILTINS TESTS

printf "\n\n$BOLDMAGENTA%s$RESET\n\n" "[BUILTINS TESTS]"
sleep 1

# ECHO TESTS

printf "\n\t- $BOLDWHITE%s$RESET\n\n" "ECHO TESTS"

exec_test 'echo'
exec_test 'echo -n'
exec_test 'echo -n -n -n -n'
exec_test 'echo test'
exec_test 'echo test test'
exec_test 'echo -n test test'
exec_test 'echo -n -n -n test test'
exec_test 'echo test -n test'
exec_test 'echo test -n test -n'
exec_test 'echo -n test -n test -n'
exec_test 'echo te-nst'
exec_test 'echo te -n st'
exec_test 'echo te-n st'
exec_test 'echo te -nst'

# PWD TESTS

printf "\n\t- $BOLDWHITE%s$RESET\n\n" "PWD TESTS"

exec_test 'pwd'
exec_test 'pwd test'
exec_test 'pwd test test test'
exec_test 'pwd 1 2 3 4 5'

# CD TESTS

printf "\n\t- $BOLDWHITE%s$RESET\n\n" "CD TESTS"

exec_test 'cd'
exec_test 'cd ../'
exec_test 'cd ../../'
exec_test 'cd /'
exec_test 'cd /home/user42/'
exec_test 'cd / ; cd -'
exec_test 'cd . ; cd -'
exec_test 'cd .. ; cd -'
exec_test 'cd /home/ ; cd -'
exec_test 'cd nofolder'
exec_test 'cd nofolder; cd -'
exec_test 'cd ---'
exec_test 'cd / ; cd ../../../../../../'
exec_test 'cd - - - -'
exec_test 'cd ; cd; cd ; cd ; cd; cd -'
exec_test 'cd - ; cd - ; cd - ; cd - ; cd -'
exec_test 'cd ~'
exec_test 'cd ~/Documents/'
exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; cd ..'

# ENV TESTS

printf "\n\t- $BOLDWHITE%s$RESET\n\n" "ENV TESTS"

exec_test 'env'
exec_test 'env test'
exec_test 'env -'
exec_test 'env env env'
exec_test 'env ; env'
exec_test 'env echo'
exec_test 'env pwd'

# EXPORT TESTS

printf "\n\t- $BOLDWHITE%s$RESET\n\n" "EXPORT TESTS"

exec_test 'export'
exec_test 'export toto=titi'
exec_test 'export toto='
exec_test 'export ='
exec_test 'export =titi'
exec_test 'export test = test'
exec_test 'export test = test ='
exec_test 'export test= toto='
exec_test 'export T E S T'
exec_test 'export test'
exec_test 'export toto'
exec_test 'export tr@l@l@'
exec_test 'export 42born2code=school'
exec_test 'export school=42'
exec_test 'export test=test test=toto test=test'
exec_test 'export test=@@@@----testerrror test=@'
exec_test 'export @@=@@ test=toto'
exec_test 'export 42=42; export school=42 school=43 school=@'
exec_test 'export test=1 test+=2 test+=3 test+=4'
exec_test 'export TEST=$PWD TEST+=$? ; ls invalidfile TEST+=$?'
exec_test 'export TEST+='
exec_test 'export TEST+=123'
exec_test 'export TEST===42'
exec_test 'export TE+T=4@2'
exec_test 'export TE+=ST42'
exec_test 'export TE==+=TEST'
exec_test 'export +=+=@'
exec_test 'export 1TEST= ;'
exec_test 'export TEST ;'
exec_test 'export ""="" ; '
exec_test 'export TES=T="" ;'
exec_test 'export TE+S=T="" ;'
exec_test 'export TEST=LOL ; echo $TEST ;'
exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
exec_test 'export TEST=LOL; export TEST+=LOL ; echo $TEST ;'
exec_test 'export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD'
exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; '

# UNSET TESTS

printf "\n\t- $BOLDWHITE%s$RESET\n\n" "UNSET TESTS"

exec_test 'unset'
exec_test 'unset toto'
exec_test 'unset ls'
exec_test 'unset /bin/ls'
exec_test 'unset unset'
exec_test 'unset ; unset ; unset ; unset'
exec_test 'unset OLDPWD ; env'
exec_test 'unset LESS ; env'
exec_test 'unset PAGER ; unset PAGER ; unset PAGER ; env'
exec_test 'export toto ; unset toto ; unset toti; env'
exec_test 'export test=toto ; unset toto; env ; unset test ; env'
exec_test 'export toto ; export toto ; unset toto ; env'
exec_test 'env ; unset . ; unset .. ; unset ... ; env'
exec_test 'unset TE ; env ; unset TERM ; env'
exec_test 'unset T ; env'
exec_test 'unset TERMINAL ; env'
exec_test 'unset nodeined ; env'
exec_test 'unset A'
exec_test 'unset t34T@111'

# EXIT TESTS
# Vérifiez bien que votre minishell récupère le premier exit
# Si exit 42 ; exit 23 -> valeur de retour = 42

printf "\n\t- $BOLDWHITE%s$RESET\n\n" "EXIT TESTS"

exec_test 'exit 42'
exec_test 'exit -42'
exec_test 'exit 42 43 44 45'
exec_test 'exit 259'
exec_test 'exit 1024'
exec_test 'exit -0'
exec_test 'exit 0'
exec_test 'exit 256'
exec_test 'exit -1'
exec_test 'exit 9223372036854775808'
exec_test 'exit -9223372036854775810'
exec_test 'exit invalid'
exec_test 'exit invalid command'
exec_test 'exit invalid command 42'
exec_test 'exit invalid 41 command 42'
exec_test 'exit 40 invalid 41 command 42'
exec_test 'exit 40 41 invalid 42'
exec_test 'exit -invalid'
exec_test 'exit -4a'
exec_test 'exit -410@'
exec_test 'exit -410@1'
exec_test 'exit 1-2'
exec_test 'exit 3+2'
exec_test 'exit +76432'
exec_test 'exit +abcde'
exec_test 'exit +32-3'
exec_test 'exit +@'
exec_test 'exit -@'
exec_test 'exit +42'
exec_test 'exit'
exec_test 'exit 43 ; exit 44 ; exit 45'

# REDIRECTIONS TESTS

function rm_redir_output()
{
	rm -f rrt rrt02 rrt03 drrt drrt02 drrt03 drrt04
}

printf "\n$BOLDMAGENTA%s$RESET\n\n" "[REDIRECTIONS TESTS]"
sleep 1

# REDIRECTION >

exec_test 'ls > rrt'
rm_redir_output
exec_test 'ls > rrt > rrt02 > rrt03'
rm_redir_output
exec_test 'ls > rrt > rrt02 -la > rrt03 -lR'
rm_redir_output
exec_test 'toto > rrt'
rm_redir_output
exec_test 'invalid_cmd > rrt > rrt02 > rrt03'
rm_redir_output

# REDIRECTION >>

exec_test 'ls > drrt ; ls >> drrt'
rm_redir_output
exec_test 'ls >> drrt'
rm_redir_output
exec_test 'toto >> drrt ; ls >> drrt ; toto >> drrt'
rm_redir_output
exec_test 'toto >> drrt >> drrt02 >> drrt03 >> drrt04'
rm_redir_output
exec_test 'ls >> drrt >> drrt02 >> drrt03 >> drrt04'
rm_redir_output
exec_test 'ls >> drrt -l >> drrt02 --color >> drrt03 -R >> drrt04 -a'
rm_redir_output
exec_test 'ls >> drrt -invalid >> drrt02 --invalid >> drrt03 -invalid'
rm_redir_output
exec_test 'toto > rrt >> rrt'
rm_redir_output
exec_test 'toto > rrt > rrt02 >> rrt >> rrt02'
rm_redir_output
exec_test 'ls > rrt >> rrt02 >> rrt > rrt02 >> drrt03'
rm_redir_output
exec_test 'ls -la > rrt --color >> drrt -invalid > rrt02 >> drrt02 -invalid >> drrt03 -R'
rm_redir_output

# REDIRECTION <

exec_test 'cat < toto'
rm_redir_output
exec_test 'cat < test.sh'
rm_redir_output
exec_test 'cat <'
rm_redir_output
exec_test 'cat < -e'
rm_redir_output
exec_test 'cat < toto -e'
rm_redir_output
exec_test 'cat < test.sh -e'
rm_redir_output
exec_test 'cat -e < test.sh'
rm_redir_output
exec_test 'cat < toto -invalid'
rm_redir_output
exec_test 'cat -invalid < toto -invalid'
rm_redir_output
exec_test 'cat < -invalid'
rm_redir_output

# PIPES TESTS

printf "\n$BOLDMAGENTA%s$RESET\n\n" "[PIPES TESTS]"
sleep 1

exec_test 'echo test | cat -e'
exec_test 'ps aux | grep root | grep linux | grep x86'
exec_test 'ps aux | grep invalid | grep invalid'
exec_test 'echo test |'
exec_test '| echo test'
exec_test '| | |'
exec_test '|'
exec_test 'ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e'
exec_test 'ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps | ps'
exec_test 'ls | | ls'
exec_test 'ls | ls -la | ls -R | ls'
exec_test 'ls | cat -e'
exec_test 'ls | cat -e | cat -e | cat -e'
exec_test 'ls -l -R -a -invalid | cat -e'
exec_test 'cat -e | ls -l -R -a -invalid'

# MINISHELL BASICS

printf "\n$BOLDMAGENTA%s$RESET\n\n" "[MINISHELL BASICS TESTS]"
sleep 1

exec_test ''
exec_test ';;'
exec_test ';;;'
exec_test ';'
exec_test 'invalid'
exec_test '.'
exec_test '..'
exec_test '- - -'
exec_test '<'
exec_test '>'
exec_test '< < <'
exec_test '> > >'
exec_test '>>'
exec_test '>> < >'
exec_test '><><><'
exec_test '>><>><>><>>'
exec_test '			ls			-la'
exec_test '			echo		tab'
exec_test 'invalidcommand_02'
exec_test 'cd invaliddirectory'
exec_test 'ls -la | invalid'
exec_test 'invalid | ls -la'
exec_test '~'
exec_test ''

rm minishell
