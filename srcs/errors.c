/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:34:22 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 14:27:33 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/lem_in_bug.h"

uint8_t				ft_puterror(char const *str, char const *err)
{
	ft_putstr(C_RED);
	ft_putnstr(str, 20);
	ft_putstr(C_NONE);
	printf("\t<- %s\n", err);
	return (EXIT_FAILURE);
}
