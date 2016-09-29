// Copyright 2013-2016 Stanford University
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef _STOKE_SRC_SYMSTATE_PRINT_VISITOR
#define _STOKE_SRC_SYMSTATE_PRINT_VISITOR

#include "src/symstate/visitor.h"

namespace stoke {

class SymPrintVisitor : public SymVisitor<void, void, void> {

public:
  SymPrintVisitor(std::ostream& os) : os_(os) {}

  void visit_binop(const SymBitVectorBinop * const bv) {

    switch (bv->type()) {
    case SymBitVector::AND:
      os_ << "(bvand ";
      break;
    case SymBitVector::CONCAT:
      os_ << "(concat ";
      break;
    case SymBitVector::DIV:
      os_ << "(bvudiv ";
      break;
    case SymBitVector::MINUS:
      os_ << "(bvsub ";
      break;
    case SymBitVector::MOD:
      os_ << "(unknown-mod ";
      break;
    case SymBitVector::MULT:
      os_ << "(bvmul ";
      break;
    case SymBitVector::OR:
      os_ << "(bvor ";
      break;
    case SymBitVector::PLUS:
      os_ << "(bvadd ";
      break;
    case SymBitVector::ROTATE_LEFT:
      os_ << "(unknown-rol ";
      break;
    case SymBitVector::ROTATE_RIGHT:
      os_ << "(unknown-ror ";
      break;
    case SymBitVector::SHIFT_LEFT:
      os_ << "(bvshl ";
      break;
    case SymBitVector::SHIFT_RIGHT:
      os_ << "(bvlshr ";
      break;
    case SymBitVector::SIGN_DIV:
      os_ << "(bvsdiv ";
      break;
    case SymBitVector::SIGN_MOD:
      os_ << "(bvsmod ";
      break;
    case SymBitVector::SIGN_SHIFT_RIGHT:
      os_ << "(bvashr ";
      break;
    case SymBitVector::XOR:
      os_ << "(bvxor ";
      break;
    default:
      os_ << "(UNHANDLED_BINOP" << bv->type() << " ";
      assert(false);
    }

    (*this)(bv->a_);
    os_ << " ";
    (*this)(bv->b_);
    os_ << ")";
  }

  /* Visit a binop on a bool */
  void visit_binop(const SymBoolBinop * const b) {

    switch (b->type()) {
    case SymBool::AND:
      os_ << "(&& ";
      break;
    case SymBool::IFF:
      os_ << "(<=> ";
      break;
    case SymBool::IMPLIES:
      os_ << "(=> ";
      break;
    case SymBool::OR:
      os_ << "(|| ";
      break;
    case SymBool::XOR:
      os_ << "(xor ";
      break;
    default:
      os_ << "(UNHANDLED_BINOP" << b->type() << " ";
      assert(false);
    }

    (*this)(b->a_);
    os_ << " ";
    (*this)(b->b_);
    os_ << ")";
  }


  void visit_unop(const SymBitVectorUnop * const bv) {
    os_ << "(";
    switch (bv->type()) {
    case SymBitVector::NOT:
      os_ << "bvnot";
      break;
    case SymBitVector::U_MINUS:
      os_ << "bvneg";
      break;
    default:
      os_ << "UNHANDLED_UNOP" << bv->type() << " ";
      assert(false);
    }

    os_ << " ";
    (*this)(bv->bv_);
    os_ << ")";
  }


  void visit_compare(const SymBoolCompare * const b) {

    switch (b->type()) {
    case SymBool::EQ:
      os_ << "(bveq ";
      break;
    case SymBool::GE:
      os_ << "(bvuge ";
      break;
    case SymBool::SIGN_GE:
      os_ << "(bvsge ";
      break;
    case SymBool::GT:
      os_ << "(bvugt ";
      break;
    case SymBool::SIGN_GT:
      os_ << "(bvsgt ";
      break;
    case SymBool::LE:
      os_ << "(bvule ";
      break;
    case SymBool::SIGN_LE:
      os_ << "(bvsle ";
      break;
    case SymBool::LT:
      os_ << "(bvult ";
      break;
    case SymBool::SIGN_LT:
      os_ << "(bvslt ";
      break;
    default:
      os_ << "(UNHANDLED_COMPARE" << b->type() << " ";
      assert(false);
    }

    (*this)(b->a_);
    os_ << " ";
    (*this)(b->b_);
    os_ << ")";

  }

  /** Visit a bit-vector constant */
  void visit(const SymBitVectorConstant * const bv) {
    os_ << "(bv " << std::dec << bv->constant_ << " " << bv->size_ << ")";
  }

  /** Visit a bit-vector extract */
  void visit(const SymBitVectorExtract * const bv) {
    os_ << "(extract " << std::dec << bv->high_bit_ << " " << bv->low_bit_ << " ";
    (*this)(bv->bv_);
    os_ << ")";
  }

  /** Visit a bit-vector function */
  void visit(const SymBitVectorFunction * const bv) {
    os_ << "(uninterpreted-" << bv->f_.name << " ";

    for (size_t i = 0; i < bv->args_.size(); ++i) {
      (*this)(bv->args_[i]);
      if (i != bv->args_.size() - 1)
        os_ << " ";
    }

    os_ << ")";
  }

  /** Visit a bit-vector if-then-else */
  void visit(const SymBitVectorIte * const bv) {
    os_ << "(if ";
    (*this)(bv->cond_);
    os_ << " ";
    (*this)(bv->a_);
    os_ << " ";
    (*this)(bv->b_);
    os_ << ")";
  }

  /** Visit a bit-vector sign-extend */
  void visit(const SymBitVectorSignExtend * const bv) {
    os_ << "(sign-extend ";
    (*this)(bv->bv_);
    os_ << " (bitvector " << bv->size_ << "))";
  }

  /** Visit a bit-vector variable */
  void visit(const SymBitVectorVar * const bv) {
    os_ << bv->name_;
  }

  /** Visit an array lookup */
  void visit(const SymBitVectorArrayLookup * const bv) {
    os_ << "(";
    (*this)(bv->a_);
    os_ << ")[";
    (*this)(bv->key_);
    os_ << "]";
  }

  /** Visit a boolean ARRAY EQ */
  void visit(const SymBoolArrayEq * const b) {
    os_ << "(== ";
    (*this)(b->a_);
    os_ << " ";
    (*this)(b->b_);
    os_ << ")";
  }

  /** Visit a boolean FALSE */
  void visit(const SymBoolFalse * const b) {
    os_ << "#f";
  }

  /** Visit a boolean NOT */
  void visit(const SymBoolNot * const b) {
    os_ << "(not ";
    (*this)(b->b_);
    os_ << ")";
  }

  /** Visit a boolean TRUE */
  void visit(const SymBoolTrue * const b) {
    os_ << "#t";
  }

  /** Visit a boolean VAR */
  void visit(const SymBoolVar * const b) {
    os_ << b->name_;
  }

  /** Visit an array STORE */
  void visit(const SymArrayStore * const a) {
    os_ << "(";
    (*this)(a->a_);
    os_ << " update ";
    (*this)(a->key_);
    os_ << " -> ";
    (*this)(a->value_);
    os_ << ")";
  }

  /** Visit an array VAR */
  void visit(const SymArrayVar * const a) {
    os_ << "<" << a->name_ << "|" << a->key_size_ << "|" << a->value_size_ << ">";
  }

private:
  std::ostream& os_;

};

} //namespace

#endif

