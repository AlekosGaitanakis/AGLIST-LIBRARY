#include "aglist.h"

BEGIN
  AGLIST* aglist = NULL;
  INIT(&aglist);
  INSERT_START(&aglist, 5);
  INSERT_START(&aglist, 4);
  INSERT_END(&aglist, 3);
  SORT_LIST(&aglist);
  INSERT_AT_SORTED(&aglist, 6);
  INSERT_AT_SORTED(&aglist, 4);
  INSERT_AT_SORTED(&aglist, 1);
  SORT_LIST(&aglist);

  PRINT_LIST(aglist);
  FREE_LIST(&aglist);
END
