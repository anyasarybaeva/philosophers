#include"philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	num;
	char		c;

	c = '+';
	i = 0;
	num = 0;
	while (str[i] == 32 || str[i] == '\n' || str[i] == '\t' || \
		   	str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		c = str[i++];
	while (str[i] >= 48 && str[i] <= 57 && i < 12)
		num = num * 10 + str[i++] - 48;
	if (num > 2147483647)
		return (-1);
	if (c == '-')
		return (num * (-1));
	else
		return (num);
}
