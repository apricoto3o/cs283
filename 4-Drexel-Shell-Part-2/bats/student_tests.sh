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

@test "Testing exit command" {
    run ./dsh <<EOF
exit
EOF

    [ "$status" -eq 0 ]
}

@test "Testing change directory command" {
    run ./dsh <<EOF
cd /
EOF

    [ "$status" -eq 0 ]
}

@test "Testing no command input" {
    run ./dsh <<EOF

EOF

    [ "$status" -eq 0 ]
    [[ "$output" = *"warning: no commands provided"* ]]
}

@test "Testing for spaces between ls" {
    run ./dsh <<EOF
l s
EOF

    [ "$status" -eq 0 ]
}

@test "Testing ls with arguments" {
    run ./dsh <<EOF
ls -l -a
EOF

    [ "$status" -eq 0 ]
}

@test "Testing cd with no arguments" {
    run ./dsh <<EOF
cd
EOF

    [ "$status" -eq 0 ]
}

@test "Testing command with spaces using quotes" {
    run ./dsh <<EOF
echo "one two three"
EOF

    [ "$status" -eq 0 ]
    [[ "$output" = *"one two three"* ]]
}

@test "Testing command piping" {
    run ./dsh <<EOF
ls | grep "dsh"
EOF

    [ "$status" -eq 0 ]
}

@test "Testing multiple commands" {
    run ./dsh <<EOF
echo "One"
echo "Two"
EOF

    [ "$status" -eq 0 ]
    [[ "$output" = *"One"* ]]
    [[ "$output" = *"Two"* ]]
}

@test "Testing command with piping" {
    run ./dsh <<EOF
ls | grep "dsh"
EOF

    [ "$status" -eq 0 ]
}

@test "Testing redirection" {
    run ./dsh <<EOF
echo "one two" > something.txt
cat something.txt
EOF

    [ "$status" -eq 0 ]
    [[ "$output" = *"one two"* ]]
}

@test "Testing command with special characters" {
    run ./dsh <<EOF
echo "# @ $ % &"
EOF

    [ "$status" -eq 0 ]
    [[ "$output" = *"# @ $ % &"* ]]
}

