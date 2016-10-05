// Copyright 2013-2016 Stanford University
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>

#include "src/ext/cpputil/include/command_line/command_line.h"
#include "src/ext/cpputil/include/signal/debug_handler.h"
#include "src/ext/cpputil/include/io/filterstream.h"
#include "src/ext/cpputil/include/io/column.h"
#include "src/ext/cpputil/include/io/console.h"

#include "src/symstate/pretty_visitor.h"
#include "src/symstate/print_visitor.h"
#include "src/symstate/memory/trivial.h"
#include "src/validator/handlers/combo_handler.h"

#include "tools/gadgets/solver.h"
#include "tools/gadgets/validator.h"

using namespace cpputil;
using namespace std;
using namespace stoke;
using namespace x64asm;

auto& input_header = Heading::create("Enumeration options:");

// auto& code_arg = ValueArg<Code, CodeReader, CodeWriter>::create("code")
//                  .description("Input code directly");

// auto& dbg = Heading::create("Formula Printing Options:");
auto& arg_lessbits = FlagArg::create("lessbits")
                     .description("Also output registers/constants with fewer than 32 bits");
// auto& show_unchanged_arg = FlagArg::create("show_unchanged")
//                            .description("Show the formula for unchanged registers");
// auto& use_smtlib_format_arg = FlagArg::create("smtlib_format")
//                               .description("Show formula in smtlib format");
// auto& no_simplify_arg = FlagArg::create("no_simplify")
//                         .description("Don't simplify formulas before printing them.");


std::map<x64asm::Type, std::vector<x64asm::Operand>> operands_ = {
  {x64asm::Type::RH, {x64asm::Constants::ah(), x64asm::Constants::bh(), x64asm::Constants::ch(), x64asm::Constants::dh()}},
  {x64asm::Type::R_8, {x64asm::Constants::bl(), x64asm::Constants::cl(), x64asm::Constants::dl()}},
  {x64asm::Type::R_16, {x64asm::Constants::bx(), x64asm::Constants::cx(), x64asm::Constants::dx()}},
  {x64asm::Type::R_32, {x64asm::Constants::ebx(), x64asm::Constants::ecx(), x64asm::Constants::edx()}},
  {x64asm::Type::R_64, {x64asm::Constants::rbx(), x64asm::Constants::rcx(), x64asm::Constants::rdx()}},
  {x64asm::Type::XMM, {x64asm::Constants::xmm1(), x64asm::Constants::xmm2(), x64asm::Constants::xmm3(), x64asm::Constants::xmm4()}},
  {x64asm::Type::YMM, {x64asm::Constants::ymm1(), x64asm::Constants::ymm2(), x64asm::Constants::ymm3(), x64asm::Constants::ymm4()}},
  {x64asm::Type::MM, {x64asm::Constants::mm0(), x64asm::Constants::mm1(), x64asm::Constants::mm2(), x64asm::Constants::mm3()}}
};
std::map<x64asm::Type, int> operands_idx_ = {
};
auto constant = 42;
x64asm::Operand get_next_operand(x64asm::Type t) {
  if (t == x64asm::Type::IMM_8) {
    return x64asm::Imm8(constant);
  }
  if (t == x64asm::Type::IMM_16) {
    return x64asm::Imm16(constant);
  }
  if (t == x64asm::Type::IMM_32) {
    return x64asm::Imm32(constant);
  }
  if (t == x64asm::Type::IMM_64) {
    return x64asm::Imm64(constant);
  }
  if (t == x64asm::Type::AL) {
    return x64asm::Constants::al();
  }
  if (t == x64asm::Type::CL) {
    return x64asm::Constants::cl();
  }
  if (t == x64asm::Type::AX) {
    return x64asm::Constants::ax();
  }
  if (t == x64asm::Type::DX) {
    return x64asm::Constants::dx();
  }
  if (t == x64asm::Type::EAX) {
    return x64asm::Constants::eax();
  }
  if (t == x64asm::Type::RAX) {
    return x64asm::Constants::rax();
  }
  if (t == x64asm::Type::XMM_0) {
    return x64asm::Constants::xmm0();
  }
  if (t == x64asm::Type::ZERO) {
    return x64asm::Constants::zero();
  }
  if (t == x64asm::Type::ONE) {
    return x64asm::Constants::one();
  }
  if (t == x64asm::Type::THREE) {
    return x64asm::Constants::three();
  }
  if (operands_.find(t) == operands_.end()) {
    std::cout << "ERROR: unsupported operand: " << t << std::endl;
    exit(1);
  }
  if (operands_idx_.find(t) == operands_idx_.end()) {
    operands_idx_[t] = 0;
  }
  std::vector<x64asm::Operand> candidates = operands_[t];
  assert((int)operands_[t].size() > operands_idx_[t]);
  operands_idx_[t] += 1;
  // increment other counters, too, so that we don't reuse the same register id multiple times
  if (t == x64asm::Type::R_64) {
    if (operands_idx_.find(x64asm::Type::R_8) == operands_idx_.end())
      operands_idx_[x64asm::Type::R_8] = 0;
    operands_idx_[x64asm::Type::R_8] += 1;
    if (operands_idx_.find(x64asm::Type::R_16) == operands_idx_.end())
      operands_idx_[x64asm::Type::R_16] = 0;
    operands_idx_[x64asm::Type::R_16] += 1;
    if (operands_idx_.find(x64asm::Type::R_32) == operands_idx_.end())
      operands_idx_[x64asm::Type::R_32] = 0;
    operands_idx_[x64asm::Type::R_32] += 1;
  }
  if (t == x64asm::Type::R_32) {
    if (operands_idx_.find(x64asm::Type::R_8) == operands_idx_.end())
      operands_idx_[x64asm::Type::R_8] = 0;
    operands_idx_[x64asm::Type::R_8] += 1;
    if (operands_idx_.find(x64asm::Type::R_16) == operands_idx_.end())
      operands_idx_[x64asm::Type::R_16] = 0;
    operands_idx_[x64asm::Type::R_16] += 1;
  }
  if (t == x64asm::Type::R_16) {
    if (operands_idx_.find(x64asm::Type::R_8) == operands_idx_.end())
      operands_idx_[x64asm::Type::R_8] = 0;
    operands_idx_[x64asm::Type::R_8] += 1;
  }
  if (t == x64asm::Type::YMM) {
    if (operands_idx_.find(x64asm::Type::XMM) == operands_idx_.end())
      operands_idx_[x64asm::Type::XMM] = 0;
    operands_idx_[x64asm::Type::XMM] += 1;
  }
  return operands_[t][operands_idx_[t] - 1];
}

x64asm::Instruction get_instruction(x64asm::Opcode opc) {
  operands_idx_ = {};
  x64asm::Instruction instr(opc);

  // special case for shld/shrd (versions with cl register)
  if (opc == SHLD_R16_R16_CL) {
    instr.set_operand(0, Constants::bx());
    instr.set_operand(1, Constants::dx());
    instr.set_operand(2, Constants::cl());
  } else if (opc == SHLD_R32_R32_CL) {
    instr.set_operand(0, Constants::ebx());
    instr.set_operand(1, Constants::edx());
    instr.set_operand(2, Constants::cl());
  } else if (opc == SHLD_R64_R64_CL) {
    instr.set_operand(0, Constants::rbx());
    instr.set_operand(1, Constants::rdx());
    instr.set_operand(2, Constants::cl());
  } else if (opc == SHRD_R16_R16_CL) {
    instr.set_operand(0, Constants::bx());
    instr.set_operand(1, Constants::dx());
    instr.set_operand(2, Constants::cl());
  } else if (opc == SHRD_R32_R32_CL) {
    instr.set_operand(0, Constants::ebx());
    instr.set_operand(1, Constants::edx());
    instr.set_operand(2, Constants::cl());
  } else if (opc == SHRD_R64_R64_CL) {
    instr.set_operand(0, Constants::rbx());
    instr.set_operand(1, Constants::rdx());
    instr.set_operand(2, Constants::cl());
  }

  // special case for mulb/divb/idivb/imulb
  else if (opc == IMUL_RH) {
    instr.set_operand(0, Constants::bh());
  } else if (opc == MUL_RH) {
    instr.set_operand(0, Constants::bh());
  } else if (opc == IDIV_RH) {
    instr.set_operand(0, Constants::bh());
  } else if (opc == DIV_RH) {
    instr.set_operand(0, Constants::bh());
  }

  // special case for cmpxchg with an RH register
  else if (opc == CMPXCHG_R8_RH) {
    instr.set_operand(0, Constants::cl());
    instr.set_operand(1, Constants::bh());
  } else if (opc == CMPXCHG_RH_RH) {
    instr.set_operand(0, Constants::bh());
    instr.set_operand(1, Constants::ch());
  } else if (opc == CMPXCHG_RH_R8) {
    instr.set_operand(0, Constants::bh());
    instr.set_operand(1, Constants::cl());
  }

  // special case for mulx
  else if (opc == MULX_R32_R32_R32) {
    instr.set_operand(0, Constants::eax());
    instr.set_operand(1, Constants::ebx());
    instr.set_operand(2, Constants::ecx());
  }
  else if (opc == MULX_R64_R64_R64) {
    instr.set_operand(0, Constants::rax());
    instr.set_operand(1, Constants::rbx());
    instr.set_operand(2, Constants::rcx());
  }

  // normal case
  else {
    for (size_t i = 0; i < instr.arity(); i++) {
      auto t = instr.type(i);
      instr.set_operand(i, get_next_operand(t));
    }
  }

  if (!instr.check()) {
    std::cout << "instruction not valid:" << instr << std::endl;
    exit(1);
  }
  return instr;
}


bool instr_uses_label(const x64asm::Opcode& opcode) {
  Instruction instr(opcode);
  for (size_t i = 0; i < instr.arity(); i++) {
    switch (instr.type(i)) {
    case Type::LABEL:
      return true;
    default:
      break;
    }
  }
  return false;
}

bool instr_uses_memory(const x64asm::Opcode& opcode) {
  Instruction instr(opcode);
  for (size_t i = 0; i < instr.arity(); i++) {
    switch (instr.type(i)) {
    case Type::M_8:
    case Type::M_16:
    case Type::M_32:
    case Type::M_64:
    case Type::M_128:
    case Type::M_256:
    case Type::M_16_INT:
    case Type::M_32_INT:
    case Type::M_64_INT:
    case Type::M_32_FP:
    case Type::M_64_FP:
    case Type::M_80_FP:
    case Type::M_80_BCD:
    case Type::M_2_BYTE:
    case Type::M_28_BYTE:
    case Type::M_108_BYTE:
    case Type::M_512_BYTE:
    case Type::FAR:
    case Type::PREF_REX_W:
    case Type::FAR_PTR_16_16:
    case Type::FAR_PTR_16_32:
    case Type::FAR_PTR_16_64:
    case Type::REL_32:
    case Type::REL_8:
    case Type::SREG:
    case Type::FS:
    case Type::GS:
    case Type::ST:
    case Type::ST_0:
    case Type::PREF_66:
    case Type::MOFFS_8:
    case Type::MOFFS_16:
    case Type::MOFFS_32:
    case Type::MOFFS_64:
      return true;
    default:
      break;
    }
  }
  return false;
}

// IMM_8,
// IMM_16,
// R_8,
// RH,
// AL,
// CL,
// R_16,
// AX,
// DX,
// R_32,
// EAX,
// MM,
// XMM,
// XMM_0,
// YMM

bool want_to_handle(const x64asm::Opcode& opcode, bool lessbits) {
  Instruction instr(opcode);
  for (size_t i = 0; i < instr.arity(); i++) {
    switch (instr.type(i)) {
    case Type::EAX:
    case Type::R_32:
    case Type::IMM_32:
    case Type::ZERO:
    case Type::ONE:
    case Type::THREE:
      break;
    case Type::IMM_8:
    case Type::IMM_16:
    case Type::R_8:
    case Type::RH:
    case Type::AL:
    case Type::CL:
    case Type::R_16:
    case Type::AX:
    case Type::DX:
      if (lessbits) break;
      return false;
    default:
      return false;
    }
  }
  return true;
}


int main(int argc, char** argv) {

  CommandLineConfig::strict_with_convenience(argc, argv);
  DebugHandler::install_sigsegv();
  DebugHandler::install_sigill();

  ComboHandler ch;

  cout << "#!/usr/bin/env bash" << endl << endl;

  cout << "compare=/x86sem/src/racket/compare.rkt" << endl << endl;

  for (size_t i = 1; i < X64ASM_NUM_OPCODES; ++i) {
    Opcode opcode = (Opcode)i;

    if (instr_uses_memory(opcode)) continue; // ignore memory for now
    if (instr_uses_label(opcode)) continue; // ignore labels

    // we ignore some more instructions for now
    if (!want_to_handle(opcode, arg_lessbits)) continue;

    Instruction instr = get_instruction(opcode);

    if (instr.is_memory_dereference()) continue; // also ignore implicit memory uses

    if (ch.get_support(instr) == Handler::SupportLevel::NONE) {
      // skip instructions we don't have a formula for in STOKE
      continue;
    }

    // Assembler assm;
    // Function f;
    // assm.start(f);
    // assm.assemble(instr);

    // cout << "$compare '" << instr << "'" << endl;

    cout << "$compare '" << instr << "' '" << opcode_write_intel(opcode) << "'" << endl;
    // cout << "  assembled instruction:";
    // uint8_t* data = (uint8_t*) f.data();
    // for (size_t i = 0; i < f.size(); i++) {
    //   cout << " " << setfill('0') << setw(2) << hex << (uint32_t)data[i];
    // }
    // cout << endl;
  }

  return 0;
}
