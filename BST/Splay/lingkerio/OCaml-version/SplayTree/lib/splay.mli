(* lib/splay.mli *)

(* Type for Splay Tree *)
type 'a splay

(* Function to create an empty splay tree *)
val empty : 'a splay

(* Function to insert a value into the splay tree *)
val insert : 'a -> 'a splay -> 'a splay

(* Function to check if a value exists in the splay tree *)
val member : 'a -> 'a splay -> bool * 'a splay

(* Function to find the minimum value in the splay tree *)
val min_splay : 'a splay -> 'a option * 'a splay

(* Function to find the maximum value in the splay tree *)
val max_splay : 'a splay -> 'a option * 'a splay

(* Function to delete a value from the splay tree *)
val delete : 'a -> 'a splay -> 'a splay
