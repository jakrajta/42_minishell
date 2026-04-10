/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/13 19:25:43 by jakrajic          #+#    #+#             */
/*   Updated: 2025/06/13 19:25:43 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_temp;

	if (lst == NULL)
		return (NULL);
	lst_temp = lst;
	while (lst_temp->next != NULL)
	{
		lst_temp = lst_temp->next;
	}
	return (lst_temp);
}
