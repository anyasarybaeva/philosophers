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
	{
		c = str[i];
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	if (c == '-')
		return (num * (-1));
	else
		return (num);
}
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		ft_putchar_fd(s[i++], 0);
	ft_putchar_fd('\n',0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n = n * (-1);
			write(fd, "-", 1);
		}
		if (n < 10)
		{
			str = (char)(48 + n);
			write(fd, &str, 1);
		}
		else
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
	}
}
