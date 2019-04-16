/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_hash.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:22:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/16 15:08:30 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_HASH_H
# define LEM_IN_HASH_H

# define MULTIPLIER			37

uint64_t					hash(const char *s);
uint64_t					hashn(const char *s, int size);

#endif
