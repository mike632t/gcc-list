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
 * 24 May 25  0.3  005 - Made list routines 'generic' using separate helper
 *                       functions to compare different data types or print
 *                       the values (not unlike the qsort() function)- MT
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    void  *data;
    struct node *next;
};

typedef struct node node;

int i_cmpint(const void *h_left, const void *h_right)
{
   int i_left = *(int *)h_left;
   int i_right = *(int *)h_right;
   return (i_left > i_right) - (i_left < i_right);
}

int i_cmpnum(const void *h_left, const void *h_right)
{
   double i_left = *(double *)h_left;
   double i_right = *(double *)h_right;
   return (i_left > i_right) - (i_left < i_right);
}

int i_cmpstr(const void *h_left, const void *h_right)
{
   return strcmp((char *)h_left, (char *)h_right);
}

void v_prtint(void *v_data) {
   printf(" %d", *(int *)v_data);
}

void v_prtnum(void *v_data) {
   printf(" %.5f", *(double *)v_data);
}

void v_prtstr(void *v_data) {
   printf(" %s", (char *)v_data);
}

node *h_new(void *h_data, size_t t_size) /* Create a new node */
{
   node *h_node;
   h_node = (node*)malloc(sizeof(*h_node));
   h_node->data = malloc(t_size);
   memcpy(h_node->data, h_data, t_size);
   h_node->next = NULL;
   return h_node;
}

node *h_prepend(node *h_list, void *h_data, size_t t_size) /* Insert item at head of list */
{
   node *h_node = h_new(h_data, t_size); /* Create node */
   h_node->next = h_list;
   return h_node;
}

node *h_append(node *h_list, void *h_data, size_t t_size) /* Append item to list */
{
   if (h_list != NULL)
      h_list->next = h_append(h_list->next, h_data, t_size);
   else
      h_list = h_new(h_data, t_size); /* Create node */
   return h_list;
}

node* h_insert(node *h_list, void *h_data, size_t t_size, int (*v_compare)(const void *, const void *)) /* Insert item into list */
{
   if (h_list != NULL)
   {
      if ((v_compare(h_list->data, h_data)) > 0) 
         h_list = h_prepend(h_list, h_data, t_size);
      else
         h_list->next = h_insert(h_list->next, h_data, t_size, v_compare);
   }
   else
   {
      h_list = h_new(h_data, t_size); /* Create node */
   }
   return h_list;
}

void v_print(node *h_list, void (*v_helper)(void *)) /* Print list */
{
    while (h_list != NULL)
    {
        (*v_helper)(h_list->data);
        h_list = h_list->next;
    }
    printf("\n");
}

int main() {

   node *h_list;

   int i_size;
   size_t t_size;

   int i_values[] =  { 5, 1, 3, 8, 4, 9, 6, 2, 7 };
   double f_values[] = {1.61803, 1.73205, 3.14159, 2.71828, 1.41421};
   char *s_values[] = {"one", "two", "three"};

   /** Create a (sorted) list of integers */
   h_list = NULL; /* An empty list! */
   t_size = sizeof(i_values[0]);
   i_size = sizeof(i_values) / t_size;
   for (int i_count = 0; i_count < i_size; ++i_count)
      h_list = h_insert(h_list, &i_values[i_count], t_size, i_cmpint); /* Insert in order */

   i_values[0] = 0; /* Overwriting previous value in the array to demonstrate that the value is stored in the list */
   h_list = h_append(h_list, &i_values[0], t_size); /* Append to list */
   v_print(h_list, v_prtint); /* Print list */

   /** Create a (sorted) list of floats */
   h_list = NULL; /* An empty list! */
   t_size = sizeof(f_values[0]);
   i_size = sizeof(f_values) / t_size;
   for (int i_count = 1; i_count < i_size; ++i_count)
      h_list = h_insert(h_list, &f_values[i_count], t_size, i_cmpnum);

   h_list = h_append(h_list, &f_values[0], t_size);
   v_print(h_list, v_prtnum);

   /** Create a list of strings */
   h_list = NULL; /* An empty list! */
   i_size = sizeof(s_values) / sizeof(s_values[0]);
   for (int i_count = 1 ; i_count < i_size; ++i_count)
      h_list = h_append(h_list, s_values[i_count], strlen(s_values[i_count]));

   h_list = h_insert(h_list, s_values[0], strlen(s_values[0]), i_cmpstr); /* Insert in order */
   s_values[0] = "testing";
   h_list = h_prepend(h_list, s_values[0], strlen(s_values[0])); /* Prepend to list */
   h_list = h_prepend(h_list, s_values[0], strlen(s_values[0]));
   v_print(h_list, v_prtstr);

   return 0;
}
