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
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int  data;
    struct node *next;
};

typedef struct node node;

node *h_new(int i_data) /* Create a new node */
{
   node *h_node;
   h_node = (node*)malloc(sizeof(*h_node));
   h_node->data = i_data;
   h_node->next = NULL;
   return h_node;
}

node *h_prepend(node *h_list, int i_data) /* Prepend item to list */
{
   node *h_node = h_new(i_data);
   h_node->next = h_list;
   return h_node;
}

node *h_append(node *h_list, int i_data) /* Append item to list */
{
   if (h_list != NULL)
      h_list->next = h_append(h_list->next, i_data);
   else
      h_list = h_new(i_data);
   return h_list;
}

void v_print(node *h_list) /* Print list */
{
    while (h_list != NULL)
    {
        printf(" %d", h_list->data);
        h_list = h_list->next;
    }
    printf("\n");
}

int main()
{
   node *h_list;

   int i_size;
   size_t t_size;

   int i_values[] =  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   
   h_list = NULL; /* An empty list! */
   t_size = sizeof(i_values[0]);
   i_size = sizeof(i_values) / t_size;
   for (int i_count = 1; i_count < i_size; ++i_count)
      h_list = h_append(h_list, i_values[i_count]); /* Append to list */

   h_list = h_prepend(h_list, i_values[0]); /* Prepend to the start of list */
   v_print(h_list); /* Print list */

   return 0;
}
