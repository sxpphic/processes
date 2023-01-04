/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit-status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:42:24 by vipereir          #+#    #+#             */
/*   Updated: 2023/01/04 13:18:14 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../minishell/libft/libft.h"
#include <fcntl.h>

int	main (void)
{
	int	id;

	id = fork();

	char *buff;

	if (id == -1)
		return (1);
	if (id == 0)
	{
		int	err;
		int	file = open("ping_result.log", O_WRONLY | O_CREAT, 0777);
		dup2(file, 1);
		err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
			printf("error finding the program\n");
	}
	else
	{
		int	wstatus;
		wait(&wstatus);
	//	if (wstatus == 0)
		if (WIFEXITED(wstatus))
		{
			int	status_code = WEXITSTATUS(wstatus);
			if (status_code == 0)
				printf("success!\n");
			else
				printf("error: %i\n", EXIT_FAILURE);
		}
	}
	return (0);
}

