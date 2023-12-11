#include "shell.h"

/**
 * big_ups - big_ups function concatenates the message for cd error
 * @dsh: data
 * @message: message to be printed
 * @o: output message
 * @d_s: counter lines
 * Return: error message
 */
char *big_ups(shell_shell *dsh, char *message, char *o, char *d_s)
{
	char *awful_flag;
	dup_string(o, dsh->ichi[0]);
	concate(o, ": ");
	concate(o, d_s);
	concate(o, ": ");
	concate(o, dsh->args[0]);
	concate(o, message);
	if (dsh->args[1][0] == '-')
	{
		awful_flag = malloc(3);
		awful_flag[0] = '-';
		awful_flag[1] = dsh->args[1][1];
		awful_flag[2] = '\0';
		concate(o, awful_flag);
		free(awful_flag);
	}
	else
	{
		concate(o, dsh->args[1]);
	}
	
	concate(o, "\n");
	concate(o, "\0");
	return (o);
}

/**
 * errorMessage_cd - errorMessage_cd is the function error
 * message for cd command in get_cd
 * @dsh: data
 * Return: Error message
 *
 */
char *errorMessage_cd(shell_shell *dsh)
{
	int lat, lat_id;
	char *o, *d_s, *message;
	
	d_s = int_toString(dsh->counter);
	if (dsh->args[1][0] == '-')
	{
		message = ": Bad option ";
		lat_id = 2;
	}
	else
	{
		message = ": There is no such file or directory ";
		lat_id = (dsh->args[1]);
	}
	lat = string_length(dsh->ichi[0]) + string_length(dsh->args[0]);
	lat += string_length(d_s) + string_length(message) + lat_id + 5;
	o = malloc(sizeof(char) * (lat + 1));
	if (o == NULL)
	{
		free(d_s);
		return (NULL);
	}
	
	o = big_ups(dsh, message, o, d_s);
	
	free(d_s);
	
	return (o);
}


/**
 * generic_messages - generic_messages function generates generic
 * error message for command not found
 * @dsh: data
 * Return: Error message
 */
char *generic_messages(shell_shell *dsh)
{
	int lat;
	char *o;
	char *d_s;
	d_s = int_toString(dsh->counter);
	lat = string_length(dsh->ichi[0]) + string_length(d_s);
	lat += string_length(dsh->args[0]) + 16;
	o = malloc(sizeof(char) * (lat + 1));
	while (o == 0)
	{
		free(o);
		free(d_s);
		return (NULL);
	}
	dup_string(o, dsh->ichi[0]);
	concate(o, ": ");
	concate(o, d_s);
	concate(o, ": ");
	concate(o, dsh->args[0]);
	concate(o, ": not found\n");
	concate(o, "\0");
	free(d_s);
	return (o);
}

/**
 * exit_get - This function generic error message for exit in get_exit
 * @dsh: data
 * Return: Error message
 */
char *exit_get(shell_shell *dsh)
{
	int lat;
	char *o;
	char *d_s;
	
	d_s = int_toString(dsh->counter);
	lat = string_length(dsh->ichi[0]) + string_length(d_s);
	lat += string_length(dsh->args[0]) + string_length(dsh->args[1]) + 23;
	o = malloc(sizeof(char) * (lat + 1));
	while (o == 0)
	{
		free(d_s);
		return (NULL);
	}
	dup_string(o, dsh->ichi[0]);
	concate(o, ": ");
	concate(o, d_s);
	concate(o, ": ");
	concate(o, dsh->args[0]);
	concate(o, ": Bad number: ");
	concate(o, dsh->args[1]);concate(o, "\n\0");
	free(d_s);
	
	return (o);
}