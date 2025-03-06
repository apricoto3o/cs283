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

@test "Testing the command execution pwd" {
    run ./dsh <<EOF
pwd
EOF
    [ "$status" -eq 0 ]
}

@test "Testing command cd to tmp and checking the location" {
    run ./dsh <<EOF
cd /tmp
pwd
EOF
    [[ "$output" == *"/tmp"* ]]
}

@test "Testing command exit terminates out of shell" {
    run ./dsh <<EOF
exit
EOF
    [ "$status" -eq 0 ]
}

@test "Testing piping ls | grep" {
    run ./dsh <<EOF
ls | grep dshlib
EOF
    [[ "$output" == *"dshlib.c"* ]]
}

@test "Testing multiple commands with pipes" {
    run ./dsh <<EOF
echo "hello world" | tr a-z A-Z
EOF
    [[ "$output" == *"HELLO WORLD"* ]]
}

@test "Testing that empty command prints warning" {
    run ./dsh <<EOF

EOF
    [[ "$output" == *"warning: no commands provided"* ]]
}

@test "Testing command execution with arguments" {
    run ./dsh <<EOF
echo hello there
EOF
    [[ "$output" == *"hello there"* ]]
}

@test "Testing command with special characters" {
    run ./dsh <<EOF
echo '$HOME'
EOF
    [[ "$output" == *"$HOME"* ]]
}

@test "Testing empty command, should warn" {
    run ./dsh <<EOF

EOF
    [[ "$output" == *"warning: no commands provided"* ]]
}

@test "Testing piping ls | wc -l" {
    run ./dsh <<EOF
ls | wc -l
EOF
    [ "$status" -eq 0 ]
}

@test "Testing command cd with no argument" {
    run ./dsh <<EOF
cd
pwd
EOF
    [ "$status" -eq 0 ]
}

@test "Testing basic command echo" {
    run ./dsh <<EOF
echo "test"
EOF
    [[ "$output" == *"test"* ]]
}
