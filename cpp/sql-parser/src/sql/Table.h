#ifndef __SQLPARSER__TABLEREF_H__
#define __SQLPARSER__TABLEREF_H__

#include "Expr.h"
#include <stdio.h>
#include <vector>

namespace hsql {

  struct SelectStatement;
  struct JoinDefinition;
  struct DiffDefinition;
  struct TableRef;

  // Possible table reference types.
  enum TableRefType {
    kTableDiff,
    kTableName,
    kTableSelect,
    kTableJoin,
    kTableCrossProduct
  };

  // Holds reference to tables. Can be either table names or a select statement.
  struct TableRef {
    TableRef(TableRefType type);
    virtual ~TableRef();

    TableRefType type;

    char* schema;
    char* name;
    char* alias;

    SelectStatement* select;
    std::vector<TableRef*>* list;
    JoinDefinition* join;
    DiffDefinition* diff;

    // Returns true if a schema is set.
    bool hasSchema() const;

    // Returns the alias, if it is set. Otherwise the name.
    const char* getName() const;
  };

  // Possible types of joins.
  enum JoinType {
    kJoinInner,
    kJoinOuter,
    kJoinLeft,
    kJoinRight,
    kJoinLeftOuter,
    kJoinRightOuter,
    kJoinCross,
    kJoinNatural
  };

  // Definition of a join construct.
  struct JoinDefinition {
    JoinDefinition();
    virtual ~JoinDefinition();

    TableRef* left;
    TableRef* right;
    Expr* condition;

    JoinType type;
  };

  struct DiffDefinition {
    DiffDefinition();
    virtual ~DiffDefinition();

    TableRef* first;
    TableRef* second;
    std::vector<Expr*>* attribute_cols;
    Expr* compare_by;
    Expr* max_combo;
  };

} // namespace hsql
#endif
