/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 20:19:08 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/02 15:11:17 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int exit_status = 0;
	if (argv[1])
		exit_status = atoi(argv[1]);

	printf("test_exec running with exit status %d..\n", exit_status);

	return exit_status;
}
