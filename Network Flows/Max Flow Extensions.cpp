// In Max Flow, to add a "demand" function d(u,v) which forces 
// edge (u,v) to have a flow of at least d(u,v), let s, t be 
// the source and sink respectively.

// This problem is reduced to a normal max flow in graph 
// V' = V u {s', t'}  
// with new capacities c', source s' and sink t':
// c'(s', v) = sum{ d(u,v), u in V }
// c'(v, t') = sum{ d(v,w), w in V }
// c'(u, v) = c(u,v) - d(u,v)
// c'(t, s) = INF

// There exists a solution in problem V if and only if the 
// problem in graph V' has a saturating max flow 
// (with |f| = sum{ d(u, v) / u,v in V }).
// If a max flow / min flow solution is needed, consider adding
// a node to control the total flow, controlling its 
// capacity / demand in a binary search.
