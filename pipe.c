/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:23:44 by vipereir          #+#    #+#             */
/*   Updated: 2023/01/04 14:41:47 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main (void)
{
	int	id;
	int	id2;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (2);
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
			exit(1);
	}
	else
	{
		int	wstatus;
		wait(&wstatus);
		id2 = fork();
		if (id2 == -1)
			return (1);
		if (id2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			int err = execlp("grep", "grep", "min", NULL);
		}
		else (wait(NULL));
	}
	return (0);
}
