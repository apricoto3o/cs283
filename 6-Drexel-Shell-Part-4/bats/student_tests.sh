#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Testing pwd command execution" {
    run ./dsh <<EOF                
pwd
EOF
    [ "$status" -eq 0 ]
}

@test "Testing echo command with argument" {
    run ./dsh <<EOF
echo hi there
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"hi there"* ]]
}

@test "Testing multiple commands using pipes" {
    run ./dsh <<EOF                
ls | grep dshlib.c
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"dshlib.c"* ]]
}

@test "Testing command sub" {
    run ./dsh <<EOF                
echo \$(whoami)
EOF
    [ "$status" -eq 0 ]
}

@test "Testing built-in cd" {
    run ./dsh <<EOF
cd /
pwd
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"/"* ]]
}

@test "Testing exit command" {
    run ./dsh <<EOF
exit
EOF
    [ "$status" -eq 0 ]
}

@test "Testing ls -l output" {
    run ./dsh <<EOF
ls -l
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"total"* ]]
}

@test "Testing mkdir and rmdir" {
    run ./dsh <<EOF
mkdir testdir && ls | grep testdir && rmdir testdir
EOF
    [ "$status" -eq 0 ]
}

@test "Testing chained commands &&" {
    run ./dsh <<EOF
echo "first" && echo "second"
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"first"* ]]
    [[ "$output" == *"second"* ]]
}

@test "Testing shell stops server" {
    run ./dsh -c 127.0.0.1 <<EOF
stop-server
EOF
    [ "$status" -eq 0 ]
}

@test "Testing single and double quotes" {
    run ./dsh <<EOF
echo 'Single quotes test' && echo "Double quotes test"
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *"Single quotes test"* ]]
    [[ "$output" == *"Double quotes test"* ]]
}

@test "Testing process sub" {
    run ./dsh <<EOF
diff <(echo test1) <(echo test2)
EOF
    [ "$status" -eq 0 ]
}

@test "Testing stopping server with command" {
    run ./dsh -c 127.0.0.1 <<EOF
stop-server
EOF
    [ "$status" -eq 0 ]
}
