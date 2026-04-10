/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/13 19:06:08 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/13 19:06:08 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!lst || !new)
		return ;
	last_node = ft_lstlast(*lst);
	if (last_node == NULL)
		*lst = new;
	else
		last_node->next = new;
}
