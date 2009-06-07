(** Mappings *)

open Flx_ast
open Flx_types

val map_type:
  (typecode_t -> typecode_t) -> typecode_t -> typecode_t

val map_b0type:
  (b0typecode_t -> b0typecode_t) -> b0typecode_t -> b0typecode_t

val map_btype:
  (btypecode_t -> btypecode_t) -> btypecode_t -> btypecode_t

val iter_b0type:
  (b0typecode_t -> unit) -> b0typecode_t -> unit

val iter_btype:
  (btypecode_t -> unit) -> btypecode_t -> unit

(* throw Not_found if type variable not under a pointer
 * is found
 *)
val check_abstract_type: btypecode_t -> unit
val check_abstract_expr: tbexpr_t -> unit
val check_abstract_exe : bexe_t -> unit

val flat_iter_tbexpr:
  (bid_t -> unit) ->
  (tbexpr_t -> unit) ->
  (btypecode_t -> unit) ->
  tbexpr_t -> unit

val iter_tbexpr:
  (bid_t -> unit) ->
  (tbexpr_t -> unit) ->
  (btypecode_t -> unit) ->
  tbexpr_t -> unit

val map_expr:
  (expr_t -> expr_t) ->
  expr_t ->
  expr_t

val map_tbexpr:
  (bid_t -> bid_t) ->
  (tbexpr_t -> tbexpr_t) ->
  (btypecode_t -> btypecode_t) ->
  tbexpr_t -> tbexpr_t

val iter_bexe:
  (bid_t -> unit) ->
  (tbexpr_t -> unit) ->
  (btypecode_t -> unit) ->
  (string -> unit) ->
  (string -> unit) ->
  bexe_t -> unit

val map_bexe:
  (bid_t -> bid_t) ->
  (tbexpr_t -> tbexpr_t) ->
  (btypecode_t -> btypecode_t) ->
  (string -> string) ->
  (string -> string) ->
  bexe_t -> bexe_t

val reduce_tbexpr:
  fully_bound_symbol_table_t ->
  tbexpr_t -> tbexpr_t

val reduce_bexe:
  fully_bound_symbol_table_t ->
  bexe_t -> bexe_t

val reduce_type:
  btypecode_t ->
  btypecode_t

val scan_expr: expr_t -> Flx_srcref.t list
