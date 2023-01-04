/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-two-way.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:25:06 by vipereir          #+#    #+#             */
/*   Updated: 2023/01/04 10:29:48 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	main (void)
{
	// 5 => 5 * 4 = 20 => 20
	//	fd[0] read
	//	fd[1] write
	int	fd1[2];  // c -> p
	int	fd2[2];  // p -> c
	int	id;

	if (pipe(fd1) == -1)
		return (1);
	if (pipe(fd2) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (3);
	if (id == 0)
	{
		close(fd1[0]);
		close(fd2[1]);
		int	c;
		read(fd2[0], &c, sizeof(int));
		printf("recived : %i\n", c);
		c *= 4;
		write(fd1[1], &c, sizeof(int));
		close(fd2[0]);
		close(fd1[1]);
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);
		int	x;
		x = 5;
		write(fd2[1], &x, sizeof(int));
		read(fd1[0], &x, sizeof(int));
		printf("output: %i\n", x);
		close(fd1[0]);
		close(fd2[1]);
	}
	return (0);
}
