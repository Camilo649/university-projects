/**
*  @file strfuncs.h
*  @brief Functions about strings
*/

#ifndef __STRFUNCS_H__
#define __STRFUNCS_H__

/**
* @brief Calculates the length of a string
* @param str A String
* @return The length of a string
*/
size_t string_length(const char *str);

/**
* @brief Removes all occurrences of a character from a string
* @param str A String
* @param c A character to remove from the string
* @return A new string in dynamic memory that is obtained by taking
* the characters of str that are different from the character c
*/
char *string_filter(const char *str, char c);


#endif