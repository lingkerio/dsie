let log_to_file log_entry =
  let oc = open_out_gen [Open_creat; Open_text; Open_append] 0o666 "../correctness.csv" in
  output_string oc (log_entry ^ "\n");
  close_out oc

let process_operation tree (operation, value) =
  match operation with
  | "insert" ->
    let new_tree = Avl.insert value tree in
    log_to_file (Printf.sprintf "insert,%d" value);
    new_tree
  | "search" ->
    let result = Avl.member value tree in
    log_to_file (Printf.sprintf "search,%d,%s" value (if result then "true" else "false"));
    tree
  | "delete" ->
    let node_to_delete = if Avl.member value tree then Some tree else None in
    let new_tree = Avl.delete value tree in
    (match node_to_delete with
     | Some _ -> log_to_file (Printf.sprintf "delete,%d" value)
     | None -> log_to_file (Printf.sprintf "delete,%d,null" value));
    new_tree
  | "findmin" ->
    (match Avl.min_avl tree with
    | Some min_val -> log_to_file (Printf.sprintf "findmin,%d" min_val)
    | None -> log_to_file "findmin,null");
    tree
  | "findmax" ->
    (match Avl.max_avl tree with
    | Some max_val -> log_to_file (Printf.sprintf "findmax,%d" max_val)
    | None -> log_to_file "findmax,null");
    tree
  | _ ->
    Printf.eprintf "Warning: Unknown operation: %s\n" operation;
    tree

let read_csv_file filename =
  let in_channel = open_in filename in
  let rec loop acc =
    try
      let line = input_line in_channel in
      let parts = String.split_on_char ',' line in
      match parts with
      | [op; value_str] -> 
        (try
           let value = int_of_string (String.trim value_str) in
           loop ((op, value) :: acc)
         with Failure _ ->
           Printf.eprintf "Warning: Could not convert '%s' to int in line: %s\n" value_str line;
           loop acc)
      | _ -> 
        Printf.eprintf "Warning: Malformed line: %s\n" line;
        loop acc
    with End_of_file ->
      close_in in_channel;
      List.rev acc
  in
  loop []

let () =
  let operations = read_csv_file "../../../../benchmark/benchmark_operations.csv" in
    List.fold_left process_operation Avl.empty operations |> ignore