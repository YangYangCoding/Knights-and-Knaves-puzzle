solve.c is the solution code of this assignment, it is written by YangYang, please read the lisence before you download it or use it. There are some test files, you can test solve.c by using these test files.

test?.txt files are the files you are going to use to test,
expected_?.txt files are the output answers, you can look at your answers and compare yours with the expected_?.txt answers. 


Assignment

1 Aim of assignment and general description

The aim of the assignment is to analyse English sentences and solve logical puzzles. The assignment will make you practice the use of pointers, command line arguments, and dynamic memory allocation.
Raymond Smullyan has designed many puzzles involving Knights and Knaves. Knights always tell the truth, whereas Knaves always lie. We refer to Knights and Knaves as Sirs. A puzzle, which is a set of English sentences, involves a finite number of Sirs. Solving the puzzle means:
• determining the names of all Sirs involved in the puzzle;
• determining solutions to the puzzle, where a solution qualifies each Sir as either a Knight or a
Knave.
Some puzzles have no solution, others have a unique solution, and others have at least 2 solutions. The following is an example of a puzzle with a unique solution.
     One evening as you are out for a stroll, you walk by a doorway labeled no normals
     allowed.  Some people are talking inside.  Curious, you listen, and you hear
     Sir Paul who says:  "all of us are Knaves." "Exactly one of us is a Knight,"
     replies Sir Jenny.  As for Sir John, who is also inside, he just keeps quiet.
     Who is a Knight, and who is a Knave?
The Sirs involved in this puzzle are Sir Jenny, Sir John, and Sir Paul. The unique solution is given by Sir Jenny being a Knight, Sir John being a Knave, and Sir Paul being a Knave.

2 Detailed description 

2.1 Syntax of puzzles

A sentence starts with a capital letter and ends in a full stop, an exclamation mark, or a question mark, possibly followed by closing double quotes. Sir, Sirs, Sir names, Knight and Knave always start with a capital letter, and no other word inside a sentence is capitalised. A sentence in a puzzle contains at most one part enclosed between double quotes. When a sentence contains one part enclosed between double quotes, the part outside the double quotes contains a single occurrence of the form Sir Sir_Name, and what occurs between the double quotes is something said by Sir Sir_Name. A sentence that contains no part enclosed between double quotes might refer to a number of Sirs, always in the form Sir Sir_Name, or Sirs Sir_Name_1 and Sir_Name_2, or Sirs Sir_Name_1, Sir_Name_2, . . . and Sir_Name_n, where n ≥ 3, and Sir_Name_1, . . . , Sir_Name_n are pairwise distinct.
What is between double quotes is a sentence in one of the following forms, ending in either a comma, a full stop, an exclamation mark, or a question mark:

• At/at least one of Conjunction_of_Sirs/us is a Knight/Knave
• At/at most one of Conjunction_of_Sirs/us is a Knight/Knave
• Exactly/exactly one of Conjunction_of_Sirs/us is a Knight/Knave • All/all of us are Knights/Knaves
• I am a Knight/Knave
• Sir Sir_Name is a Knight/Knave
• Disjunction_of_Sirs is a Knight/Knave
• Conjunction_of_Sirs are Knights/Knaves
where:
• Disjunction_of_Sirs is in one of the following forms:
– Sir_1 or Sir_2
– Sir_1, Sir_2, ... or Sir_n (n ≥ 3)
• Conjunction_of_Sirs is in one of the following forms: – Sir_1 and Sir_2
– Sir_1, Sir_2, ... and Sir_n (n ≥ 3)
• Sir_1, . . . , Sir_n are pairwise distinct expressions of the form Sir Sir_Name or I.

2.2 Input and output of programs

Your program will accept the sentences that make up a puzzle as command line arguments. Practically, assuming that solve is the name of the executable file and the puzzle is stored in a file test.txt, your program will be run with the command
                                     solve $(cat test.txt)
No assumption should be made on the number of English sentences provided as input, nor on the length of a sentence, nor on the length of a Sir name, nor on the number of Sirs involved in the puzzle.
Your program should:
• output the Sirs involved in the puzzle in lexicographic order;
• output whether or not there is a solution, and in case there is one, whether the solution is unique;
• outputs the solution in case a unique solution exists, with all Sirs being qualified as either Knight or Knave in alphabetical order.


2.3 Sample outputs

Here are a few tests together with the expected outputs of your program for the two file tests given above. The output of your program should be EXACTLY in accordance with the following outputs, WITHOUT extra blank lines, etc. Outputs of your program will be matched against expected outputs LINE FOR LINE.
$ cat test1.txt
I have just seen Sirs Sanjay and Eleonore!
"I am a Knave," whispered Sir Eleonore.
Who is a Knight and who is a Knave?
$ solve $(cat test1.txt)
The Sirs are: Eleonore Sanjay
There is no solution.
$ cat test2.txt
I have just met Sirs Frank, Paul and Nina.
Sir Nina said: "I am a Knight," but I am not sure
if that is true. What do you think?
$ solve $(cat test2.txt)
The Sirs are: Frank Nina Paul
There are 8 solutions.
$ cat test3.txt
Yesterday, I visited Sirs Andrew and Nancy. I asked Sir Andrew
who he was, and he answered impatiently: "Sir Nancy and I
are Knaves!" Then I met Sir Bill who introduced me to his wife
and told me: "at least one of Sir Hilary
and I is a Knave." Should I trust them?
$ solve $(cat test3.txt)
The Sirs are: Andrew Bill Hilary Nancy
There is a unique solution:
Sir Andrew is a Knave.
Sir Bill is a Knight.
Sir Hilary is a Knave.
Sir Nancy is a Knight.

3 Assessment and submission 

3.1 Submission

The main() procedure of your program should be stored in a file called solve.c. Your program can contain other other .c and .h files. You are encouraged to make your program modular and split it into different files.
