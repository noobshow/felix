open Flx_mtypes1
open Flx_types
open List

(* generic entity instances: functions, variables *)
type instance_registry_t = (int * btypecode_t list, int) Hashtbl.t

type felix_compiler_options_t =
{
  print_flag: bool;
  debug : bool;
  optimise : bool;
  trace : bool;
  include_dirs : string list;
  files : string list;
  raw_options: (string * string) list;
  reverse_return_parity: bool;
  max_inline_length : int;
  compile_only : bool;
  force_recompile : bool;
  with_comments : bool;
  document_grammar: bool;
  document_typeclass: bool;
  mangle_names : bool;
  elkhound : string;
  generate_axiom_checks : bool;
  auto_imports : string list;
  cache_dir : string option;
  output_dir : string option;
}


type sym_state_t =
{
  dfns : symbol_table_t;
  counter : int ref;
  varmap : typevarmap_t;
  ticache : (int, btypecode_t) Hashtbl.t;
  glr_cache : (int, btypecode_t) Hashtbl.t;
  env_cache : (int, env_t) Hashtbl.t;
  registry : type_registry_t;
  compiler_options : felix_compiler_options_t;
  instances : instance_registry_t;
  include_files : string list ref;
  roots : IntSet.t ref;
  wrappers : (int, int) Hashtbl.t;
  lexers : (int * tbexpr_t, int) Hashtbl.t;
  parsers : (int * btypecode_t * int list, int) Hashtbl.t;
  quick_names : (string, (int * btypecode_t list)) Hashtbl.t;
  mutable bifaces : biface_t list;
  mutable reductions : reduction_t list;
  mutable axioms: axiom_t list;
  variant_map: (btypecode_t * btypecode_t,int) Hashtbl.t;
  typeclass_to_instance: (int, (bvs_t * btypecode_t * btypecode_t list * int) list) Hashtbl.t;
  instances_of_typeclass: (int, (int * (bvs_t * btypecode_t * btypecode_t list)) list) Hashtbl.t;
  transient_specialisation_cache: (int * btypecode_t list, int * btypecode_t list) Hashtbl.t;
}

module VarMap = StringMap
type varmap_t = string_string_map_t

module TypecodeSet = Set.Make(
  struct type t = Flx_ast.typecode_t let compare = compare end
)
type typecodeset_t = TypecodeSet.t

let typecodeset_of_list x =
  let rec tsol x = match x with
  | h :: t -> TypecodeSet.add h (tsol t)
  | [] -> TypecodeSet.empty
  in tsol x

let typecodeset_map f x = typecodeset_of_list (map f (TypecodeSet.elements x))

(* for regular expressions *)

(* PosSet -- set of positions in regular expression, used for followpos *)
module PosSet = IntSet
module PosSetSet = IntSetSet
module CharSet = IntSet

module Drules = Map.Make(struct
  type t = string
  let compare = compare
end)
