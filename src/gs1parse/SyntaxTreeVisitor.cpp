#include <gs1/parse/SyntaxTree.hpp>

using namespace gs1;

// --------------------------------------------------
// Core syntax tree structure
// --------------------------------------------------

void SyntaxTreeVisitor::Visit(SyntaxNodeOrTerminal *node) {}

void SyntaxTreeVisitor::Visit(SyntaxNode *node)
{
  Visit((SyntaxNodeOrTerminal *)node);

  for (auto child : node->children) {
    child->Accept(this);
  }
}

void SyntaxTreeVisitor::Visit(SyntaxTerminal *node)
{
  Visit((SyntaxNodeOrTerminal *)node);
}

// --------------------------------------------------
// Statements
// --------------------------------------------------

void SyntaxTreeVisitor::Visit(Stmt *node) { Visit((SyntaxNode *)node); }

void SyntaxTreeVisitor::Visit(StmtEmpty *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtBlock *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtIf *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtFor *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtWhile *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtBreak *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtContinue *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtReturn *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtCommand *node) { Visit((Stmt *)node); }

void SyntaxTreeVisitor::Visit(StmtFunctionDecl *node) { Visit((Stmt *)node); }

// --------------------------------------------------
// Expressions
// --------------------------------------------------

void SyntaxTreeVisitor::Visit(Expr *node) { Visit((SyntaxNode *)node); }

void SyntaxTreeVisitor::Visit(ExprId *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprNumberLiteral *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprStringLiteral *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprList *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprRange *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprUnaryOp *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprBinaryOp *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprTernaryOp *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprIndex *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprIndexDotLookup *node) { Visit((Expr *)node); }

void SyntaxTreeVisitor::Visit(ExprCall *node) { Visit((Expr *)node); }
