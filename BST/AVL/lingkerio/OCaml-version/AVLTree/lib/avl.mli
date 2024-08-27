(* lib/avl.mli *)

(* Type for AVL Tree *)
type 'a avl

(* Function to create an empty AVL Tree *)
val empty : 'a avl

(* Function to insert a value into the AVL Tree *)
val insert : 'a -> 'a avl -> 'a avl

(* Function to check if a value exists in the AVL Tree *)
val member : 'a -> 'a avl -> bool

(* Function to find the minimum value in the AVL Tree *)
val min_avl : 'a avl -> 'a option

(* Function to find the maximum value in the AVL Tree *)
val max_avl : 'a avl -> 'a option

(* Function to delete a value from the AVL Tree *)
val delete : 'a -> 'a avl -> 'a avl
