/*
 * File:   LZX.c
 * Author: Tyler Hayslett
 * Date:   02/09/2020
 * Description: This is a Lempel-Ziv coding test.
 * 
 * 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int encode(FILE *fp, int dictionary_order);
int decode(FILE *fp);
int * build_dictionary(int dictionary_order);

int main(int argc, char** argv) {
  
  // Parse arguments, make sure there are enough, check format 
  if (argc < 3){
    printf("Not enough input arguments\n");
    return 1;
  }
  else if ((strcmp(argv[1], "decode") != 0) && (strcmp(argv[1], "encode") != 0)){
    printf("Please specify either \"encoding\" or \"decoding\" as first argument\n");
    return 1;
  }
  
  int dictionary_order = 2;
  int temp;
  
  if (argc > 3){
    temp = atoi(argv[3]);
    if (temp >= 1){
      dictionary_order = temp;
      printf("Inital dictionary size specified to: %i\n", 2 << (temp - 1));
    }
    else {
      printf("Inital dictionary order cannot be: %i\n", temp);
      return 1;
    }
  }
  else {
    printf("Inital dictionary size defaulting to 2\n", temp);
  }
  
  
  FILE *fp;
  char* filename = argv[2];
  
  fp = fopen(filename, "r");
  if (fp == NULL){
    printf("Could not open file %s\n",filename);
    return 1;
  }
  
  fseek(fp, 0L, SEEK_END);
  int size_of_file = ftell(fp);
  rewind(fp);
  
  printf("The file specified is %i characters long\n", size_of_file);
  
  if (strcmp(argv[1], "encode") == 0) {
    int result_size = encode(fp, dictionary_order);
    printf("File encoded to size: %i\n", result_size);
    printf("Coding efficiency: %i\%\n", 100 * (result_size/size_of_file));
  }
  else {
    decode(fp);
  }
  
  return 0;
}





int encode(FILE *fp, int dictionary_order){
  
  int *dict = build_dictionary(dictionary_order);
  int num_entries = 2 << (dictionary_order - 1);
  FILE *write_fp = fopen("comressed.txt", "w+");
  
  // Get size of file
  fseek(fp, 0L, SEEK_END);
  int size_of_file = ftell(fp);
  rewind(fp);
  // Get number of symbols to pull from file
  int num_symbols = (size_of_file << 8) >> dictionary_order;
  
  int search_result = 0;
  
  for (int i = num_symbols; i > 0; i--){
    int next_sym = get_next_symbol();
    search_result = search_dictionary(dict, n, next_sym, num_entries);
    if (search_result != -1)
      n = search_result;
    }
    else {
      fprintf(write_fp, "%i\n", n);
      add_to_dictionary(n, next_sym);
      num_entries++;
      n = next_sym;
    }
  }
  
  fprintf(write_fp, "%i\n", n);
  
  return 0;
}

int decode(FILE *fp){


  return 0;
}











