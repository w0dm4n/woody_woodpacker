/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 05:28:32 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/07 05:33:20 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_add_in(char *buffer, char *toadd, int oct, int i)
{
	int			new_len;
	char		*tmp;

	if (!buffer || buffer == NULL)
		buffer = (char*)malloc(sizeof(char));
	new_len = (ft_strlen(buffer) + ft_strlen(toadd));
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(buffer) + 1))))
		return (NULL);
	while (buffer[i])
	{
		tmp[i] = buffer[i];
		i++;
	}
	tmp[i] = '\0';
	i = 0;
	if (!(buffer = (char*)malloc(sizeof(char) * (new_len + 1))))
		return (NULL);
	buffer = ft_strcat(buffer, tmp);
	buffer = ft_strncat(buffer, toadd, oct);
	free(tmp);
	return (buffer);
}
