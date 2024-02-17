/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwywijas <uwywijas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:07:44 by uwywijas          #+#    #+#             */
/*   Updated: 2024/02/17 15:38:12 by uwywijas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	philosophers(argc, argv);
	return (0);
}
