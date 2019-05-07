/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:34:22 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/07 10:44:36 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <lem_in_bug.h>
#include "../libft/libft.h"

uint8_t				ft_puterror(char const *str, char const *err)
{
	ft_putstr(C_RED);
	ft_putnstr(str, 20);
	ft_putstr(C_NONE);
	printf("\t<- %s\n", err);
	return (EXIT_FAILURE);
}
