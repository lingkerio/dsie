type 'a splay =
  | Empty
  | Node of 'a * 'a splay * 'a splay

let rec splay x = function
  | Empty -> failwith "splay: value not found"
  | Node (y, a, b) as tree ->
    if x < y then
      match a with
      | Empty -> failwith "splay: value not found"
      | Node (z, a1, a2) ->
        if x < z then
          match splay x a1 with
          | Empty -> failwith "splay: value not found"
          | Node (c, d, e) ->
            Node (c, d, Node (z, e, Node (y, a2, b)))
        else if x > z then
          match splay x a2 with
          | Empty -> failwith "splay: value not found"
          | Node (c, d, e) ->
            Node (c, Node (z, a1, d), Node (y, e, b))
        else
          Node (z, a1, Node (y, a2, b))
    else if x > y then
      match b with
      | Empty -> failwith "splay: value not found"
      | Node (z, a1, a2) ->
        if x < z then
          match splay x a1 with
          | Empty -> failwith "splay: value not found"
          | Node (c, d, e) ->
            Node (c, Node (y, a, d), Node (z, e, a2))
        else if x > z then
          match splay x a2 with
          | Empty -> failwith "splay: value not found"
          | Node (c, d, e) ->
            Node (c, Node (z, Node (y, a, a1), d), e)
        else
          Node (z, Node (y, a, a1), a2)
    else
      tree     

let empty = Empty

let rec insert x = function
  | Empty -> Node (x, Empty, Empty)
  | Node (y, a, b) as tree ->
    if x < y then
      Node (y, insert x a, b)
    else if x > y then
      Node (y, a, insert x b)
    else
      tree

let insert x tree = splay x (insert x tree)

let rec member x = function
  | Empty -> false
  | Node (y, a, b) ->
    if x < y then
      member x a
    else if x > y then
      member x b
    else
      true

let member x tree =
  if member x tree then
    (true, splay x tree)
  else
    (false, tree)

let rec min_splay = function
  | Empty -> None
  | Node (x, Empty, _) -> Some x
  | Node (_, a, _) -> min_splay a

let min_splay tree =
  let min = min_splay tree in
  match min with
  | None -> (None, tree)
  | Some x -> (Some x, splay x tree)

let rec max_splay = function
  | Empty -> None
  | Node (x, _, Empty) -> Some x
  | Node (_, _, b) -> max_splay b

let max_splay tree =
  let max = max_splay tree in
  match max with
  | None -> (None, tree)
  | Some x -> (Some x, splay x tree)

let rec delete x tree =
  let (found, tree) = member x tree in
  if found then
    match tree with
    | Empty -> failwith "member failed"
    | Node(_, a, b) ->
      match a, b with
      | Empty, _ -> b
      | _, Empty -> a
      | _, _ ->
        match min_splay b with
        | (None, _) -> failwith "min_splay failed"
        | (Some z, b') -> (Node(z, a, delete z b'))
  else
    tree
