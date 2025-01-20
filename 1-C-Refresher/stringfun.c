#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here

int reverse_chars(char *, int, int);
int print_words(char *, int);

int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions

    // declaring variables
    char *inPointer = user_str;   
    char *outPointer = buff;      
    int count = 0;         
    int space = 0; 

    // processes each character until null 
    while (*inPointer != '\0') {
        if (*inPointer == ' ' || *inPointer == '\t') {

            if (!space) {
                *outPointer = ' ';
                outPointer++;
                count++;
                space = 1;

                if (count >= len) {
                    return -1;
                }
            }
        } else {

            *outPointer = *inPointer;
            outPointer++;
            count++;
            space = 0;


            if (count >= len) {
                return -1;
            }
        }
        inPointer++;


    }

    // fills the remaining parts of buffer with periods
    while (count < len) {
        *outPointer = '.';
        outPointer++;
        count++;
    }

    int i = 0;
    while ((i < len) && (buff[i] != '.')) {
        i++;
    }

    // returns number of processed chars from user string
    return i; //for now just so the code compiles. 
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}


// returns word count 
int count_words(char *buff, int len, int str_len){
    //YOU MUST IMPLEMENT

    if (str_len == 0) {
        return 0;
    }

    // declares variables
    int wCount = 0;
    int word = 0;
    char *pointer = buff;

    for (int i = 0; i < str_len; i++) {
        char c = *pointer;
        if (c == ' ') {
            word = 0;
        } 
        else {
            if (!word) {
                wCount++;
                word = 1;
            }
        }
        pointer++;
    }


    return wCount;
}

//reverses str_len, returns 0 if successful
int reverse_chars(char *buff, int str_len) {
    if (str_len <= 0) {
        return -1;
    }

    char *begin = buff;
    char *end = buff + (str_len - 1);

    // swapping
    while (begin < end) {

        char temp = *begin;
        *begin = *end;
        *end = temp;
        begin++;
        end--;
    }
    return 0;
}


int print_words(char *buff, int str_len) {

    if (str_len == 0) {
        return 0;
    }

    printf("Print Word\n");
    printf("----------\n");

    int wCount = 0;
    int word = 0;
    char *start = NULL;

    for (int i = 0; i < str_len; i++) {
        char c = *(buff + i);
        if (c == ' ') {
            if (word) {
                int wordLen = (buff + i) - start;
                wCount++;
                printf("%d. ", wCount);
                for (int j = 0; j < wordLen; j++) {
                    putchar(*(start + j));
                }
                printf(" (%d)\n", wordLen);
                word = 0;
            }
        }


        else {
            if (!word) {
                word = 1;
                start = (buff + i);
            }

        }
    }

    // closes out if false 
    if (word) {

        int i = str_len;
        int wordLen = (buff + i) - start;

        wCount++;
        printf("%d. ", wCount);
        
        for (int j = 0; j < wordLen; j++) {
            putchar(*(start + j));
        }

        printf(" (%d)\n", wordLen);
    }
    return wCount;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING

    /*
    
    This is safe because it checks if argc is greater than 2 or if the second argument doesn't contain 
    a hypen at the beginning, if so it calls usage and then exits. With this, we ensure that argv[1] 
    exists and isn't null meaning it has at least one character.
    
    */


    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING

    /*
    
    argv[0] is the program name, argv[1] is whatever option the user chooses to include
    , argv[2] is the user string. The if statement will fail if the user doesn't include 
    the necessary arguments, which then usage and exit will be called. 

    */


    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3

    buff = (char *) malloc(BUFFER_SZ);

    if (buff == NULL) {
        exit(99);
    }


    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options

        case 'r': {

            // reverses the characters
            rc = reverse_chars(buff, user_str_len);

            if (rc < 0) {
                printf("Error reversing string, rc = %d\n", rc);
                free(buff);
                exit(3);
            }

            printf("Reversed String: ");

            for (int i = 0; i < user_str_len; i++) {
                putchar(*(buff + i));
            }

            putchar('\n');
            break;
        }

        case 'w': {

            // prints out the words
            rc = print_words(buff, user_str_len);

            if (rc < 0) {

                printf("Error printing words, rc = %d\n", rc);

                free(buff);
                exit(3);
            }

            break;
        }



        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);

    free(buff);

    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE

            /*
            
            I think that its good practice because when it comes to larger programs you might
            not know precisely how large the memory area is from one pointer. So providing both
            the pointer and the length helps to avoid buffer overflow. 

            */
