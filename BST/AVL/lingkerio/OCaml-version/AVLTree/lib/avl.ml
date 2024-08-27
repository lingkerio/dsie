(* lib/avl.ml *)

(* Definition type for an AVL tree *)
type 'a avl =
  | Empty
  | Node of 'a * 'a avl * 'a avl * int

(* Create an empty AVL tree *)
let empty = Empty

(* Get the height of an AVL tree node *)
let height = function
  | Empty -> 0
  | Node (_, _, _, h) -> h

(* Find the minimum value in the AVL tree *)
let rec min_avl = function
  | Empty -> None
  | Node (x, Empty, _, _) -> Some x
  | Node (_, left, _, _) -> min_avl left

(* Find the maximum value in the AVL tree *)
let rec max_avl = function
  | Empty -> None
  | Node (x, _, Empty, _) -> Some x
  | Node (_, _, right, _) -> max_avl right

(* Check if a value exists in the AVL tree *)
let rec member x = function
  | Empty -> false
  | Node (y, left, right, _) ->
    if x < y then member x left
    else if x > y then member x right
    else true

(* Calculate the balance factor of a node *)
let balance_factor = function
  | Empty -> 0
  | Node (_, left, right, _) -> height left - height right

(* Rotate left *)
let rotate_left = function
  | Node (x, a, Node (y, b, c, _), _) ->
    Node (y, Node (x, a, b, 1 + max (height a) (height b)),
               c, 1 + max (1 + max (height a) (height b)) (height c))
  | _ -> failwith "Invalid rotation"

(* Rotate right *)
let rotate_right = function
  | Node (y, Node (x, a, b, _), c, _) ->
    Node (x, a, Node (y, b, c, 1 + max (height b) (height c)),
               1 + max (height a) (1 + max (height b) (height c)))
  | _ -> failwith "Invalid rotation"

(* Rotate left-right *)
let rotate_left_right = function
  | Node (x, a, Node (y, b, c, _), _) ->
    rotate_left (Node (x, a, rotate_right (Node (y, b, c, 1 + max (height b) (height c))),
                             1 + max (height a) (1 + max (height b) (height c))))
  | _ -> failwith "Invalid rotation"

(* Rotate right-left *)
let rotate_right_left = function
  | Node (y, Node (x, a, b, _), c, _) ->
    rotate_right (Node (y, rotate_left (Node (x, a, b, 1 + max (height a) (height b))),
                             c, 1 + max (1 + max (height a) (height b)) (height c)))
  | _ -> failwith "Invalid rotation"

(* Balance the AVL tree *)
let balance = function
  | Node (x, a, b, _) when balance_factor (Node (x, a, b, height a)) > 1 ->
    if balance_factor a >= 0 then rotate_right (Node (x, a, b, 1 + max (height a) (height b)))
    else rotate_right_left (Node (x, a, b, 1 + max (height a) (height b)))
  | Node (x, a, b, _) when balance_factor (Node (x, a, b, height b)) < -1 ->
    if balance_factor b <= 0 then rotate_left (Node (x, a, b, 1 + max (height a) (height b)))
    else rotate_left_right (Node (x, a, b, 1 + max (height a) (height b)))
  | node -> node

(* Insert a value into the AVL tree *)
let rec insert x = function
  | Empty -> Node (x, Empty, Empty, 1)
  | Node (y, left, right, _) as node ->
    let new_node = 
      if x < y then
        let new_left = insert x left in
        Node (y, new_left, right, 1 + max (height new_left) (height right))
      else if x > y then
        let new_right = insert x right in
        Node (y, left, new_right, 1 + max (height left) (height new_right))
      else node
    in
    balance new_node

(* Delete a value from the AVL tree *)
let rec delete x = function
  | Empty -> Empty
  | Node (y, left, right, _) ->
    let new_node = 
      if x < y then
        let new_left = delete x left in
        Node (y, new_left, right, 1 + max (height new_left) (height right))
      else if x > y then
        let new_right = delete x right in
        Node (y, left, new_right, 1 + max (height left) (height new_right))
      else
        match left, right with
        | Empty, _ -> right
        | _, Empty -> left
        | _ ->
          (match min_avl right with
          | Some min_right ->
            let new_right = delete min_right right in
            Node (min_right, left, new_right, 1 + max (height left) (height new_right))
          | None -> failwith "Unexpected None in delete")
    in
    balance new_node