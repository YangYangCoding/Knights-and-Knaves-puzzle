/* Written by Yang Yang for COMP9021 Assignment_3. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define AT_LEAST_ONE_KNIGHT 0
#define AT_LEAST_ONE_KNAVE 1
#define AT_MOST_ONE_KNIGHT 2
#define AT_MOST_ONE_KNAVE 3
#define EXACTLY_ONE_KNIGHT 4
#define EXACTLY_ONE_KNAVE 5
#define ALL_ARE_KNIGHT 6
#define ALL_ARE_KNAVE 7
#define I_AM_KNIGHT 8
#define I_AM_KNAVE 9
#define SIR_IS_KNIGHT 10
#define SIR_IS_KNAVE 11
#define SIR_OR_SIR_IS_KNIGHT 12
#define SIR_OR_SIR_IS_KNAVE 13
#define SIR_AND_SIR_ARE_KNIGHT 14
#define SIR_AND_SIR_ARE_KNAVE 15


/* If is_truth is true, it means this sentence is true,otherwise this sentene is false. */
bool is_truth = true;
/* If this possible solution is a solution,then is_a_solution is true. */
bool is_a_solution = false;


int main(int argc, char **argv) {
    int i = 1; 
    /* Find how many sentences in this test file. */
    int nb_of_sentence = 0;
    /* Find how many sirs occur in this test file. */
    int nb_of_occurrence_of_sirs = 0;
    /* Record the nb of distinct sirs. */
    int nb_of_distinct_sirs = 1;
    /* Change all the sentences that end as ." or !" or ?" to be ". or "! or "? so we can count the nb of sentences easily. */ 
    while (i < argc) {
        if (argv[i][strlen(argv[i]) - 1] == '"' && argv[i][strlen(argv[i]) - 2] == '.') {
            argv[i][strlen(argv[i]) - 1] = '.';
            argv[i][strlen(argv[i]) - 2] = '"';
        }        
        if (argv[i][strlen(argv[i]) - 1] == '"' && argv[i][strlen(argv[i]) - 2] == '!') {
            argv[i][strlen(argv[i]) - 1] = '!';
            argv[i][strlen(argv[i]) - 2] = '"';
        }
        if (argv[i][strlen(argv[i]) - 1] == '"' && argv[i][strlen(argv[i]) - 2] == '?') {
            argv[i][strlen(argv[i]) - 1] = '?';
            argv[i][strlen(argv[i]) - 2] = '"';
        }
        ++i;    
    } 
    i = 1;
    /* Record the nb of sentences. */
    while (i < argc) {
        if (argv[i][strlen(argv[i]) - 1] == '.' ||
            argv[i][strlen(argv[i]) - 1] == '!' ||
            argv[i][strlen(argv[i]) - 1] == '?') {
            ++nb_of_sentence;
        }
        ++i;
    }
    i = 1;
    int end_of_sentence[nb_of_sentence];
    int m = 0;
    /* Record where these sentences end respectively. */
    while (i < argc && m < nb_of_sentence) {
        if (argv[i][strlen(argv[i]) - 1] == '.' ||
            argv[i][strlen(argv[i]) - 1] == '!' ||
            argv[i][strlen(argv[i]) - 1] == '?') {
                end_of_sentence[m] = i;
                ++m;
        }
        ++i;
    } 
    i = 1;
    m = 0;
    /* Find how many times Sirs occur in this file,we might count sirs repeatedly. */
    while (i < argc) {
        if (strcmp(argv[i], "Sir") == 0 || strcmp(argv[i], "\042Sir") == 0) {
            ++nb_of_occurrence_of_sirs;
        }
        if (strcmp(argv[i], "Sirs") == 0 || strcmp(argv[i], "\042Sirs") == 0) {
            m = 1;
            while (strcmp(argv[i + m], "and") != 0) {
                ++m;
            }
            nb_of_occurrence_of_sirs = nb_of_occurrence_of_sirs + m;
        }
        ++i;    
    }
    i = 1;
    m = 0;
    /* If there is no Sirs in file, then there should be no solution. */
    if (nb_of_occurrence_of_sirs == 0) {
        printf("The Sirs are:\n");
        printf("There is no solution.\n");
        return EXIT_SUCCESS;
    }
    /* Record where these Sirs occur in this file. */
    int occurrence_of_sir[nb_of_occurrence_of_sirs];
    while (i < argc && m < nb_of_occurrence_of_sirs) {
        if (strcmp(argv[i], "Sir") == 0 || strcmp(argv[i], "\042Sir") == 0) {
            occurrence_of_sir[m] = i + 1;
            ++m;
        }
        if (strcmp(argv[i], "Sirs") == 0 || strcmp(argv[i], "\042Sirs") == 0) {
            int n = 1;
            while (strcmp(argv[i + n], "and") != 0) {
                occurrence_of_sir[m] = i + n;
                ++n;
                ++m;
            }
            occurrence_of_sir[m] = i + n + 1; 
            ++m;     
        } 
        ++i;  
    }
    i = 1;
    m = 0;
    /* Delete quotes behind names. */
    for (int j = 0; j < nb_of_occurrence_of_sirs; ++j) {
         if (!isalpha(argv[occurrence_of_sir[j]][strlen(argv[occurrence_of_sir[j]]) - 1])) {
             argv[occurrence_of_sir[j]][strlen(argv[occurrence_of_sir[j]]) - 1] = '\0';
         }
    }
    /* Find how many distinct Sirs in this file.*/   
    while (m < (nb_of_occurrence_of_sirs - 1)) {
        bool is_distinct = true;
        i = nb_of_occurrence_of_sirs - 1;
        for (int j = 0; j < (nb_of_occurrence_of_sirs - 1 - m); ++j) {
            if (strcmp(argv[occurrence_of_sir[m]], argv[occurrence_of_sir[i]]) != 0) {
                --i;
            }
            else if (strcmp(argv[occurrence_of_sir[m]], argv[occurrence_of_sir[i]]) == 0) {
                is_distinct = false;
                break;
            }
        }
        if (is_distinct) {
            ++nb_of_distinct_sirs;
        }
        ++m;
    }
    i = 1;
    m = 0;
    /* Record where these distinct Sirs are in this file. */
    int sirs[nb_of_distinct_sirs];
    int num_sirs = 0;
    while (m < (nb_of_occurrence_of_sirs - 1)) {
        bool is_distinct = true;    
        i = nb_of_occurrence_of_sirs - 1;
        for (int j = 0; j < (nb_of_occurrence_of_sirs - 1 - m); ++j) {
            if (strcmp(argv[occurrence_of_sir[m]], argv[occurrence_of_sir[i]]) != 0) {
                --i;
            }
            else if (strcmp(argv[occurrence_of_sir[m]], argv[occurrence_of_sir[i]]) == 0) {
                is_distinct = false;
                break;
            }
        }
        if (is_distinct && num_sirs < nb_of_distinct_sirs) {
            sirs[num_sirs] = occurrence_of_sir[m];
            ++num_sirs;
        }
        ++m;
    }
    sirs[num_sirs] = occurrence_of_sir[nb_of_occurrence_of_sirs - 1];
    m = 0;
    i = 1;
    /* Output the Sirs involved in the puzzle in lexicographic order. */
    while (m < (nb_of_distinct_sirs - 1)) {
        int temp_sir_name = 0;
        for (int j = m; j < (nb_of_distinct_sirs - 1); ++j) {
            if (strcmp(argv[sirs[m]],argv[sirs[j + 1]]) > 0) {
                temp_sir_name = sirs[m];
                sirs[m] = sirs[j + 1];
                sirs[j + 1] = temp_sir_name;
            }
        }
        ++m;
    }
    m = 0;
    i = 1;
    /* Print Sirs. */
    printf("The Sirs are:");
    for (int j = 0; j < nb_of_distinct_sirs; ++j) {
        printf(" ");
        printf(argv[sirs[j]]);
    }
    printf("\n");
    /* Find out how many sentences have quotes. */
    bool found_quote = false;
    int nb_of_quotes_sentences = 0;
    while (i < argc) {    
        if (argv[i][0] == '"') {
            found_quote = true;
        }
        if (i == end_of_sentence[m]) {
            ++m;
            if (found_quote) {
                ++nb_of_quotes_sentences;
                found_quote = false;
            }
        }
        ++i;
    }
    m = 0;
    i = 1;  
    /* If there is no sentence with quotes, then the solutions will be pow(2, nb_of_distinct_sirs). */
    if (nb_of_quotes_sentences == 0) {
        int nb_sol = pow(2, nb_of_distinct_sirs);
        printf("There are %d solutions.\n", nb_sol);
        return EXIT_SUCCESS; 
    }
    /* Record where these quotes sentences begin and end,where quotes open and close in these sentences. */
    /* quotes_sentence[0/1/2```][(begin,end,open",close",talking sir)],As you see,[0/1/2```] means which quotes sentence we are recording*/
    /* now,and[(begin,end,open",close",talking sir)] means where this sentence begin,end and who is talking and where quotes open and close. */
    int quotes_sentence[nb_of_quotes_sentences][5];
    bool found_a_pair_of_quotes = false;
    int sentence_position = 0;
    /* Find out all information about quote sentences except talking sir.*/
    while (m < nb_of_quotes_sentences && i < argc) {
        if (argv[i][0] == '"') {
            quotes_sentence[m][2] = i;
        }
        else if (argv[i][strlen(argv[i]) - 2] == '"' ||
                 argv[i][strlen(argv[i]) - 1] == '"') {
            quotes_sentence[m][3] = i;
            found_a_pair_of_quotes = true;
        }
        if (i == end_of_sentence[sentence_position]) {
            if (found_a_pair_of_quotes) {
                if (sentence_position == 0) {
                    quotes_sentence[m][0] = 1;
                    quotes_sentence[m][1] = i;
                }
                else {
                    quotes_sentence[m][0] = end_of_sentence[sentence_position - 1] + 1; 
                    quotes_sentence[m][1] = i; 
                }    
                ++m;
                found_a_pair_of_quotes = false;
            }
            ++sentence_position;          
        }  
        ++i;
    }  
    m = 0;
    i = 1;
    /* Find out who is talking. */
    bool found_talking_sir = false;
    while (m < nb_of_quotes_sentences) {
        i = quotes_sentence[m][0];
        while (i < quotes_sentence[m][2]) {
            if (strcmp(argv[i], "Sir") == 0) {
                quotes_sentence[m][4] = i + 1;
                found_talking_sir = true;
            }
            ++i;
        }
        if (!found_talking_sir) {
            i = quotes_sentence[m][3] + 1;
        }
        else if (found_talking_sir) {
            ++m;
            found_talking_sir = false;
            continue;
        }
        while (i < quotes_sentence[m][1]) {
            if (strcmp(argv[i], "Sir") == 0) {
                quotes_sentence[m][4] = i + 1;
            }
            ++i;
        }  
        ++m; 
        found_talking_sir = false; 
    }
    m = 0;
    i = 1;
    /* Find out who is mentioned in every sentence with quotes.Use an array called quotes_sentence_information[nb_of_quotes_sentences][2 + nb_of_distinct_sirs]. */
    /* The struct of this array will be quotes_sentence_information[0/1/2```][(talking sir,what saying,who is mentioned(contains nb_of_distinct_sirs cells))]*/
    /* Find out all the information about quotes_sentence_information[][] except (what saying). */
    int quotes_sentence_information[nb_of_quotes_sentences][2 + nb_of_distinct_sirs];
    int talking_sir_position = 0;
    while (m < nb_of_quotes_sentences) {
        quotes_sentence_information[m][0] = quotes_sentence[m][4];
        i = quotes_sentence[m][2];
        for (int j = 2; j < nb_of_distinct_sirs + 2; ++j) {
            quotes_sentence_information[m][j] = 0;
        }
        for (int j = 0; j < nb_of_distinct_sirs; ++j) {
            if (strcmp(argv[quotes_sentence[m][4]], argv[sirs[j]]) == 0) {
                talking_sir_position = j + 2;    
            }
        }
        while (i <= quotes_sentence[m][3]) { 
            for (int j = 0; j < nb_of_distinct_sirs; ++j) {
                if (strcmp(argv[i], argv[sirs[j]]) == 0) {
                    quotes_sentence_information[m][j + 2] = 1;    
                }
            }
            if (strcmp(argv[i], "I") == 0 || strcmp(argv[i], "\042I") == 0) {
                quotes_sentence_information[m][talking_sir_position] = 1;   
            } 
            if (strcmp(argv[i], "us") == 0) {
                for (int j = 0; j < nb_of_distinct_sirs; ++j) {
                    quotes_sentence_information[m][j + 2] = 1;
                }
                break;   
            }
            ++i;            
        }
        ++m;
    } 
    m = 0;
    i = 1;
    /* Find out (what saying) for quotes_sentence_information[][]. */
    /* If is_knight is false,it means people who is mentioned is knave,otherwise he is knight. */
    bool is_knight = false;
    while (m < nb_of_quotes_sentences) {
        i = quotes_sentence[m][2];
        while (i <= quotes_sentence[m][3]) {
            if (strcmp(argv[i], "Knight") == 0 || strcmp(argv[i], "Knight,\042") == 0 || strcmp(argv[i], "Knight\042.") == 0 || strcmp(argv[i], "Knight\042!") == 0 || strcmp(argv[i], "Knight\042?") == 0 || strcmp(argv[i], "Knights") == 0 || strcmp(argv[i], "Knights,\042") == 0 || strcmp(argv[i], "Knights\042.") == 0 || strcmp(argv[i], "Knights\042!") == 0 || strcmp(argv[i], "Knights\042?") == 0) {
                is_knight = true;
            }
            else if (strcmp(argv[i], "Knave") == 0 || strcmp(argv[i], "Knave,\042") == 0 || strcmp(argv[i], "Knave\042.") == 0 || strcmp(argv[i], "Knave\042!") == 0 || strcmp(argv[i], "Knave\042?") == 0 || strcmp(argv[i], "Knaves") == 0 || strcmp(argv[i], "Knaves,\042") == 0 || strcmp(argv[i], "Knaves\042.") == 0 || strcmp(argv[i], "Knaves\042!") == 0 || strcmp(argv[i], "Knaves\042?") == 0) {
                is_knight = false;
            }
            ++i;
        } 
        i = quotes_sentence[m][2];   
        while (i <= quotes_sentence[m][3]) {
            /* at least one */
            if (strcmp(argv[i], "least") == 0 && strcmp(argv[i + 1], "one") == 0) {
                if (is_knight) {
                    quotes_sentence_information[m][1] = AT_LEAST_ONE_KNIGHT;
                    break;
                }
                if (!is_knight) {
                    quotes_sentence_information[m][1] = AT_LEAST_ONE_KNAVE;
                    break;
                }
            } 
            /* at most one */
            if (strcmp(argv[i], "most") == 0 && strcmp(argv[i + 1], "one") == 0) {
                if (is_knight) {
                    quotes_sentence_information[m][1] = AT_MOST_ONE_KNIGHT;
                    break;
                }
                if (!is_knight) {
                    quotes_sentence_information[m][1] = AT_MOST_ONE_KNAVE;
                    break;
                }
            }
            /* exactly one */
            if (strcmp(argv[i], "\042Exactly") == 0 && strcmp(argv[i + 1], "one") == 0 ||
                strcmp(argv[i], "exactly") == 0 && strcmp(argv[i + 1], "one") == 0 ||
                strcmp(argv[i], "Exactly") == 0 && strcmp(argv[i + 1], "one") == 0 ||
                strcmp(argv[i], "\042exactly") == 0 && strcmp(argv[i + 1], "one") == 0) {
                if (is_knight) {
                    quotes_sentence_information[m][1] = EXACTLY_ONE_KNIGHT;
                    break;
                }
                if (!is_knight) {
                    quotes_sentence_information[m][1] = EXACTLY_ONE_KNAVE;
                    break;
                }
            }
            /* all are */
            if (strcmp(argv[i], "\042all") == 0 || strcmp(argv[i], "all") == 0 || 
                strcmp(argv[i], "\042All") == 0 || strcmp(argv[i], "All") == 0) {
                if (is_knight) {
                    quotes_sentence_information[m][1] = ALL_ARE_KNIGHT;
                    break;
                }
                if (!is_knight) {
                    quotes_sentence_information[m][1] = ALL_ARE_KNAVE;
                    break;
                }
            }
            /* I am */
            if (strcmp(argv[i], "\042I") == 0 && strcmp(argv[i + 1], "am") == 0 || 
                strcmp(argv[i], "I") == 0 || strcmp(argv[i + 1], "am") == 0) {
                if (is_knight) {
                    quotes_sentence_information[m][1] = I_AM_KNIGHT;
                    break;
                }
                if (!is_knight) {
                    quotes_sentence_information[m][1] = I_AM_KNAVE;
                    break;
                }
            }
            /* Sir is a */
            if (strcmp(argv[i], "\042Sir") == 0 && strcmp(argv[i + 2], "is") == 0 || 
                strcmp(argv[i], "Sir") == 0 || strcmp(argv[i + 2], "is") == 0) {
                if (is_knight) {
                    quotes_sentence_information[m][1] = SIR_IS_KNIGHT;
                    break;
                }
                if (!is_knight) {
                    quotes_sentence_information[m][1] = SIR_IS_KNAVE;
                    break;
                }
            }
            /* Sir or Sir is */
            if (strcmp(argv[i], "or") == 0 && strcmp(argv[i + 2], "is") == 0 || 
                strcmp(argv[i], "or") == 0 || strcmp(argv[i + 3], "is") == 0) {
                if (is_knight) {
                    quotes_sentence_information[m][1] = SIR_OR_SIR_IS_KNIGHT;
                    break;
                }
                if (!is_knight) {
                    quotes_sentence_information[m][1] = SIR_OR_SIR_IS_KNAVE;
                    break;
                }
            }
            /* Sir and Sir are */
            if (strcmp(argv[i], "and") == 0 && strcmp(argv[i + 2], "is") == 0 || 
                strcmp(argv[i], "and") == 0 || strcmp(argv[i + 3], "is") == 0) {
                if (is_knight) {
                    quotes_sentence_information[m][1] = SIR_AND_SIR_ARE_KNIGHT;
                    break;
                }
                if (!is_knight) {
                    quotes_sentence_information[m][1] = SIR_AND_SIR_ARE_KNAVE;
                    break;
                }
            }
            ++i;    
        }
        ++m;    
    }
    m = 0;
    i = 1;

    /* Compare sentence with quotes with all possible solutions so that we know how many solutions. For instance, if there are */
    /* four Sirs like test3.txt in file,then all possible solution will be 0000,0001,0010,0011 ... 1111, totally 16 possible solutions.*/
    /* So if there are n Sirs,then possible solutions will be power(2, n). */   
    /* Record the unique solution. */
    int unique_sol[nb_of_distinct_sirs];
    /* Store the number of solutions. */
    int nb_of_sol = 0; 
    for (int j = 0; j < pow(2, nb_of_distinct_sirs); ++j) {
        int is_a_possible_solution = 0;
        /* If if_enter is true,it means we enter while(m < nb_of_quotes_sentences && quotes_sentence_information[m][1] == ?). */
        int pos_sol[nb_of_distinct_sirs];
        /* I transform intege (j == pos_sol_value) to be type of this: 0000 or 0001 or ... 1111(if there are four Sirs in file) and put */
        /* this new form into an array called possible_solution[],so that we can copy it to unique_sol[] easily. */
        for (int w = 0; w < nb_of_distinct_sirs; ++w) {
            if (j & 1 << (nb_of_distinct_sirs - 1 - w)) {
                pos_sol[w] = 1;
            }
            else {
                pos_sol[w] = 0;
            }
        }  
        m = 0;
        is_a_solution = false;
        while (m < nb_of_quotes_sentences) {         
            /* at least one knight */
            if (quotes_sentence_information[m][1] == AT_LEAST_ONE_KNIGHT) {   
                int if_has_one_or_more_knights = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 1) {
                        ++if_has_one_or_more_knights;
                    }
                } 
                if (if_has_one_or_more_knights >= 1) {
                    is_truth = true;
                }
                else if (if_has_one_or_more_knights < 1) {
                    is_truth = false;
                }      
            }
            /* at least one knave */
            else if (quotes_sentence_information[m][1] == AT_LEAST_ONE_KNAVE) {
                int if_has_one_or_more_knaves = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 0) {
                        ++if_has_one_or_more_knaves;
                    }
                } 
                if (if_has_one_or_more_knaves >= 1) {
                    is_truth = true;
                }
                else if (if_has_one_or_more_knaves < 1) {
                    is_truth = false;
                }
            }    
            /* at most one knight */
            else if (quotes_sentence_information[m][1] == AT_MOST_ONE_KNIGHT) {
                int if_has_one_or_none_knight = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 1) {
                        ++if_has_one_or_none_knight;
                    }
                } 
                if (if_has_one_or_none_knight <= 1) {
                    is_truth = true;
                }
                else if (if_has_one_or_none_knight > 1) {
                    is_truth = false;
                }
            }
            /* at most one knave */
            else if (quotes_sentence_information[m][1] == AT_MOST_ONE_KNAVE) {
                int if_has_one_or_none_knave = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 0) {
                        ++if_has_one_or_none_knave;
                    }
                } 
                if (if_has_one_or_none_knave <= 1) {
                    is_truth = true;
                }
                else if (if_has_one_or_none_knave > 1) {
                    is_truth = false;
                }
            }
            /* exactly one knight */
            else if (quotes_sentence_information[m][1] == EXACTLY_ONE_KNIGHT) {
                int if_has_one_knight = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 1) {
                        ++if_has_one_knight;
                    }
                } 
                if (if_has_one_knight == 1) {
                    is_truth = true;
                }
                else if (if_has_one_knight != 1) {
                    is_truth = false;
                }
           
            }
            /* exactly one knave */
            else if (quotes_sentence_information[m][1] == EXACTLY_ONE_KNAVE) {
                int if_has_one_knave = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 0) {
                        ++if_has_one_knave;
                    }
                } 
                if (if_has_one_knave == 1) {
                    is_truth = true;
                }
                else if (if_has_one_knave != 1) {
                    is_truth = false;
                }
            }
            /* all are knight */
            else if (quotes_sentence_information[m][1] == ALL_ARE_KNIGHT && m < nb_of_quotes_sentences) {
                int nb_of_mentioned_sirs_knight = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1) {
                        ++nb_of_mentioned_sirs_knight;
                    }
                }
                int nb_of_knights = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 1) {
                        ++nb_of_knights;
                    }
                } 
                if (nb_of_knights == nb_of_mentioned_sirs_knight) {
                    is_truth = true;
                }
                else if (nb_of_knights != nb_of_mentioned_sirs_knight) {
                    is_truth = false;
                }
            }
            /* all are knave */
            else if (quotes_sentence_information[m][1] == ALL_ARE_KNAVE) {
                int nb_of_mentioned_sirs_knave = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1) {
                        ++nb_of_mentioned_sirs_knave;
                    }
                }
                int nb_of_knaves = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 0) {
                        ++nb_of_knaves;
                    }  
                } 
                if (nb_of_knaves == nb_of_mentioned_sirs_knave) {
                    is_truth = true;
                }
                else if (nb_of_knaves != nb_of_mentioned_sirs_knave) {
                    is_truth = false;
                }   
            }
            /* I am knight */
            else if (quotes_sentence_information[m][1] == I_AM_KNIGHT) {
                /* All possible solutions are suitable for this case because if knight says he is a knight,then this knight speaks truth,so it is */
                /* a solution;if a knave says he is a knight,then this knave speaks liar,so it is a solution too. */
                ++is_a_possible_solution; 
            }
            /* I am knave */
            else if (quotes_sentence_information[m][1] == I_AM_KNAVE) {
                /* All possible solutions are not suitable for this case because if knight says he is a knave,then this knight speaks liar,*/
                /* so it is not a solution;if a knave says he is a knave,then this knave speaks truth,so it is not a solution either. */
                is_a_possible_solution = is_a_possible_solution;
            }
            /* Sir is knight */
            else if (quotes_sentence_information[m][1] == SIR_IS_KNIGHT) {
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 1) {
                        is_truth = true;
                    }
                    else if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 0) {
                        is_truth = false;
                    }
                }
            }
            /* Sir is knave */
            else if (quotes_sentence_information[m][1] == SIR_IS_KNAVE) {
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 0) {
                        is_truth = true;
                    }
                    else if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 1) {
                        is_truth = false;
                    }
                }
            }
            /* Sir or Sir is knight */
            else if (quotes_sentence_information[m][1] == SIR_OR_SIR_IS_KNIGHT) {
                int nb_of_knight = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 1) {
                        ++nb_of_knight;
                    }
                } 
                if (nb_of_knight > 0) {
                    is_truth = true;
                }
                else if (nb_of_knight == 0) {
                    is_truth = false;
                }
            }
            /* Sir or Sir is knave */
            else if (quotes_sentence_information[m][1] == SIR_OR_SIR_IS_KNAVE) {
                int nb_of_knave = 0;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 0) {
                        ++nb_of_knave;
                    }
                } 
                if (nb_of_knave > 0) {
                    is_truth = true;
                }
                else if (nb_of_knave == 0) {
                    is_truth = false;
                }
            }
            /* Sir and Sir are knight */
            else if (quotes_sentence_information[m][1] == SIR_AND_SIR_ARE_KNIGHT) {
                is_truth = true;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 0) {
                        is_truth = false;
                        break;
                    }
                } 
            }
            /* Sir and Sir are knave */
            else if (quotes_sentence_information[m][1] == SIR_AND_SIR_ARE_KNAVE) {
                is_truth = true;
                for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                    if (quotes_sentence_information[m][sir_order + 2] == 1 && pos_sol[sir_order] == 1) {
                        is_truth = false;
                        break;
                    } 
                } 
            }
            /* Check if the speaker is knave or knight,if knave speaks liar,then it is a solution,if knight speaks truth,then it is a solution. */
            for (int sir_order = 0; sir_order < nb_of_distinct_sirs; ++sir_order) {
                if (strcmp(argv[quotes_sentence_information[m][0]], argv[sirs[sir_order]]) == 0) {
                    if (quotes_sentence_information[m][1] != I_AM_KNIGHT && quotes_sentence_information[m][1] != I_AM_KNAVE) {
                        if ((pos_sol[sir_order] == 1 && is_truth) || (pos_sol[sir_order] == 0 && !is_truth)) {
                            ++is_a_possible_solution;
                        }
                    } 
                }
            }    
            ++m;
        }  
        if (is_a_possible_solution == nb_of_quotes_sentences) {
            is_a_solution = true;
        } 
        else if (is_a_possible_solution != nb_of_quotes_sentences) {
            is_a_solution = false;
        }   
        if (!is_a_solution) {      
            continue;
        }
        else if (is_a_solution) {
            ++nb_of_sol;
            for (int w = 0; w < nb_of_distinct_sirs; ++w) {
               unique_sol[w] = pos_sol[w];
            }
            continue;
        }
    }
    if (nb_of_sol == 0) {
        printf("There is no solution.\n");
    }
    else if (nb_of_sol == 1) {
        printf("There is a unique solution:\n");
        for (int j = 0; j < nb_of_distinct_sirs; ++j) {
            printf("Sir ");
            printf(argv[sirs[j]]);
            printf(" is a ");
            if (unique_sol[j] == 0) {
                printf("Knave.\n");
            }
            else if (unique_sol[j] == 1) {
                printf("Knight.\n");
            }
        }
    }
    else if (nb_of_sol > 1) {
        printf("There are %d solutions.\n", nb_of_sol);
    }
    return EXIT_SUCCESS;
}


    








