(* lib/BST.mli *)

(* Type for a binary search tree *)
type 'a bst

(* Function to create an empty BST *)
val empty : 'a bst

(* Function to insert a value into the BST *)
val insert : 'a -> 'a bst -> 'a bst

(* Function to check if a value exists in the BST *)
val member : 'a -> 'a bst -> bool

(* Function to find the minimum value in the BST *)
val min_bst : 'a bst -> 'a option

(* Function to find the maximum value in the BST *)
val max_bst : 'a bst -> 'a option

(* Function to delete a value from the BST *)
val delete : 'a -> 'a bst -> 'a bst
