/*
 *
 * gcc-list.c
 *
 * Copyright(C) 2025   MEJT
 *
 * Creates a linked list structure.  
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * 23 May 25  0.1  001 - Initial version - MT
 *                 002 - Items can be inserted into the list in order - MT
 *            0.2  003 - Create list using strings - MT
 *                 004 - Allocates storage for each string and saves a copy
 *                       of the data with each node - MT
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *data;
    struct node *next;
};

typedef struct node node;

node *h_new(char *s_data) /* Create a new node */
{
   node *h_node;
   h_node = (node*)malloc(sizeof(*h_node));
   h_node->data = malloc(strlen(s_data)); /* Allocates storage for string */
   memcpy(h_node->data, s_data, strlen(s_data)); /* and copies it to node */ 
   h_node->next = NULL;
   return h_node;
}

node *h_prepend(node *h_list, char *s_data) /* Prepend item to list */
{
   node *h_node = h_new(s_data);
   h_node->next = h_list;
   return h_node;
}

node *h_append(node *h_list, char *s_data) /* Append item to list */
{
   if (h_list != NULL)
      h_list->next = h_append(h_list->next, s_data);
   else
      h_list = h_new(s_data);
   return h_list;
}

node* h_insert(node *h_list, char *s_data) /* Insert item into list */
{
   if (h_list != NULL)
   {
      if (strcmp(h_list->data, s_data) > 0) 
         h_list = h_prepend(h_list, s_data);
      else
         h_list->next = h_insert(h_list->next, s_data);
   }
   else
   {
      h_list = h_new(s_data);
   }
   return h_list;
}

void v_print(node *h_list) /* Print list */
{
    while (h_list != NULL)
    {
        printf(" %s", h_list->data);
        h_list = h_list->next;
    }
    printf("\n");
}

int main()
{
   node *h_list;

   int i_size;
   size_t t_size;

   char *s_values[] = { "William", "Michael", "Lisa", "John", "Mary",
                        "David", "James", "Karen", "Robert", "Linda",
                        "Mark",  "Patricia", "Deborah", "Richard",
                        "Elizabeth" };

   h_list = NULL; /* An empty list! */
   t_size = sizeof(s_values[0]);
   i_size = sizeof(s_values) / t_size;
   for (int i_count = 1; i_count < i_size; ++i_count)
      h_list = h_insert(h_list, s_values[i_count]); /* Insert in order */

   h_list = h_append(h_list, s_values[0]); /* Append to list */
   v_print(h_list); /* Print list */

   return 0;
}
