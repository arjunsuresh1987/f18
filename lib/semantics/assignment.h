//===-- lib/semantics/assignment.h ------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef FORTRAN_SEMANTICS_ASSIGNMENT_H_
#define FORTRAN_SEMANTICS_ASSIGNMENT_H_

#include "flang/common/indirection.h"
#include "flang/evaluate/expression.h"
#include "flang/semantics/semantics.h"

namespace Fortran::parser {
class ContextualMessages;
struct AssignmentStmt;
struct PointerAssignmentStmt;
struct WhereStmt;
struct WhereConstruct;
}

namespace Fortran::semantics {

class AssignmentContext;
class Scope;
class Symbol;

// Applies checks from C1594(1-2) on definitions in pure subprograms
void CheckDefinabilityInPureScope(parser::ContextualMessages &, const Symbol &,
    const Scope &context, const Scope &pure);
// Applies checks from C1594(5-6) on copying pointers in pure subprograms
void CheckCopyabilityInPureScope(parser::ContextualMessages &,
    const evaluate::Expr<evaluate::SomeType> &, const Scope &);

class AssignmentChecker : public virtual BaseChecker {
public:
  explicit AssignmentChecker(SemanticsContext &);
  ~AssignmentChecker();
  void Enter(const parser::AssignmentStmt &);
  void Enter(const parser::PointerAssignmentStmt &);
  void Enter(const parser::WhereStmt &);
  void Enter(const parser::WhereConstruct &);

private:
  common::Indirection<AssignmentContext> context_;
};

}

extern template class Fortran::common::Indirection<
    Fortran::semantics::AssignmentContext>;
#endif  // FORTRAN_SEMANTICS_ASSIGNMENT_H_
