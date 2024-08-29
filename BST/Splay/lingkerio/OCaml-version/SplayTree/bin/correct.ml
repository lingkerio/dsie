(* Logging function *)
let log_to_file log_entry =
  let oc = open_out_gen [Open_creat; Open_text; Open_append] 0o666 "correctness.csv" in
  output_string oc (log_entry ^ "\n");
  close_out oc

(* Function to process operations on the Splay tree *)
let process_operation tree (operation, value) =
  match operation with
  | "insert" ->
    let new_tree = Splay.insert value tree in
    log_to_file (Printf.sprintf "insert,%d" value);
    new_tree
  | "search" ->
    let (result, new_tree) = Splay.member value tree in
    log_to_file (Printf.sprintf "search,%d,%s" value (if result then "true" else "false"));
    new_tree
  | "delete" ->
    let (result, _) = Splay.member value tree in
    let new_tree = Splay.delete value tree in
    if result then
      log_to_file (Printf.sprintf "delete,%d" value)
    else
      log_to_file (Printf.sprintf "delete,%d,null" value);
    new_tree
  | "findmin" ->
    let (min_val, new_tree) = Splay.min_splay tree in
    (match min_val with
     | Some v -> log_to_file (Printf.sprintf "findmin,%d" v)
     | None -> log_to_file "findmin,null");
    new_tree
  | "findmax" ->
    let (max_val, new_tree) = Splay.max_splay tree in
    (match max_val with
     | Some v -> log_to_file (Printf.sprintf "findmax,%d" v)
     | None -> log_to_file "findmax,null");
    new_tree
  | _ ->
    Printf.eprintf "Warning: Unknown operation: %s\n" operation;
    tree

(* Function to read operations from a CSV file *)
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

(* Main function *)
let () =
  let operations = read_csv_file "../../../../benchmark/benchmark_operations.csv" in
  List.fold_left process_operation Splay.empty operations |> ignore
