#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#define __STDC_LIMIT_MACROS
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#define psvn2c_PSVN_API

#define HAVE_FWD_MOVE_PRUNING
#define HAVE_BWD_MOVES
#define HAVE_BWD_MOVE_PRUNING
#define HAVE_ABSTRACTION


/* number of variables in a state */
#define NUMVARS 48


typedef int8_t var_t;
#define PRI_VAR PRId8
#define SCN_VAR SCNd8

#define NUMDOMAINS 1
static var_t domain_sizes[ NUMDOMAINS ] = { 6 };
static const char *name_of_domain[ NUMDOMAINS ] = { "COLOUR" };
static int var_domains[ NUMVARS ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static const char *domain_0[ 6 ] = {"RED", "GREEN", "BLUE", "YELLOW", "ORANGE", "WHITE" };
static const char **domain_to_domain_names[ NUMDOMAINS ] = { domain_0 };
static const char **var_domain_names[ NUMVARS ] = { domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0 };

typedef struct {
 var_t vars[ NUMVARS ];
} state_t;

typedef int (*funcptr)( const state_t *, void * );
typedef void (*actfuncptr)( const state_t *, state_t * );

typedef struct {
 const state_t *my_state;
 funcptr my_funcptr;
} ruleid_iterator_t;

#define num_fwd_rules 18
#define num_bwd_rules 18
static const char *fwd_rule_name[ 18 ] = { "UCW", "U180", "UCCW", "FCW", "F180", "FCCW", "RCW", "R180", "RCCW", "BCW", "B180", "BCCW", "LCW", "L180", "LCCW", "DCW", "D180", "DCCW" };
#define get_fwd_rule_label( ruleid ) (fwd_rule_name[(ruleid)]) 
static const char *bwd_rule_name[ 18 ] = { "UCW", "U180", "UCCW", "FCW", "F180", "FCCW", "RCW", "R180", "RCCW", "BCW", "B180", "BCCW", "LCW", "L180", "LCCW", "DCW", "D180", "DCCW" };
#define get_bwd_rule_label( ruleid ) (bwd_rule_name[(ruleid)]) 
#define cost_of_cheapest_fwd_rule 1
#define cost_of_costliest_fwd_rule 1
#define get_fwd_rule_cost( ruleid ) 1
#define cost_of_cheapest_bwd_rule 1
#define cost_of_costliest_bwd_rule 1
#define get_bwd_rule_cost( ruleid ) 1

static int fwd_rule_label_sets[864] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47};

static int bwd_rule_label_sets[864] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47};

static int fwd_prune_table[ 342 ] = { 18, 36, 54, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 0, 0, 0, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 0, 0, 0, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 0, 0, 0, 234, 252, 270, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 0, 0, 0, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 0, 0, 0, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 0, 0, 0, 288, 306, 324, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 0, 0, 0, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 0, 0, 0, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 0, 0, 0 };

static void fwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 6 ];
  child_state->vars[ 1 ] = state->vars[ 7 ];
  child_state->vars[ 2 ] = state->vars[ 0 ];
  child_state->vars[ 3 ] = state->vars[ 1 ];
  child_state->vars[ 4 ] = state->vars[ 2 ];
  child_state->vars[ 5 ] = state->vars[ 3 ];
  child_state->vars[ 6 ] = state->vars[ 4 ];
  child_state->vars[ 7 ] = state->vars[ 5 ];
  child_state->vars[ 8 ] = state->vars[ 16 ];
  child_state->vars[ 9 ] = state->vars[ 17 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 23 ];
  child_state->vars[ 16 ] = state->vars[ 24 ];
  child_state->vars[ 17 ] = state->vars[ 25 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 31 ];
  child_state->vars[ 24 ] = state->vars[ 32 ];
  child_state->vars[ 25 ] = state->vars[ 33 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 39 ];
  child_state->vars[ 32 ] = state->vars[ 8 ];
  child_state->vars[ 33 ] = state->vars[ 9 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 15 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 4 ];
  child_state->vars[ 1 ] = state->vars[ 5 ];
  child_state->vars[ 2 ] = state->vars[ 6 ];
  child_state->vars[ 3 ] = state->vars[ 7 ];
  child_state->vars[ 4 ] = state->vars[ 0 ];
  child_state->vars[ 5 ] = state->vars[ 1 ];
  child_state->vars[ 6 ] = state->vars[ 2 ];
  child_state->vars[ 7 ] = state->vars[ 3 ];
  child_state->vars[ 8 ] = state->vars[ 24 ];
  child_state->vars[ 9 ] = state->vars[ 25 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 31 ];
  child_state->vars[ 16 ] = state->vars[ 32 ];
  child_state->vars[ 17 ] = state->vars[ 33 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 39 ];
  child_state->vars[ 24 ] = state->vars[ 8 ];
  child_state->vars[ 25 ] = state->vars[ 9 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 15 ];
  child_state->vars[ 32 ] = state->vars[ 16 ];
  child_state->vars[ 33 ] = state->vars[ 17 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 23 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 2 ];
  child_state->vars[ 1 ] = state->vars[ 3 ];
  child_state->vars[ 2 ] = state->vars[ 4 ];
  child_state->vars[ 3 ] = state->vars[ 5 ];
  child_state->vars[ 4 ] = state->vars[ 6 ];
  child_state->vars[ 5 ] = state->vars[ 7 ];
  child_state->vars[ 6 ] = state->vars[ 0 ];
  child_state->vars[ 7 ] = state->vars[ 1 ];
  child_state->vars[ 8 ] = state->vars[ 32 ];
  child_state->vars[ 9 ] = state->vars[ 33 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 39 ];
  child_state->vars[ 16 ] = state->vars[ 8 ];
  child_state->vars[ 17 ] = state->vars[ 9 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 15 ];
  child_state->vars[ 24 ] = state->vars[ 16 ];
  child_state->vars[ 25 ] = state->vars[ 17 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 23 ];
  child_state->vars[ 32 ] = state->vars[ 24 ];
  child_state->vars[ 33 ] = state->vars[ 25 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 31 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 33 ];
  child_state->vars[ 4 ] = state->vars[ 34 ];
  child_state->vars[ 5 ] = state->vars[ 35 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 14 ];
  child_state->vars[ 9 ] = state->vars[ 15 ];
  child_state->vars[ 10 ] = state->vars[ 8 ];
  child_state->vars[ 11 ] = state->vars[ 9 ];
  child_state->vars[ 12 ] = state->vars[ 10 ];
  child_state->vars[ 13 ] = state->vars[ 11 ];
  child_state->vars[ 14 ] = state->vars[ 12 ];
  child_state->vars[ 15 ] = state->vars[ 13 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 3 ];
  child_state->vars[ 22 ] = state->vars[ 4 ];
  child_state->vars[ 23 ] = state->vars[ 5 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 47 ];
  child_state->vars[ 34 ] = state->vars[ 40 ];
  child_state->vars[ 35 ] = state->vars[ 41 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 22 ];
  child_state->vars[ 41 ] = state->vars[ 23 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 21 ];
}

static void fwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 47 ];
  child_state->vars[ 4 ] = state->vars[ 40 ];
  child_state->vars[ 5 ] = state->vars[ 41 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 12 ];
  child_state->vars[ 9 ] = state->vars[ 13 ];
  child_state->vars[ 10 ] = state->vars[ 14 ];
  child_state->vars[ 11 ] = state->vars[ 15 ];
  child_state->vars[ 12 ] = state->vars[ 8 ];
  child_state->vars[ 13 ] = state->vars[ 9 ];
  child_state->vars[ 14 ] = state->vars[ 10 ];
  child_state->vars[ 15 ] = state->vars[ 11 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 33 ];
  child_state->vars[ 22 ] = state->vars[ 34 ];
  child_state->vars[ 23 ] = state->vars[ 35 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 21 ];
  child_state->vars[ 34 ] = state->vars[ 22 ];
  child_state->vars[ 35 ] = state->vars[ 23 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 4 ];
  child_state->vars[ 41 ] = state->vars[ 5 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 3 ];
}

static void fwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 21 ];
  child_state->vars[ 4 ] = state->vars[ 22 ];
  child_state->vars[ 5 ] = state->vars[ 23 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 10 ];
  child_state->vars[ 9 ] = state->vars[ 11 ];
  child_state->vars[ 10 ] = state->vars[ 12 ];
  child_state->vars[ 11 ] = state->vars[ 13 ];
  child_state->vars[ 12 ] = state->vars[ 14 ];
  child_state->vars[ 13 ] = state->vars[ 15 ];
  child_state->vars[ 14 ] = state->vars[ 8 ];
  child_state->vars[ 15 ] = state->vars[ 9 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 47 ];
  child_state->vars[ 22 ] = state->vars[ 40 ];
  child_state->vars[ 23 ] = state->vars[ 41 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 3 ];
  child_state->vars[ 34 ] = state->vars[ 4 ];
  child_state->vars[ 35 ] = state->vars[ 5 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 34 ];
  child_state->vars[ 41 ] = state->vars[ 35 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 33 ];
}

static void fwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 9 ];
  child_state->vars[ 2 ] = state->vars[ 10 ];
  child_state->vars[ 3 ] = state->vars[ 11 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 41 ];
  child_state->vars[ 10 ] = state->vars[ 42 ];
  child_state->vars[ 11 ] = state->vars[ 43 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 22 ];
  child_state->vars[ 17 ] = state->vars[ 23 ];
  child_state->vars[ 18 ] = state->vars[ 16 ];
  child_state->vars[ 19 ] = state->vars[ 17 ];
  child_state->vars[ 20 ] = state->vars[ 18 ];
  child_state->vars[ 21 ] = state->vars[ 19 ];
  child_state->vars[ 22 ] = state->vars[ 20 ];
  child_state->vars[ 23 ] = state->vars[ 21 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 1 ];
  child_state->vars[ 30 ] = state->vars[ 2 ];
  child_state->vars[ 31 ] = state->vars[ 3 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 29 ];
  child_state->vars[ 42 ] = state->vars[ 30 ];
  child_state->vars[ 43 ] = state->vars[ 31 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 41 ];
  child_state->vars[ 2 ] = state->vars[ 42 ];
  child_state->vars[ 3 ] = state->vars[ 43 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 29 ];
  child_state->vars[ 10 ] = state->vars[ 30 ];
  child_state->vars[ 11 ] = state->vars[ 31 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 20 ];
  child_state->vars[ 17 ] = state->vars[ 21 ];
  child_state->vars[ 18 ] = state->vars[ 22 ];
  child_state->vars[ 19 ] = state->vars[ 23 ];
  child_state->vars[ 20 ] = state->vars[ 16 ];
  child_state->vars[ 21 ] = state->vars[ 17 ];
  child_state->vars[ 22 ] = state->vars[ 18 ];
  child_state->vars[ 23 ] = state->vars[ 19 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 9 ];
  child_state->vars[ 30 ] = state->vars[ 10 ];
  child_state->vars[ 31 ] = state->vars[ 11 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 1 ];
  child_state->vars[ 42 ] = state->vars[ 2 ];
  child_state->vars[ 43 ] = state->vars[ 3 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 29 ];
  child_state->vars[ 2 ] = state->vars[ 30 ];
  child_state->vars[ 3 ] = state->vars[ 31 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 1 ];
  child_state->vars[ 10 ] = state->vars[ 2 ];
  child_state->vars[ 11 ] = state->vars[ 3 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 18 ];
  child_state->vars[ 17 ] = state->vars[ 19 ];
  child_state->vars[ 18 ] = state->vars[ 20 ];
  child_state->vars[ 19 ] = state->vars[ 21 ];
  child_state->vars[ 20 ] = state->vars[ 22 ];
  child_state->vars[ 21 ] = state->vars[ 23 ];
  child_state->vars[ 22 ] = state->vars[ 16 ];
  child_state->vars[ 23 ] = state->vars[ 17 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 41 ];
  child_state->vars[ 30 ] = state->vars[ 42 ];
  child_state->vars[ 31 ] = state->vars[ 43 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 9 ];
  child_state->vars[ 42 ] = state->vars[ 10 ];
  child_state->vars[ 43 ] = state->vars[ 11 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 38 ];
  child_state->vars[ 1 ] = state->vars[ 39 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 37 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 7 ];
  child_state->vars[ 18 ] = state->vars[ 0 ];
  child_state->vars[ 19 ] = state->vars[ 1 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 26 ];
  child_state->vars[ 25 ] = state->vars[ 27 ];
  child_state->vars[ 26 ] = state->vars[ 28 ];
  child_state->vars[ 27 ] = state->vars[ 29 ];
  child_state->vars[ 28 ] = state->vars[ 30 ];
  child_state->vars[ 29 ] = state->vars[ 31 ];
  child_state->vars[ 30 ] = state->vars[ 24 ];
  child_state->vars[ 31 ] = state->vars[ 25 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 43 ];
  child_state->vars[ 38 ] = state->vars[ 44 ];
  child_state->vars[ 39 ] = state->vars[ 45 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 17 ];
  child_state->vars[ 44 ] = state->vars[ 18 ];
  child_state->vars[ 45 ] = state->vars[ 19 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 44 ];
  child_state->vars[ 1 ] = state->vars[ 45 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 43 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 37 ];
  child_state->vars[ 18 ] = state->vars[ 38 ];
  child_state->vars[ 19 ] = state->vars[ 39 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 28 ];
  child_state->vars[ 25 ] = state->vars[ 29 ];
  child_state->vars[ 26 ] = state->vars[ 30 ];
  child_state->vars[ 27 ] = state->vars[ 31 ];
  child_state->vars[ 28 ] = state->vars[ 24 ];
  child_state->vars[ 29 ] = state->vars[ 25 ];
  child_state->vars[ 30 ] = state->vars[ 26 ];
  child_state->vars[ 31 ] = state->vars[ 27 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 17 ];
  child_state->vars[ 38 ] = state->vars[ 18 ];
  child_state->vars[ 39 ] = state->vars[ 19 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 7 ];
  child_state->vars[ 44 ] = state->vars[ 0 ];
  child_state->vars[ 45 ] = state->vars[ 1 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 18 ];
  child_state->vars[ 1 ] = state->vars[ 19 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 17 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 43 ];
  child_state->vars[ 18 ] = state->vars[ 44 ];
  child_state->vars[ 19 ] = state->vars[ 45 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 30 ];
  child_state->vars[ 25 ] = state->vars[ 31 ];
  child_state->vars[ 26 ] = state->vars[ 24 ];
  child_state->vars[ 27 ] = state->vars[ 25 ];
  child_state->vars[ 28 ] = state->vars[ 26 ];
  child_state->vars[ 29 ] = state->vars[ 27 ];
  child_state->vars[ 30 ] = state->vars[ 28 ];
  child_state->vars[ 31 ] = state->vars[ 29 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 7 ];
  child_state->vars[ 38 ] = state->vars[ 0 ];
  child_state->vars[ 39 ] = state->vars[ 1 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 37 ];
  child_state->vars[ 44 ] = state->vars[ 38 ];
  child_state->vars[ 45 ] = state->vars[ 39 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void fwdrule13( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 25 ];
  child_state->vars[ 6 ] = state->vars[ 26 ];
  child_state->vars[ 7 ] = state->vars[ 27 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 5 ];
  child_state->vars[ 14 ] = state->vars[ 6 ];
  child_state->vars[ 15 ] = state->vars[ 7 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 45 ];
  child_state->vars[ 26 ] = state->vars[ 46 ];
  child_state->vars[ 27 ] = state->vars[ 47 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 38 ];
  child_state->vars[ 33 ] = state->vars[ 39 ];
  child_state->vars[ 34 ] = state->vars[ 32 ];
  child_state->vars[ 35 ] = state->vars[ 33 ];
  child_state->vars[ 36 ] = state->vars[ 34 ];
  child_state->vars[ 37 ] = state->vars[ 35 ];
  child_state->vars[ 38 ] = state->vars[ 36 ];
  child_state->vars[ 39 ] = state->vars[ 37 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 13 ];
  child_state->vars[ 46 ] = state->vars[ 14 ];
  child_state->vars[ 47 ] = state->vars[ 15 ];
}

static void fwdrule14( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 45 ];
  child_state->vars[ 6 ] = state->vars[ 46 ];
  child_state->vars[ 7 ] = state->vars[ 47 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 25 ];
  child_state->vars[ 14 ] = state->vars[ 26 ];
  child_state->vars[ 15 ] = state->vars[ 27 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 13 ];
  child_state->vars[ 26 ] = state->vars[ 14 ];
  child_state->vars[ 27 ] = state->vars[ 15 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 36 ];
  child_state->vars[ 33 ] = state->vars[ 37 ];
  child_state->vars[ 34 ] = state->vars[ 38 ];
  child_state->vars[ 35 ] = state->vars[ 39 ];
  child_state->vars[ 36 ] = state->vars[ 32 ];
  child_state->vars[ 37 ] = state->vars[ 33 ];
  child_state->vars[ 38 ] = state->vars[ 34 ];
  child_state->vars[ 39 ] = state->vars[ 35 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 5 ];
  child_state->vars[ 46 ] = state->vars[ 6 ];
  child_state->vars[ 47 ] = state->vars[ 7 ];
}

static void fwdrule15( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 13 ];
  child_state->vars[ 6 ] = state->vars[ 14 ];
  child_state->vars[ 7 ] = state->vars[ 15 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 45 ];
  child_state->vars[ 14 ] = state->vars[ 46 ];
  child_state->vars[ 15 ] = state->vars[ 47 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 5 ];
  child_state->vars[ 26 ] = state->vars[ 6 ];
  child_state->vars[ 27 ] = state->vars[ 7 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 34 ];
  child_state->vars[ 33 ] = state->vars[ 35 ];
  child_state->vars[ 34 ] = state->vars[ 36 ];
  child_state->vars[ 35 ] = state->vars[ 37 ];
  child_state->vars[ 36 ] = state->vars[ 38 ];
  child_state->vars[ 37 ] = state->vars[ 39 ];
  child_state->vars[ 38 ] = state->vars[ 32 ];
  child_state->vars[ 39 ] = state->vars[ 33 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 25 ];
  child_state->vars[ 46 ] = state->vars[ 26 ];
  child_state->vars[ 47 ] = state->vars[ 27 ];
}

static void fwdrule16( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 35 ];
  child_state->vars[ 12 ] = state->vars[ 36 ];
  child_state->vars[ 13 ] = state->vars[ 37 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 11 ];
  child_state->vars[ 20 ] = state->vars[ 12 ];
  child_state->vars[ 21 ] = state->vars[ 13 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 19 ];
  child_state->vars[ 28 ] = state->vars[ 20 ];
  child_state->vars[ 29 ] = state->vars[ 21 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 27 ];
  child_state->vars[ 36 ] = state->vars[ 28 ];
  child_state->vars[ 37 ] = state->vars[ 29 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 46 ];
  child_state->vars[ 41 ] = state->vars[ 47 ];
  child_state->vars[ 42 ] = state->vars[ 40 ];
  child_state->vars[ 43 ] = state->vars[ 41 ];
  child_state->vars[ 44 ] = state->vars[ 42 ];
  child_state->vars[ 45 ] = state->vars[ 43 ];
  child_state->vars[ 46 ] = state->vars[ 44 ];
  child_state->vars[ 47 ] = state->vars[ 45 ];
}

static void fwdrule17( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 27 ];
  child_state->vars[ 12 ] = state->vars[ 28 ];
  child_state->vars[ 13 ] = state->vars[ 29 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 35 ];
  child_state->vars[ 20 ] = state->vars[ 36 ];
  child_state->vars[ 21 ] = state->vars[ 37 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 11 ];
  child_state->vars[ 28 ] = state->vars[ 12 ];
  child_state->vars[ 29 ] = state->vars[ 13 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 19 ];
  child_state->vars[ 36 ] = state->vars[ 20 ];
  child_state->vars[ 37 ] = state->vars[ 21 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 44 ];
  child_state->vars[ 41 ] = state->vars[ 45 ];
  child_state->vars[ 42 ] = state->vars[ 46 ];
  child_state->vars[ 43 ] = state->vars[ 47 ];
  child_state->vars[ 44 ] = state->vars[ 40 ];
  child_state->vars[ 45 ] = state->vars[ 41 ];
  child_state->vars[ 46 ] = state->vars[ 42 ];
  child_state->vars[ 47 ] = state->vars[ 43 ];
}

static void fwdrule18( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 19 ];
  child_state->vars[ 12 ] = state->vars[ 20 ];
  child_state->vars[ 13 ] = state->vars[ 21 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 27 ];
  child_state->vars[ 20 ] = state->vars[ 28 ];
  child_state->vars[ 21 ] = state->vars[ 29 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 35 ];
  child_state->vars[ 28 ] = state->vars[ 36 ];
  child_state->vars[ 29 ] = state->vars[ 37 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 11 ];
  child_state->vars[ 36 ] = state->vars[ 12 ];
  child_state->vars[ 37 ] = state->vars[ 13 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 42 ];
  child_state->vars[ 41 ] = state->vars[ 43 ];
  child_state->vars[ 42 ] = state->vars[ 44 ];
  child_state->vars[ 43 ] = state->vars[ 45 ];
  child_state->vars[ 44 ] = state->vars[ 46 ];
  child_state->vars[ 45 ] = state->vars[ 47 ];
  child_state->vars[ 46 ] = state->vars[ 40 ];
  child_state->vars[ 47 ] = state->vars[ 41 ];
}

static actfuncptr fwd_rules[ 18 ] = { fwdrule1, fwdrule2, fwdrule3, fwdrule4, fwdrule5, fwdrule6, fwdrule7, fwdrule8, fwdrule9, fwdrule10, fwdrule11, fwdrule12, fwdrule13, fwdrule14, fwdrule15, fwdrule16, fwdrule17, fwdrule18 };

static int fwdfn0_r17( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 17;
}

static int fwdfn0_r16( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r17;
  return 16;
}

static int fwdfn0_r15( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r16;
  return 15;
}

static int fwdfn0_r14( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r15;
  return 14;
}

static int fwdfn0_r13( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r14;
  return 13;
}

static int fwdfn0_r12( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r13;
  return 12;
}

static int fwdfn0_r11( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r12;
  return 11;
}

static int fwdfn0_r10( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r11;
  return 10;
}

static int fwdfn0_r9( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r10;
  return 9;
}

static int fwdfn0_r8( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r9;
  return 8;
}

static int fwdfn0_r7( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r8;
  return 7;
}

static int fwdfn0_r6( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r7;
  return 6;
}

static int fwdfn0_r5( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r6;
  return 5;
}

static int fwdfn0_r4( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r5;
  return 4;
}

static int fwdfn0_r3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r4;
  return 3;
}

static int fwdfn0_r2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r3;
  return 2;
}

static int fwdfn0_r1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r2;
  return 1;
}

static int fwdfn0_r0( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn0_r1;
  return 0;
}

static int bwd_prune_table[ 342 ] = { 18, 36, 54, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 0, 0, 0, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 0, 0, 0, 234, 252, 270, 288, 306, 324, 18, 36, 54, 0, 0, 0, 126, 144, 162, 0, 0, 0, 234, 252, 270, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 0, 0, 0, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 0, 0, 0, 288, 306, 324, 18, 36, 54, 72, 90, 108, 0, 0, 0, 180, 198, 216, 0, 0, 0, 288, 306, 324, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 0, 0, 0, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 0, 0, 0, 0, 0, 0, 72, 90, 108, 126, 144, 162, 180, 198, 216, 234, 252, 270, 0, 0, 0 };

static void bwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 2 ];
  child_state->vars[ 1 ] = state->vars[ 3 ];
  child_state->vars[ 2 ] = state->vars[ 4 ];
  child_state->vars[ 3 ] = state->vars[ 5 ];
  child_state->vars[ 4 ] = state->vars[ 6 ];
  child_state->vars[ 5 ] = state->vars[ 7 ];
  child_state->vars[ 6 ] = state->vars[ 0 ];
  child_state->vars[ 7 ] = state->vars[ 1 ];
  child_state->vars[ 8 ] = state->vars[ 32 ];
  child_state->vars[ 9 ] = state->vars[ 33 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 39 ];
  child_state->vars[ 16 ] = state->vars[ 8 ];
  child_state->vars[ 17 ] = state->vars[ 9 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 15 ];
  child_state->vars[ 24 ] = state->vars[ 16 ];
  child_state->vars[ 25 ] = state->vars[ 17 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 23 ];
  child_state->vars[ 32 ] = state->vars[ 24 ];
  child_state->vars[ 33 ] = state->vars[ 25 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 31 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 4 ];
  child_state->vars[ 1 ] = state->vars[ 5 ];
  child_state->vars[ 2 ] = state->vars[ 6 ];
  child_state->vars[ 3 ] = state->vars[ 7 ];
  child_state->vars[ 4 ] = state->vars[ 0 ];
  child_state->vars[ 5 ] = state->vars[ 1 ];
  child_state->vars[ 6 ] = state->vars[ 2 ];
  child_state->vars[ 7 ] = state->vars[ 3 ];
  child_state->vars[ 8 ] = state->vars[ 24 ];
  child_state->vars[ 9 ] = state->vars[ 25 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 31 ];
  child_state->vars[ 16 ] = state->vars[ 32 ];
  child_state->vars[ 17 ] = state->vars[ 33 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 39 ];
  child_state->vars[ 24 ] = state->vars[ 8 ];
  child_state->vars[ 25 ] = state->vars[ 9 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 15 ];
  child_state->vars[ 32 ] = state->vars[ 16 ];
  child_state->vars[ 33 ] = state->vars[ 17 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 23 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 6 ];
  child_state->vars[ 1 ] = state->vars[ 7 ];
  child_state->vars[ 2 ] = state->vars[ 0 ];
  child_state->vars[ 3 ] = state->vars[ 1 ];
  child_state->vars[ 4 ] = state->vars[ 2 ];
  child_state->vars[ 5 ] = state->vars[ 3 ];
  child_state->vars[ 6 ] = state->vars[ 4 ];
  child_state->vars[ 7 ] = state->vars[ 5 ];
  child_state->vars[ 8 ] = state->vars[ 16 ];
  child_state->vars[ 9 ] = state->vars[ 17 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 23 ];
  child_state->vars[ 16 ] = state->vars[ 24 ];
  child_state->vars[ 17 ] = state->vars[ 25 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 31 ];
  child_state->vars[ 24 ] = state->vars[ 32 ];
  child_state->vars[ 25 ] = state->vars[ 33 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 39 ];
  child_state->vars[ 32 ] = state->vars[ 8 ];
  child_state->vars[ 33 ] = state->vars[ 9 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 15 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 21 ];
  child_state->vars[ 4 ] = state->vars[ 22 ];
  child_state->vars[ 5 ] = state->vars[ 23 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 10 ];
  child_state->vars[ 9 ] = state->vars[ 11 ];
  child_state->vars[ 10 ] = state->vars[ 12 ];
  child_state->vars[ 11 ] = state->vars[ 13 ];
  child_state->vars[ 12 ] = state->vars[ 14 ];
  child_state->vars[ 13 ] = state->vars[ 15 ];
  child_state->vars[ 14 ] = state->vars[ 8 ];
  child_state->vars[ 15 ] = state->vars[ 9 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 47 ];
  child_state->vars[ 22 ] = state->vars[ 40 ];
  child_state->vars[ 23 ] = state->vars[ 41 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 3 ];
  child_state->vars[ 34 ] = state->vars[ 4 ];
  child_state->vars[ 35 ] = state->vars[ 5 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 34 ];
  child_state->vars[ 41 ] = state->vars[ 35 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 33 ];
}

static void bwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 47 ];
  child_state->vars[ 4 ] = state->vars[ 40 ];
  child_state->vars[ 5 ] = state->vars[ 41 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 12 ];
  child_state->vars[ 9 ] = state->vars[ 13 ];
  child_state->vars[ 10 ] = state->vars[ 14 ];
  child_state->vars[ 11 ] = state->vars[ 15 ];
  child_state->vars[ 12 ] = state->vars[ 8 ];
  child_state->vars[ 13 ] = state->vars[ 9 ];
  child_state->vars[ 14 ] = state->vars[ 10 ];
  child_state->vars[ 15 ] = state->vars[ 11 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 33 ];
  child_state->vars[ 22 ] = state->vars[ 34 ];
  child_state->vars[ 23 ] = state->vars[ 35 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 21 ];
  child_state->vars[ 34 ] = state->vars[ 22 ];
  child_state->vars[ 35 ] = state->vars[ 23 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 4 ];
  child_state->vars[ 41 ] = state->vars[ 5 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 3 ];
}

static void bwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 33 ];
  child_state->vars[ 4 ] = state->vars[ 34 ];
  child_state->vars[ 5 ] = state->vars[ 35 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 14 ];
  child_state->vars[ 9 ] = state->vars[ 15 ];
  child_state->vars[ 10 ] = state->vars[ 8 ];
  child_state->vars[ 11 ] = state->vars[ 9 ];
  child_state->vars[ 12 ] = state->vars[ 10 ];
  child_state->vars[ 13 ] = state->vars[ 11 ];
  child_state->vars[ 14 ] = state->vars[ 12 ];
  child_state->vars[ 15 ] = state->vars[ 13 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 3 ];
  child_state->vars[ 22 ] = state->vars[ 4 ];
  child_state->vars[ 23 ] = state->vars[ 5 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 47 ];
  child_state->vars[ 34 ] = state->vars[ 40 ];
  child_state->vars[ 35 ] = state->vars[ 41 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 22 ];
  child_state->vars[ 41 ] = state->vars[ 23 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 21 ];
}

static void bwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 29 ];
  child_state->vars[ 2 ] = state->vars[ 30 ];
  child_state->vars[ 3 ] = state->vars[ 31 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 1 ];
  child_state->vars[ 10 ] = state->vars[ 2 ];
  child_state->vars[ 11 ] = state->vars[ 3 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 18 ];
  child_state->vars[ 17 ] = state->vars[ 19 ];
  child_state->vars[ 18 ] = state->vars[ 20 ];
  child_state->vars[ 19 ] = state->vars[ 21 ];
  child_state->vars[ 20 ] = state->vars[ 22 ];
  child_state->vars[ 21 ] = state->vars[ 23 ];
  child_state->vars[ 22 ] = state->vars[ 16 ];
  child_state->vars[ 23 ] = state->vars[ 17 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 41 ];
  child_state->vars[ 30 ] = state->vars[ 42 ];
  child_state->vars[ 31 ] = state->vars[ 43 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 9 ];
  child_state->vars[ 42 ] = state->vars[ 10 ];
  child_state->vars[ 43 ] = state->vars[ 11 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 41 ];
  child_state->vars[ 2 ] = state->vars[ 42 ];
  child_state->vars[ 3 ] = state->vars[ 43 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 29 ];
  child_state->vars[ 10 ] = state->vars[ 30 ];
  child_state->vars[ 11 ] = state->vars[ 31 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 20 ];
  child_state->vars[ 17 ] = state->vars[ 21 ];
  child_state->vars[ 18 ] = state->vars[ 22 ];
  child_state->vars[ 19 ] = state->vars[ 23 ];
  child_state->vars[ 20 ] = state->vars[ 16 ];
  child_state->vars[ 21 ] = state->vars[ 17 ];
  child_state->vars[ 22 ] = state->vars[ 18 ];
  child_state->vars[ 23 ] = state->vars[ 19 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 9 ];
  child_state->vars[ 30 ] = state->vars[ 10 ];
  child_state->vars[ 31 ] = state->vars[ 11 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 1 ];
  child_state->vars[ 42 ] = state->vars[ 2 ];
  child_state->vars[ 43 ] = state->vars[ 3 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 9 ];
  child_state->vars[ 2 ] = state->vars[ 10 ];
  child_state->vars[ 3 ] = state->vars[ 11 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 41 ];
  child_state->vars[ 10 ] = state->vars[ 42 ];
  child_state->vars[ 11 ] = state->vars[ 43 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 22 ];
  child_state->vars[ 17 ] = state->vars[ 23 ];
  child_state->vars[ 18 ] = state->vars[ 16 ];
  child_state->vars[ 19 ] = state->vars[ 17 ];
  child_state->vars[ 20 ] = state->vars[ 18 ];
  child_state->vars[ 21 ] = state->vars[ 19 ];
  child_state->vars[ 22 ] = state->vars[ 20 ];
  child_state->vars[ 23 ] = state->vars[ 21 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 27 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 1 ];
  child_state->vars[ 30 ] = state->vars[ 2 ];
  child_state->vars[ 31 ] = state->vars[ 3 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 37 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 29 ];
  child_state->vars[ 42 ] = state->vars[ 30 ];
  child_state->vars[ 43 ] = state->vars[ 31 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 45 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 18 ];
  child_state->vars[ 1 ] = state->vars[ 19 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 17 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 43 ];
  child_state->vars[ 18 ] = state->vars[ 44 ];
  child_state->vars[ 19 ] = state->vars[ 45 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 30 ];
  child_state->vars[ 25 ] = state->vars[ 31 ];
  child_state->vars[ 26 ] = state->vars[ 24 ];
  child_state->vars[ 27 ] = state->vars[ 25 ];
  child_state->vars[ 28 ] = state->vars[ 26 ];
  child_state->vars[ 29 ] = state->vars[ 27 ];
  child_state->vars[ 30 ] = state->vars[ 28 ];
  child_state->vars[ 31 ] = state->vars[ 29 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 7 ];
  child_state->vars[ 38 ] = state->vars[ 0 ];
  child_state->vars[ 39 ] = state->vars[ 1 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 37 ];
  child_state->vars[ 44 ] = state->vars[ 38 ];
  child_state->vars[ 45 ] = state->vars[ 39 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 44 ];
  child_state->vars[ 1 ] = state->vars[ 45 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 43 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 37 ];
  child_state->vars[ 18 ] = state->vars[ 38 ];
  child_state->vars[ 19 ] = state->vars[ 39 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 28 ];
  child_state->vars[ 25 ] = state->vars[ 29 ];
  child_state->vars[ 26 ] = state->vars[ 30 ];
  child_state->vars[ 27 ] = state->vars[ 31 ];
  child_state->vars[ 28 ] = state->vars[ 24 ];
  child_state->vars[ 29 ] = state->vars[ 25 ];
  child_state->vars[ 30 ] = state->vars[ 26 ];
  child_state->vars[ 31 ] = state->vars[ 27 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 17 ];
  child_state->vars[ 38 ] = state->vars[ 18 ];
  child_state->vars[ 39 ] = state->vars[ 19 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 7 ];
  child_state->vars[ 44 ] = state->vars[ 0 ];
  child_state->vars[ 45 ] = state->vars[ 1 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 38 ];
  child_state->vars[ 1 ] = state->vars[ 39 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 37 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 7 ];
  child_state->vars[ 18 ] = state->vars[ 0 ];
  child_state->vars[ 19 ] = state->vars[ 1 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 26 ];
  child_state->vars[ 25 ] = state->vars[ 27 ];
  child_state->vars[ 26 ] = state->vars[ 28 ];
  child_state->vars[ 27 ] = state->vars[ 29 ];
  child_state->vars[ 28 ] = state->vars[ 30 ];
  child_state->vars[ 29 ] = state->vars[ 31 ];
  child_state->vars[ 30 ] = state->vars[ 24 ];
  child_state->vars[ 31 ] = state->vars[ 25 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 35 ];
  child_state->vars[ 36 ] = state->vars[ 36 ];
  child_state->vars[ 37 ] = state->vars[ 43 ];
  child_state->vars[ 38 ] = state->vars[ 44 ];
  child_state->vars[ 39 ] = state->vars[ 45 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 17 ];
  child_state->vars[ 44 ] = state->vars[ 18 ];
  child_state->vars[ 45 ] = state->vars[ 19 ];
  child_state->vars[ 46 ] = state->vars[ 46 ];
  child_state->vars[ 47 ] = state->vars[ 47 ];
}

static void bwdrule13( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 13 ];
  child_state->vars[ 6 ] = state->vars[ 14 ];
  child_state->vars[ 7 ] = state->vars[ 15 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 45 ];
  child_state->vars[ 14 ] = state->vars[ 46 ];
  child_state->vars[ 15 ] = state->vars[ 47 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 5 ];
  child_state->vars[ 26 ] = state->vars[ 6 ];
  child_state->vars[ 27 ] = state->vars[ 7 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 34 ];
  child_state->vars[ 33 ] = state->vars[ 35 ];
  child_state->vars[ 34 ] = state->vars[ 36 ];
  child_state->vars[ 35 ] = state->vars[ 37 ];
  child_state->vars[ 36 ] = state->vars[ 38 ];
  child_state->vars[ 37 ] = state->vars[ 39 ];
  child_state->vars[ 38 ] = state->vars[ 32 ];
  child_state->vars[ 39 ] = state->vars[ 33 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 25 ];
  child_state->vars[ 46 ] = state->vars[ 26 ];
  child_state->vars[ 47 ] = state->vars[ 27 ];
}

static void bwdrule14( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 45 ];
  child_state->vars[ 6 ] = state->vars[ 46 ];
  child_state->vars[ 7 ] = state->vars[ 47 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 25 ];
  child_state->vars[ 14 ] = state->vars[ 26 ];
  child_state->vars[ 15 ] = state->vars[ 27 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 13 ];
  child_state->vars[ 26 ] = state->vars[ 14 ];
  child_state->vars[ 27 ] = state->vars[ 15 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 36 ];
  child_state->vars[ 33 ] = state->vars[ 37 ];
  child_state->vars[ 34 ] = state->vars[ 38 ];
  child_state->vars[ 35 ] = state->vars[ 39 ];
  child_state->vars[ 36 ] = state->vars[ 32 ];
  child_state->vars[ 37 ] = state->vars[ 33 ];
  child_state->vars[ 38 ] = state->vars[ 34 ];
  child_state->vars[ 39 ] = state->vars[ 35 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 5 ];
  child_state->vars[ 46 ] = state->vars[ 6 ];
  child_state->vars[ 47 ] = state->vars[ 7 ];
}

static void bwdrule15( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 25 ];
  child_state->vars[ 6 ] = state->vars[ 26 ];
  child_state->vars[ 7 ] = state->vars[ 27 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 5 ];
  child_state->vars[ 14 ] = state->vars[ 6 ];
  child_state->vars[ 15 ] = state->vars[ 7 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 19 ];
  child_state->vars[ 20 ] = state->vars[ 20 ];
  child_state->vars[ 21 ] = state->vars[ 21 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 45 ];
  child_state->vars[ 26 ] = state->vars[ 46 ];
  child_state->vars[ 27 ] = state->vars[ 47 ];
  child_state->vars[ 28 ] = state->vars[ 28 ];
  child_state->vars[ 29 ] = state->vars[ 29 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 38 ];
  child_state->vars[ 33 ] = state->vars[ 39 ];
  child_state->vars[ 34 ] = state->vars[ 32 ];
  child_state->vars[ 35 ] = state->vars[ 33 ];
  child_state->vars[ 36 ] = state->vars[ 34 ];
  child_state->vars[ 37 ] = state->vars[ 35 ];
  child_state->vars[ 38 ] = state->vars[ 36 ];
  child_state->vars[ 39 ] = state->vars[ 37 ];
  child_state->vars[ 40 ] = state->vars[ 40 ];
  child_state->vars[ 41 ] = state->vars[ 41 ];
  child_state->vars[ 42 ] = state->vars[ 42 ];
  child_state->vars[ 43 ] = state->vars[ 43 ];
  child_state->vars[ 44 ] = state->vars[ 44 ];
  child_state->vars[ 45 ] = state->vars[ 13 ];
  child_state->vars[ 46 ] = state->vars[ 14 ];
  child_state->vars[ 47 ] = state->vars[ 15 ];
}

static void bwdrule16( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 19 ];
  child_state->vars[ 12 ] = state->vars[ 20 ];
  child_state->vars[ 13 ] = state->vars[ 21 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 27 ];
  child_state->vars[ 20 ] = state->vars[ 28 ];
  child_state->vars[ 21 ] = state->vars[ 29 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 35 ];
  child_state->vars[ 28 ] = state->vars[ 36 ];
  child_state->vars[ 29 ] = state->vars[ 37 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 11 ];
  child_state->vars[ 36 ] = state->vars[ 12 ];
  child_state->vars[ 37 ] = state->vars[ 13 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 42 ];
  child_state->vars[ 41 ] = state->vars[ 43 ];
  child_state->vars[ 42 ] = state->vars[ 44 ];
  child_state->vars[ 43 ] = state->vars[ 45 ];
  child_state->vars[ 44 ] = state->vars[ 46 ];
  child_state->vars[ 45 ] = state->vars[ 47 ];
  child_state->vars[ 46 ] = state->vars[ 40 ];
  child_state->vars[ 47 ] = state->vars[ 41 ];
}

static void bwdrule17( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 27 ];
  child_state->vars[ 12 ] = state->vars[ 28 ];
  child_state->vars[ 13 ] = state->vars[ 29 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 35 ];
  child_state->vars[ 20 ] = state->vars[ 36 ];
  child_state->vars[ 21 ] = state->vars[ 37 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 11 ];
  child_state->vars[ 28 ] = state->vars[ 12 ];
  child_state->vars[ 29 ] = state->vars[ 13 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 19 ];
  child_state->vars[ 36 ] = state->vars[ 20 ];
  child_state->vars[ 37 ] = state->vars[ 21 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 44 ];
  child_state->vars[ 41 ] = state->vars[ 45 ];
  child_state->vars[ 42 ] = state->vars[ 46 ];
  child_state->vars[ 43 ] = state->vars[ 47 ];
  child_state->vars[ 44 ] = state->vars[ 40 ];
  child_state->vars[ 45 ] = state->vars[ 41 ];
  child_state->vars[ 46 ] = state->vars[ 42 ];
  child_state->vars[ 47 ] = state->vars[ 43 ];
}

static void bwdrule18( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 35 ];
  child_state->vars[ 12 ] = state->vars[ 36 ];
  child_state->vars[ 13 ] = state->vars[ 37 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
  child_state->vars[ 16 ] = state->vars[ 16 ];
  child_state->vars[ 17 ] = state->vars[ 17 ];
  child_state->vars[ 18 ] = state->vars[ 18 ];
  child_state->vars[ 19 ] = state->vars[ 11 ];
  child_state->vars[ 20 ] = state->vars[ 12 ];
  child_state->vars[ 21 ] = state->vars[ 13 ];
  child_state->vars[ 22 ] = state->vars[ 22 ];
  child_state->vars[ 23 ] = state->vars[ 23 ];
  child_state->vars[ 24 ] = state->vars[ 24 ];
  child_state->vars[ 25 ] = state->vars[ 25 ];
  child_state->vars[ 26 ] = state->vars[ 26 ];
  child_state->vars[ 27 ] = state->vars[ 19 ];
  child_state->vars[ 28 ] = state->vars[ 20 ];
  child_state->vars[ 29 ] = state->vars[ 21 ];
  child_state->vars[ 30 ] = state->vars[ 30 ];
  child_state->vars[ 31 ] = state->vars[ 31 ];
  child_state->vars[ 32 ] = state->vars[ 32 ];
  child_state->vars[ 33 ] = state->vars[ 33 ];
  child_state->vars[ 34 ] = state->vars[ 34 ];
  child_state->vars[ 35 ] = state->vars[ 27 ];
  child_state->vars[ 36 ] = state->vars[ 28 ];
  child_state->vars[ 37 ] = state->vars[ 29 ];
  child_state->vars[ 38 ] = state->vars[ 38 ];
  child_state->vars[ 39 ] = state->vars[ 39 ];
  child_state->vars[ 40 ] = state->vars[ 46 ];
  child_state->vars[ 41 ] = state->vars[ 47 ];
  child_state->vars[ 42 ] = state->vars[ 40 ];
  child_state->vars[ 43 ] = state->vars[ 41 ];
  child_state->vars[ 44 ] = state->vars[ 42 ];
  child_state->vars[ 45 ] = state->vars[ 43 ];
  child_state->vars[ 46 ] = state->vars[ 44 ];
  child_state->vars[ 47 ] = state->vars[ 45 ];
}

static actfuncptr bwd_rules[ 18 ] = { bwdrule1, bwdrule2, bwdrule3, bwdrule4, bwdrule5, bwdrule6, bwdrule7, bwdrule8, bwdrule9, bwdrule10, bwdrule11, bwdrule12, bwdrule13, bwdrule14, bwdrule15, bwdrule16, bwdrule17, bwdrule18 };

static int bwdfn0_r17( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 17;
}

static int bwdfn0_r16( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r17;
  return 16;
}

static int bwdfn0_r15( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r16;
  return 15;
}

static int bwdfn0_r14( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r15;
  return 14;
}

static int bwdfn0_r13( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r14;
  return 13;
}

static int bwdfn0_r12( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r13;
  return 12;
}

static int bwdfn0_r11( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r12;
  return 11;
}

static int bwdfn0_r10( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r11;
  return 10;
}

static int bwdfn0_r9( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r10;
  return 9;
}

static int bwdfn0_r8( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r9;
  return 8;
}

static int bwdfn0_r7( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r8;
  return 7;
}

static int bwdfn0_r6( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r7;
  return 6;
}

static int bwdfn0_r5( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r6;
  return 5;
}

static int bwdfn0_r4( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r5;
  return 4;
}

static int bwdfn0_r3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r4;
  return 3;
}

static int bwdfn0_r2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r3;
  return 2;
}

static int bwdfn0_r1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r2;
  return 1;
}

static int bwdfn0_r0( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn0_r1;
  return 0;
}


#define init_history 0

#define max_fwd_children 18

/* NOTE: FOR ALL OF THE MOVE ITERATOR DEFINITIONS funcptr
   MUST BE A VARIABLE. */

/* initialise a forward move iterator */
#define init_fwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = fwdfn0_r0 ; \
  (*ruleid_iter).my_state = state; \
}

/* use iterator to generate next applicable rule to apply 
   returns rule to use, -1 if there are no more rules to apply */
#define next_ruleid( ruleid_iter ) (((*ruleid_iter).my_funcptr)?((*ruleid_iter).my_funcptr)((*ruleid_iter).my_state,&((*ruleid_iter).my_funcptr)):-1)

/* apply a rule to a state */
#define apply_fwd_rule( rule, state, result ) fwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define fwd_rule_valid_for_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_fwd_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])


static const int bw_max_children = 18;
#define max_bwd_children 18

/* initialise a backwards move iterator */
#define init_bwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = bwdfn0_r0 ; \
  (*ruleid_iter).my_state = state; \
}

/* apply a rule to a state */
#define apply_bwd_rule( rule, state, result ) bwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define bwd_rule_valid_for_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_bwd_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])


/* returns 1 if state is a goal state, 0 otherwise */
static int is_goal( const state_t *state )
{
  if( state->vars[ 0 ] == 0 && state->vars[ 1 ] == 0 && state->vars[ 2 ] == 0 && state->vars[ 3 ] == 0 && state->vars[ 4 ] == 0 && state->vars[ 5 ] == 0 && state->vars[ 6 ] == 0 && state->vars[ 7 ] == 0 && state->vars[ 8 ] == 1 && state->vars[ 9 ] == 1 && state->vars[ 10 ] == 1 && state->vars[ 11 ] == 1 && state->vars[ 12 ] == 1 && state->vars[ 13 ] == 1 && state->vars[ 14 ] == 1 && state->vars[ 15 ] == 1 && state->vars[ 16 ] == 2 && state->vars[ 17 ] == 2 && state->vars[ 18 ] == 2 && state->vars[ 19 ] == 2 && state->vars[ 20 ] == 2 && state->vars[ 21 ] == 2 && state->vars[ 22 ] == 2 && state->vars[ 23 ] == 2 && state->vars[ 24 ] == 3 && state->vars[ 25 ] == 3 && state->vars[ 26 ] == 3 && state->vars[ 27 ] == 3 && state->vars[ 28 ] == 3 && state->vars[ 29 ] == 3 && state->vars[ 30 ] == 3 && state->vars[ 31 ] == 3 && state->vars[ 32 ] == 4 && state->vars[ 33 ] == 4 && state->vars[ 34 ] == 4 && state->vars[ 35 ] == 4 && state->vars[ 36 ] == 4 && state->vars[ 37 ] == 4 && state->vars[ 38 ] == 4 && state->vars[ 39 ] == 4 && state->vars[ 40 ] == 5 && state->vars[ 41 ] == 5 && state->vars[ 42 ] == 5 && state->vars[ 43 ] == 5 && state->vars[ 44 ] == 5 && state->vars[ 45 ] == 5 && state->vars[ 46 ] == 5 && state->vars[ 47 ] == 5 ) {
    return 1;
  }
  return 0;
}

static void init_goal_state( state_t *state, int goal_rule )
{
  switch( goal_rule ) {
  case 0:
    state->vars[ 0 ] = 0;
    state->vars[ 1 ] = 0;
    state->vars[ 2 ] = 0;
    state->vars[ 3 ] = 0;
    state->vars[ 4 ] = 0;
    state->vars[ 5 ] = 0;
    state->vars[ 6 ] = 0;
    state->vars[ 7 ] = 0;
    state->vars[ 8 ] = 1;
    state->vars[ 9 ] = 1;
    state->vars[ 10 ] = 1;
    state->vars[ 11 ] = 1;
    state->vars[ 12 ] = 1;
    state->vars[ 13 ] = 1;
    state->vars[ 14 ] = 1;
    state->vars[ 15 ] = 1;
    state->vars[ 16 ] = 2;
    state->vars[ 17 ] = 2;
    state->vars[ 18 ] = 2;
    state->vars[ 19 ] = 2;
    state->vars[ 20 ] = 2;
    state->vars[ 21 ] = 2;
    state->vars[ 22 ] = 2;
    state->vars[ 23 ] = 2;
    state->vars[ 24 ] = 3;
    state->vars[ 25 ] = 3;
    state->vars[ 26 ] = 3;
    state->vars[ 27 ] = 3;
    state->vars[ 28 ] = 3;
    state->vars[ 29 ] = 3;
    state->vars[ 30 ] = 3;
    state->vars[ 31 ] = 3;
    state->vars[ 32 ] = 4;
    state->vars[ 33 ] = 4;
    state->vars[ 34 ] = 4;
    state->vars[ 35 ] = 4;
    state->vars[ 36 ] = 4;
    state->vars[ 37 ] = 4;
    state->vars[ 38 ] = 4;
    state->vars[ 39 ] = 4;
    state->vars[ 40 ] = 5;
    state->vars[ 41 ] = 5;
    state->vars[ 42 ] = 5;
    state->vars[ 43 ] = 5;
    state->vars[ 44 ] = 5;
    state->vars[ 45 ] = 5;
    state->vars[ 46 ] = 5;
    state->vars[ 47 ] = 5;
    break;
  }
}

/* get the first goal state and initialise iterator */
#define first_goal_state( state_ptr, int_ptr_goal_iter ) init_goal_state(state_ptr,*(int_ptr_goal_iter)=0)

/* get the next goal state
   returns 1 if there is another goal state, 0 otherwise */
static int8_t next_goal_state( state_t *state, int *goal_iter )
{
  switch( *goal_iter ) {
  case 0:
    return 0;
  }
  return 0;
}

