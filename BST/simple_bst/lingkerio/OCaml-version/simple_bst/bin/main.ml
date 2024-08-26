(* test/test_bst.ml *)

let process_operation tree (operation, value) =
  match operation with
  | "insert" -> Bst.insert value tree
  | "search" ->
    let _ = Bst.member value tree in
    tree
  | "delete" -> Bst.delete value tree
  | _ -> tree

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



let time_execution f x =
  let start_time = Unix.gettimeofday () in
  let result = f x in
  let end_time = Unix.gettimeofday () in
  let elapsed_time = end_time -. start_time in
  (result, elapsed_time)

let () =
  let operations = read_csv_file "../../../../benchmark/benchmark_operations.csv" in
  let (_, elapsed_time) =
    time_execution (List.fold_left process_operation Bst.empty) operations
  in
  Printf.printf "Total time to execute all operations: %.6f seconds\n" elapsed_time;
  (* Optional: further analyze the final_tree if needed *)
  ()
(* test_time.ml *)

(* let time_operation f x =
  let start_time = Unix.gettimeofday () in
  let result = f x in
  let end_time = Unix.gettimeofday () in
  let elapsed_time = end_time -. start_time in
  (result, elapsed_time)

let dummy_operation n =
  let rec loop i =
    if i = 0 then ()
    else loop (i - 1)
  in
  loop n

let () =
  let (_, elapsed_time) = time_operation dummy_operation 1_0_000 in
  Printf.printf "Time taken to perform dummy operation: %.6f seconds\n" elapsed_time *)
