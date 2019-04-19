/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_hash.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:22:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/17 20:33:26 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_HASH_H
# define LEM_IN_HASH_H

# define MULTIPLIER			37

uint32_t					hash(const char *s);
uint32_t					hashn(const char *s, size_t size);

#endif
