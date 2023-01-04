/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:58:39 by vipereir          #+#    #+#             */
/*   Updated: 2023/01/04 09:12:26 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int	main(void)
{
	//	fd[0] read;
	//	fd[1] write;
	int fd[2];
	int id;

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (2);
	if (id == 0)
	{
		int	i = 10;
		close(fd[0]);
		write(fd[1], &i, sizeof(int));
		close(fd[1]);
	}
	else
	{
		int	c;
		wait(NULL);
		close(fd[1]);
		read(fd[0], &c, sizeof(int));
		printf("output: %i\n", c);
		close(fd[0]);
	}
	return (0);
}
