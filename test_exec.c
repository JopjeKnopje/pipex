/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 20:19:08 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/03 17:06:12 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

int main(int argc, char *argv[])
{
	int exit_status = 0;
	if (ft_strnstr(argv[1], "seg", strlen("seg")))
	{
		printf("forcing segfault\n");
		char *s = "a";
		s[2] = 'a';
	}
	else
		exit_status = atoi(argv[1]);


	printf("test_exec running with exit status %d..\n", exit_status);
	return exit_status;
}
