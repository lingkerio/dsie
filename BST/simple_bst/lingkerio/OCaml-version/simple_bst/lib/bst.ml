(* lib/BST.ml *)

(* Define the type for a binary search tree *)
type 'a bst =
  | Empty
  | Node of 'a * 'a bst * 'a bst

(* Create an empty BST *)
let empty = Empty

(* Insert a value into the BST *)
let rec insert x = function
  | Empty -> Node (x, Empty, Empty)
  | Node (y, left, right) as node ->
    if x < y then Node (y, insert x left, right)
    else if x > y then Node (y, left, insert x right)
    else node

(* Check if a value exists in the BST *)
let rec member x = function
  | Empty -> false
  | Node (y, left, right) ->
    if x < y then member x left
    else if x > y then member x right
    else true

(* Find the minimum value in the BST *)
let rec min_bst = function
  | Empty -> None
  | Node (x, Empty, _) -> Some x
  | Node (_, left, _) -> min_bst left

(* Find the maximum value in the BST *)
let rec max_bst = function
  | Empty -> None
  | Node (x, _, Empty) -> Some x
  | Node (_, _, right) -> max_bst right

(* Delete a value from the BST *)
let rec delete x = function
  | Empty -> Empty
  | Node (y, left, right) ->
    if x < y then Node (y, delete x left, right)
    else if x > y then Node (y, left, delete x right)
    else
      match left, right with
      | Empty, _ -> right
      | _, Empty -> left
      | _, _ ->
        (match min_bst right with
        | Some min_right -> Node (min_right, left, delete min_right right)
        | None -> failwith "Unexpected None in delete")