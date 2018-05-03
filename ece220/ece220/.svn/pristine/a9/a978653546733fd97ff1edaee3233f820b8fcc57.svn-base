#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <float.h>
#include <time.h>

#ifndef FLOORPLAN_H_
#define FLOORPLAN_H_

#define FROZEN 0.00001
#define TEMPERATURE_DECREASING_RATE 0.9
#define MAX_NUM_RAND_STEPS 2000
#define MIN(x, y) x < y ? x : y;
#define MAX(x, y) x > y ? x : y;

//-------------------------------------------------------------------------------------------------
// Definition field of enum and struct.
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
//an enum identifier and it defines the type of a cutline,
//whose value could be either vertical (V) or horizontal (H), or undefined (UNDEFINED_CUTLINE).
typedef enum CUTLINE {                                      // Cutline type.
  V = 0,
  H = 1,
  UNDEFINED_CUTLINE
}cutline_t;

//The module_t is a struct identifier for a module, which contains 1)
//an integer variable idx denoting the unique index of the module,
//2) two integer variabls llx and lly denoting the lower-left x and y coordinates of the module,
//and 3) two integer variables w and h denoting the width and height of the module.
typedef struct MODULE {                                     // Module struct.
  int idx;
  int llx, lly;//lower-left x and y coordinates of the module
  int w, h;//width and height of the module
}module_t;

//The expression_unit_t defines the unit of
//the postfix expression, which could be either a module pointer or a cutline value.
typedef struct EXPRESSION_UNIT {                            // Expression struct.
  module_t* module;
  cutline_t cutline;
}expression_unit_t;

//The node_t is a struct identifier that defines the node in the slicing tree.
//A node is either an internal node, where a cutline type must be explicitly specified
//or a leaf node where the value of module pointer must be assigned. Each node is
//associated with three node pointers, parent, left, and right.
//The topology of the slicing tree can be implicitly inferred by these node-to-node
//pointers. The pointer parent points to the parent of the node.
//Every node has only one parent and the parent of the tree root is assigned by NULL.
//Due to the binary property of a slicing tree, a node has two children,
//which are connected by the pointer left and the pointer right, respectively.
// A node with NULL values on both left and right pointers is a leaf node.
typedef struct NODE {                                       // Slicing tree struce.
  module_t* module;
  cutline_t cutline;
  struct NODE* parent;
  struct NODE* left;
  struct NODE* right;
}node_t;

typedef struct CLUSTER {                                    // Cluster of module.
  int beg, end;
  int w, h;
}cluster_t;

//-------------------------------------------------------------------------------------------------
// Definition of functions.

void floorplan(const char []);                              // Major subroutine of floorplan.
void read_modules(const char []);                           // Read the modules.
void draw_modules(const char []);                           // Draw the module.
void get_expression(node_t*, int, expression_unit_t*);      // Get the expression.
void pnt_expression(expression_unit_t *, int);              // Print the expression.
void pnt_modules();                                         // Display the module coordinates.
void write_modules(const char []);                          // Write the module into a file.
void postfix_traversal(node_t*, int*, expression_unit_t*);  // Postfix tree traversal.
void rotate(node_t*);                                       // Rotate the module.
void recut(node_t*);                                        // Change the cutline.
void swap_topology(node_t*, node_t*);                       // Swap the topology.
void swap_module(node_t*, node_t*);                         // Swap the module.
double optimize(node_t*, int);                              // Optimize the floorplan.
double packing(expression_unit_t*, int);                    // Packing.
int is_overlapped();                                        // Check if modules have overlap.
int is_internal_node(node_t*);                              // Check if is a internal node.
int is_leaf_node(node_t*);                                  // Check if is a leaf node.
int is_in_subtree(node_t*, node_t*);                        // Check the subtree statue.
int is_valid_expression(expression_unit_t*, int);           // Check if the expression is valid.
node_t* init_slicing_tree(node_t*, int);                    // Initialize the tree.
node_t* challenge_init_slicing_tree();                      // Initialize the tree.
node_t* challenge_init_slicing_tree(node_t*, int);          // Initialize the tree.
module_t* get_module(int);                                  // Get the module pointer.



#endif
