/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mada <kel-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:45:50 by kel-mada          #+#    #+#             */
/*   Updated: 2025/11/22 17:02:05 by kel-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_cd(char *path)
{
	if (chdir(path) == -1) // changes directory of THE CURRENT PROCESS
		return (0);
	return (1);
}
// check it wont make issues when forking and different processes happen
// like when using pipes