#include "election.h"
//include any other headers you need here...
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 64
#define PART_N 3

state_t parseLine(const char * line) {
  //STEP 1: write me
  char * copyOfLine = malloc(BUFFER_SIZE * sizeof(*copyOfLine));
  memset(copyOfLine, '\0', BUFFER_SIZE * sizeof(*copyOfLine));
  strcpy(copyOfLine, line);
  const char * delim = ":";
  char * ptk = NULL;
  char * psv = NULL;
  if ((ptk = strtok_r(copyOfLine, delim, &psv)) == NULL) {
    free(copyOfLine);
    fprintf(stderr, "Cannot find a specific delimiter %s\n", delim);
    exit(EXIT_FAILURE);
  }
  size_t counter = 0;
  char rawSptData[PART_N][BUFFER_SIZE];
  for (int i = 0; i < PART_N; i++) {
    for (int j = 0; j < BUFFER_SIZE; j++) {
      rawSptData[i][j] = '\0';
    }
  }
  while (ptk != NULL) {
    strcpy(rawSptData[counter], ptk);
    ptk = strtok_r(NULL, delim, &psv);
    counter++;
  }
  if (counter != 3) {
    free(copyOfLine);
    fprintf(stderr, "Number of delimiters (%s) does not match\n", delim);
    exit(EXIT_FAILURE);
  }
  free(copyOfLine);
  state_t state;
  strcpy(state.name, rawSptData[0]);
  state.population = atol(rawSptData[1]);
  state.electoralVotes = atoi(rawSptData[2]);
  return state;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int ans = 0;
  for (size_t i = 0; i < nStates; i++) {
    if ((long double)voteCounts[i] / (long double)stateData[i].population > 0.5) {
      ans += stateData[i].electoralVotes;
    }
  }
  return ans;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  for (size_t i = 0; i < nStates; i++) {
    float voteRate = (float)((long double)voteCounts[i] / (long double)stateData[i].population);
    if (voteRate >= (0.5 - 0.005) && voteRate <= (0.5 + 0.005)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             100 * voteRate);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  //li: largestIndex
  //livr: largestInexVoteRate
  //vr: voteRate
  size_t li = 0;
  float livr = (float)((long double)voteCounts[li] / (long double)stateData[li].population);
  for (size_t i = 1; i < nStates; i++) {
    float vr = (float)((long double)voteCounts[i] / (long double)stateData[i].population);
    if (vr > livr) {
      li = i;
      livr = (float)((long double)voteCounts[li] / (long double)stateData[li].population);
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[li].name, 100 * livr);
}
