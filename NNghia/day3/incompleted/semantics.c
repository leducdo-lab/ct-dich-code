/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

static int on_search = 0;

Object* lookupObject(char *name) {
  // TODO
  Object* object = NULL;
  static Scope* currentScope = NULL;

  if(on_search == 0)
    currentScope = symtab->currentScope;
  
  while (currentScope != NULL)
  {
    object = findObject(currentScope->objList, name);

    currentScope = currentScope->outer;

    on_search = 1;

    if(object != NULL)
      return object;
  }

  object = findObject(symtab->globalObjectList, name);

  on_search = 0;
  return object;
}

void checkFreshIdent(char *name) {
  // TODO
  Object* object = findObject(symtab->currentScope->objList, name);
  if(object != NULL)
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

Object* checkDeclaredIdent(char* name) {
  // TODO
  on_search = 0;

  Object* object = lookupObject(name);

  on_search = 0;

  if(object == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);

  return object;
}

Object* checkDeclaredConstant(char* name) {
  // TODO
  Object* object = NULL;

  on_search = 0;

  do{
    object = lookupObject(name);
    if(object != NULL && object->kind == OBJ_CONSTANT)
      break;
  }while(object != NULL);

  on_search = 0;

  if(object == NULL)
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  
  return object;
}

Object* checkDeclaredType(char* name) {
  // TODO
  Object* object = NULL;
  
  on_search = 0;

  do{
    object = lookupObject(name);
    if(object != NULL && object->kind == OBJ_TYPE)
      break;
  }while(object != NULL);

  on_search = 0;

  if(object == NULL)
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);

  return object;
}

Object* checkDeclaredVariable(char* name) {
  // TODO
  Object* object = NULL;

  on_search = 0;

  do{
    object = lookupObject(name);
    if(object != NULL && object->kind == OBJ_VARIABLE)
      break;
  }while(object != NULL);

  on_search = 0;

  if(object == NULL)
    error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);

  return object;
}

Object* checkDeclaredFunction(char* name) {
  // TODO
  Object* object = NULL;

  on_search = 0;

  do{
    object = lookupObject(name);
    if(object != NULL && object->kind == OBJ_FUNCTION)
      break;
  }while(object != NULL);

  on_search = 0;

  if(object == NULL)
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);

  return object;
}

Object* checkDeclaredProcedure(char* name) {
  // TODO
  Object* object = NULL;

  on_search = 0;

  do
  {
    object = lookupObject(name);
    if(object != NULL && object->kind == OBJ_PROCEDURE)
      break;
  } while (object != NULL);
  
  on_search = 0;

  if(object == NULL)
    error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);

  return object;
}

Object* checkDeclaredLValueIdent(char* name) {
  // TODO
  Object* object = NULL;

  on_search = 0;

  do
  {
    object = lookupObject(name);
    if(object != NULL &&(object->kind == OBJ_PARAMETER || object->kind == OBJ_FUNCTION || object->kind == OBJ_VARIABLE))
      break;
  } while (object != NULL);
  
  on_search = 0;

  if(object == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);

  return object;
}

