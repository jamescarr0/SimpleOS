/**
 * @file path_parser.h
 * @author James Carr
 * @brief Function prototypes for parsing and storing directory tokens.
 * @version 0.1
 * @date 05-04-2022
 * 
 * Parse a directory string, create tokens, and store in linked list.
 */

#ifndef SIMPLEOS_PATH_PARSER_H
#define SIMPLEOS_PATH_PARSER_H

#define PATHPARSER_MAX_BUF_SIZE 256
#define PATHPARSER_MAX_PATH_LEN 512
#define PATHPARSER_DRIVE_VALID_FORMAT ":/"

/* Linked List data structure for storing a parsed directory string */
typedef struct PathToken_s
{
    char *str;
    struct PathToken_s *next;
} PathToken;

typedef struct
{
    int drive;
    struct PathToken_s *next;
} PathRoot;

/**
 * @brief Parses and tokenizes a directory path string
 * 
 * @param path_root PathRoot data structure for storing tokens
 * @param path Directory string to be tokenized
 * @param cwd Curernt working directory string
 * @return int: 0 on success, < 0 on error.
 * 
 * Parses and tokenizes a directory path string using linked list data structure.
 */
int pathparser_parse(PathRoot *path_root, char *path, const char *cwd);

/**
 * @brief Free all memory allocated during generation of PathRoot & PathTokens
 * 
 * @param p The PathRoot used for storing the path.
 */
void pathparser_free(PathRoot *p);

#endif //SIMPLEOS_PATH_PARSER_H
