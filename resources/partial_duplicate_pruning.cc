
// Code that shows how to use PSVN API for partial pruning of duplicates.
// psvn2c must be called with history_length > 0 for partial pruning.
// PSVN pruning implements automata-based pruning. The current node in
// the automaton is stored in the variable called 'history' of type int.
// Initially, history is set to 'init_history'. The variable 'state'
// contains the state to be expanded.

ruleid_iterator_t iter; // iterator over rules for state
state_t child;          // stores child
int ruleid;             // id of rule applied

init_fwd_iter(&iter, &state);
while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
    if( fwd_rule_valid_for_history(history, ruleid) == 0 ) continue;
    apply_fwd_rule(ruleid, &state, &child);
    int move_cost = get_fwd_rule_cost(ruleid);
    int new_history = next_fwd_history(history, ruleid); // next history for child
    // do something with child
}

// If doing regression, change 'fwd' by 'bwd'

