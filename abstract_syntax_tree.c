/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:47:55 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/09 10:20:31 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct e_root
{
	int data;
	struct e_root *right;
	struct e_root *left;
		
}s_root;

s_root *create_node(int value)
{
	s_root* bin = malloc(sizeof(s_root));
	if (!bin)
		return(NULL);
	bin->data = value;
	bin->left = NULL;
	bin->right = NULL;
	return (bin);
}

s_root *insert_node(s_root *root, int value)
{
	if (root == NULL)
		return create_node(value);

	if (value < root->data)
		root->left = insert_node(root->left, value);
	else
		root->right = insert_node(root->right, value);

	return root;
}

void print_tree(s_root *root)
{
		printf("%d\n",root);
}



int main()
{
	s_root *root = NULL;

	root = insert_node(root, 30);
	print_tree(root);
}  
