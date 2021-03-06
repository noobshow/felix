Package: src/packages/cparse.fdoc


===============
C Parsing Utils
===============

========== ========================
key        file                     
========== ========================
ctok.flx   share/lib/std/c/ctok.flx 
========== ========================

C Tokeniser
===========

This is a crude C tokeniser that is intended for parsing
header files only, i.e. interfaces.


.. index:: Ctok(class)
.. index:: newline(proc)
.. index:: str(fun)
.. index:: str(fun)
.. code-block:: felix

  //[ctok.flx]
  
  // TODO: strings, chars
  // NOTE: preprocesor directives start with # and end with newline
  // NOTE: trailing slosh is elided, but also ends a token, not really correct
  
  class Ctok
  {
  
  fun c_tok(x:string): list[string] =
  { 
    var result = Empty[string];
    var token = "";
    var n = x.len.int;
    var inmacro = false;
    var i = 0;
    while i < n do
      // 3 char tokens
      if x.[i.+3] in ("<<=", ">>=","...")  do
       result -= x.[i.+3];
       i += 3;
  
      elif x.[i.+2] == "\\\n" do
       i += 2;
      
      // C++ comment
      elif x.[i.+2] == "//" do
        i += 2;
        while i <= n and x.[i] != "\n" do
          ++i;
        done 
        if inmacro do
          result -= "\\n";
          inmacro = false;
        done
        ++i;
  
      // C comment
      elif x.[i.+2] == "/*" do
        i += 2;
        while i <= n and x.[i.+2] != "*/" do
          ++i;
        done
        i += 2;
  
      elif x.[i] == "\n" do
        if inmacro do
          result -= "\n";
          inmacro = false;
        done
        ++i;
  
      // whitespace
      elif ord x.[i]  <= 32 do
        ++i; 
  
      // 2 char tokens
      elif x.[i.+2] in ("::", 
         "<<", ">>", "<=", ">=", "==","!=". "&&","||",
        "++","--", "+=","==","!=","&=","^=","|=") 
      do
        result -= x.[i.+2];; 
        i += 2;
  
      elif x.[i] == "#" do
        inmacro = true;
        result -= "#";
        ++i;
  
      // 1 char tokens
      elif x.[i] in "<>^!+-*/%(){}[],:;&|?=" do
        result -= x.[i].string; 
        ++i;
  
  
      // char 
      elif x.[i] == "'" do
        ++i;
        token = x.[i].string;
        while i < n and x.[i] != "'" do
          if x.[i] == "\\" do
            token += "\\";
            ++i;
          done
          token += x.[i]; 
          ++i;
        done
        result -= token + "'";
        ++i;
  
      // string
      elif x.[i] == '"' do
        token = x.[i].string;
        ++i;
        while i < n and x.[i] != '"' do
          if x.[i] == "\\" do
            token += "\\";
            ++i;
          done
          token += x.[i]; 
          ++i;
        done
        result -= token + '"';
        ++i;
  
      // identifier
      elif iscidstart x.[i] do
        token = x.[i].string;
        ++i;
        while i <= n and iscidcont x.[i] do
          token += string x.[i]; 
          ++i;
        done
        result -= token;
  
      // number
      elif x.[i] in "0123456789" do
       token = x.[i].string;
       ++i;
       while x.[i] in "0123456789xabcdefXABCDEF.pP+-uUlL" do
         token += x.[i].string;
         ++i;
       done
       result -= token;
  
      // other
      else
       result -= x.[i].string;
       ++i;
      done // conditional
    done //loop
    return rev result;
  }
  proc dump_tokens_formatted (x:list[string]) {
    var nest = 0;
    proc newline() { println$ ""; print$ " " * ( 2 * nest); }
    println$ "Tokens = ";
    for token in tokens do
      if token == ";" do
        print$ ";"; newline;
  
      elif token == "{" do
        newline;
        print$ "{";
        ++nest;
        newline;
  
      elif token == "}" do
        --nest;
        newline;
        print$ "}";
        newline;
      elif token == "#" do
        newline;
        print$ "#"; 
      elif token == "\n" do
        print "#endmacro";
        newline;
      else 
        print$ token.str+  " ";
      done 
    done
  } // dump
  
  fun iscident(x:string) : bool = {
    var result = iscidstart x.[0];
    for ch in x.[1..] perform
      result &= iscidcont ch;
    return result;
  }
  typedef parameter_t = ctyp_t * string;
  
  typedef field_t = ctyp_t * string;
  
  // either or both the tag string is present of the field list is present
  typedef struct_t = string * opt[list[field_t]];
  
  typedef enumconst_t = string * int;
  typedef enum_t = string * list[enumconst_t];
  
  
  variant ctyp_t =
  | Base of string
  | Ptr of ctyp_t
  | ConstPtr of ctyp_t
  | Array of ctyp_t * int
  | Bitfield of string * int
  | Function of ctyp_t * list[parameter_t]
  | Struct of struct_t
  | Union of struct_t
  | Enum of enum_t
  ;
  instance Eq[ctyp_t] {
    fun == (a:ctyp_t, b:ctyp_t) => 
      match a,b with
      | Base x, Base y => x == y
      | Ptr x, Ptr y => x == y
      | ConstPtr x, ConstPtr y => x == y
      | Array (x,l1), Array (y,l2) => x == y and l1 == l2
      | Bitfield (x,l1), Bitfield (y,l2) => x == y and l1 == l2
      | Struct x, Struct y => x == y
      | Union x, Union y => x == y
      | Enum x, Enum y => x == y
      | _ => false
      endmatch
    ;
  }
  inherit Eq[ctyp_t];
  
  
  fun strbody (tag:string, fields:opt[list[field_t]]) : string =>
    if tag != "" then tag + " " else "" endif + 
    match fields with 
    | Some flds => 
      "{ " + fold_left (fun (acc:string) (fld:field_t) => acc + " " +  fld.str + ";") "" flds + " }"
    | None => ""
    endmatch
  ;
   
  instance Str[ctyp_t] {
    fun str : ctyp_t -> string =
      | Base b => b
      | Ptr x => x.str + "*"
      | ConstPtr x => x.str + " const*"
      | Array (x,l) => "array(" + x.str + "," + l.str + ")"
      | Bitfield (b,l) => b + ":" + l.str
      | Function (r,ps) => 
        r.str + "(" + catmap "," str of parameter_t ps + ")"
      | Struct s => "struct " + strbody s
      | Union s => "union " + strbody s
      | Enum b => "enum " + b.str
    ;
  }
  
  instance Str[parameter_t] {
    fun str (t:ctyp_t,n:string) => t.str + if n!="" then " " else "" endif + n;
  }
  
  fun discard_to_rbrace (level:int) (tokens: list[string]) =>
    match tokens with
    | "{" ! tokens => discard_to_rbrace (level + 1) tokens
    | "}" ! tokens => if level > 1 then discard_to_rbrace (level - 1) tokens else tokens
    | _ ! tokens  => discard_to_rbrace level tokens
    | Empty => tokens
    endmatch
  ;
  
  // discard everything up to the next top level }
  fun discard_to_rbrace (tokens: list[string]) =>
    discard_to_rbrace 0 tokens
  ;
  
  // discard everything up to the next top level ;
  // won't work for nested code because of ; in for statements
  fun discard_to_semi (tokens: list[string]) =>
    match tokens with
    | "{" ! tokens => discard_to_semi (discard_to_rbrace 1 tokens)
    | ";" ! tokens => tokens
    | _ ! tokens => discard_to_semi tokens
    | Empty => tokens
    endmatch
  ;
  
  fun rev_grab_to_rbrace (out:list[string]) (level:int) (tokens: list[string]) =>
    match tokens with
    | "{" ! tokens => rev_grab_to_rbrace ("{" ! out) (level + 1) tokens
    | "}" ! tokens => if level > 1 then rev_grab_to_rbrace ("}" ! out) (level - 1) tokens else out, tokens
    | token  ! tokens  => rev_grab_to_rbrace (token ! out) level tokens
    | Empty => out, tokens
    endmatch
  ;
  
  // grab everything up to the next top level }
  fun grab_to_rbrace (tokens: list[string]) =>
    rev (rev_grab_to_rbrace Empty[string] 0 tokens)
  ;
  
  // grab everything up to the next top level ;
  // won't work for nested code because of ; in for statements
  fun rev_grab_to_semi (out:list[string]) (tokens: list[string]) =>
    match tokens with
    | "{" ! tokens => 
      let grabbed, trailing = (rev_grab_to_rbrace out 1 tokens) in
      rev_grab_to_semi grabbed trailing
  
    | ";" ! tokens => out,tokens
    | _ ! tokens => rev_grab_to_semi out tokens
    | Empty => out,tokens
    endmatch
  ;
  
  fun grab_to_semi (tokens: list[string]) =>
    rev (rev_grab_to_semi Empty[string] tokens)
  ;
  
  
  // ***********************************************
  // input a token list
  // parse the LHS of a C type, the base type, eg int
  // return that and the rest of the tokens
  // ***********************************************
  
  
  fun parse_type_base (tokens:list[string]) : opt[ctyp_t * bool] * list[string] =
  {
    var isconst = false;
  next:>
    if is_empty tokens return None[ctyp_t * bool], tokens;
    var token = head tokens;
    tokens = tail tokens;
    if token == "const" do
      isconst = true;
      goto next;
    elif token == "struct" do
      // set tag if present
      var tag = "";
      if tokens.head.iscident do
        tag = head tokens;
        tokens = tail tokens;
      done 
      // set field list if present
      var fields, toks = parse_struct_body tokens;
      var ctyp = Struct (tag, fields);
      tokens = toks;
    elif token == "union" do
      tag = "";
      if tokens.head.iscident do
        tag = head tokens;
        tokens = tail tokens;
      done 
      fields, toks = parse_struct_body tokens;
      ctyp = Union (tag, fields);
      tokens = toks;
    elif token == "enum" do
      token = head tokens;
      tokens = tail tokens;
      ctyp = Enum (token, Empty[enumconst_t]);
    else
      ctyp = Base token; // base type
    done
    return Some (ctyp, isconst), tokens;
  }
  // ***********************************************
  // input a token list and a base type and const flag
  // parse the RHS of a C type, combine with base type
  // return that and the rest of the tokens
  // ***********************************************
  
  fun parse_tail_type 
  (
    var ctyp:ctyp_t, 
    isconst:bool, 
    var tokens:list[string]
  ) 
  : ctyp_t * list[string] =
  {
  next:>
    if is_empty tokens return ctyp, tokens; 
    var token = head tokens;
    if token == "*" do
      if isconst do 
        ctyp = ConstPtr (ctyp);
        isconst = false;
      else 
        ctyp = Ptr ctyp;
      done
    elif token == "long" and  ctyp == Base "long" do
      ctyp = Base "long long";
    else
      return ctyp, tokens;
    done
    tokens = tail tokens;
    goto next;
  }
  
  // ***********************************************
  // input a token list
  // parse a C type
  // return type and trailing tokens
  // ***********************************************
  
  fun parse_ctype (var tokens:list[string]) : opt[ctyp_t] * list[string] = {
    match parse_type_base tokens with
    | Some (cty, isconst),toks => 
      var ctyp, trailing = parse_tail_type (cty, isconst, toks);
      return Some ctyp, trailing;
  
    | None,toks => return None[ctyp_t],toks;
    endmatch;
  }
  
  
  // ***********************************************
  // parse array suffix if present
  // recursive, assumes length is a single token or missing
  // ***********************************************
  
  fun parse_array (ctyp:ctyp_t, tokens: list[string]) : ctyp_t * list[string] = {
     match tokens with
     | "[" ! v ! "]" ! rest => return Array (ctyp, v.int), rest; 
     | "[" ! "]" ! rest => return Array (ctyp, 0), rest; 
     | _ => println$ "Failed array"; return ctyp, tokens;
     endmatch;
  }
   
  // ***********************************************
  // Input a token list
  // Parse a function parameter
  // retun C type and parameter name (could be empty string)
  // bugs out if trailing more than one token
  // ***********************************************
  
  fun parse_parameter(var tokens: list[string]) : opt[ctyp_t * string] * list[string] =
  {
    match parse_ctype tokens with
    | None,toks => 
      return None [ctyp_t * string], toks;
  
    | Some cty, toks =>
      var ctyp = cty;
      tokens = toks;
      return parse_field_tail (ctyp, tokens);
    endmatch;
  }
  
  fun parse_field_tail (var ctyp:ctyp_t, var tokens: list[string]) 
  : opt[ctyp_t * string] * list[string] 
  =
  {
  again:>
    match tokens with
    // no parameter name
    | Empty => return Some (ctyp,""),tokens;
  
    // array type, no parameter name
    | "[" ! toks =>    
      tokens = "" ! tokens;
      goto again; // push dummy name onto input
  
    // array type, parameter name
    | param ! "[" ! toks when iscident param =>    
      var l1 = tokens.len;
      ctyp, tokens= parse_array (ctyp, tail tokens);
      var l2 = tokens.len;
      if l2 < l1 do  // stop infinite loop
        tokens = param + tokens; // put param name back in input
        goto again;
      else
        return Some (ctyp, param), toks;
      done
  
    // function type, function name
    // named: i.e like int f(int,int)
    | param ! "(" ! toks when iscident param =>    
      l1 = tokens.len;
      ctyp, tokens= parse_function_decl (ctyp, tail tokens);
      l2 = tokens.len;
      if l2 < l1 do  // stop infinite loop
        tokens = param + tokens; // put param name back in input
        goto again;
      else
        return Some (ctyp, param), toks;
      done
  
    // function pointer type, name
    // named: i.e like int (*f)(int,int)
    | "(" ! "*" ! param ! toks when iscident param =>    
      l1 = tokens.len;
      ctyp, tokens= parse_function_decl (ctyp, "(" ! "*" ! toks);
      l2 = tokens.len;
      if l2 < l1 do  // stop infinite loop
        tokens = param + tokens; // put param name back in input
        goto again;
      else
        return Some (ctyp, param), toks;
      done
  
  
    // simple type, parameter name
    | param ! toks when iscident param => 
      return Some (ctyp,param),toks;
  
  
    // simple type, no parameter name
    | _ =>
      return Some (ctyp,""), tokens;
    endmatch;
  }
  
  // comma separated list
  fun parse_parameter_list(var tokens: list[string]) : list[ctyp_t * string] * list[string] =
  {
     var parameters = Empty[ctyp_t * string];
  again:>
    match parse_parameter tokens with
    | None,toks => 
      return rev parameters, toks;
    | Some (ctyp,name), toks =>
      tokens = toks;
      parameters -= (ctyp,name);
      if is_empty tokens return rev parameters,tokens;
      match tokens with
      | ","! rest =>
        tokens = rest;
        goto again;
      | _ => 
        return rev parameters, tokens;
      endmatch;
    endmatch;
  }
  
  // excludes trailing ; cause it isn't a ; in a typedef!
  fun parse_field_list (var tokens: list[string]) : list[ctyp_t * string] * list[string] =
  {
    var fields = Empty[ctyp_t * string];
    match parse_type_base tokens with
    | None, toks => return fields, tokens; // no fields 
    | Some (base_ctyp,isconst), toks =>
      var ctyp,toks2 = parse_tail_type (base_ctyp,isconst,toks);
  again:>
      match parse_field_tail (ctyp, toks2) with
      | None, toks => return fields, toks;
      | Some fld, toks =>
        fields -=  fld;
        if head toks == "," do
          ctyp,toks2 = parse_tail_type (base_ctyp,isconst,tail toks);
          goto again;
        else
          return rev fields, toks;
        done
      endmatch;
    endmatch;
  }
  
  // includes { and }
  // returns None if no { present 
  fun parse_struct_body (var tokens: list[string]) : opt[list[field_t]] * list[string] =
  {
     var fields = Empty[field_t];
     if head tokens != "{" return None[list[field_t]], tokens;
     tokens = tail tokens;
  again:>
     if head tokens == "}" return Some fields, tail tokens;
     var flds, toks = parse_field_list tokens;
     fields += flds; 
     if head toks != ";" return Some fields,toks;
     tokens = tail toks;
     goto again;
  }
  
  // called by parse_function_decl only
  private fun parse_function_ptr_decl (ret:ctyp_t, var tokens:list[string]) : ctyp_t * list[string] = {
    match tokens with
    | "*" ! ")" ! "(" ! trailing =>
      def var params, tokens = parse_parameter_list trailing;
      assert head tokens== ")";
      return Ptr (Function (ret, params)), tail tokens;
    | _ => 
      println$ "Error, parse_function_ptr_decl, tokens=" + tokens.str;
      assert false;
    endmatch;
  }
  
  fun parse_function_decl (ret:ctyp_t, var tokens:list[string]) : ctyp_t * list[string] = {
    assert head tokens == "(";
    tokens = tail tokens; // head must be "(" to get here
    if head tokens == "*" return parse_function_ptr_decl (ret, tokens);
    var params, trailing= parse_parameter_list tokens;
    assert head trailing== ")";
    return Function (ret,params), tail trailing;
  }
  
  
  }
  
  
