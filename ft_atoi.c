# include "philosophers.h"


int	ft_atoi(char *str)
{
	int		i;
	int		symbol;
	int     outcome;

	i = 0;
	symbol = 1;
	outcome = 0;
	if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return(-1);
		if (str[i] == '-')
			return(-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		outcome = outcome * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' || (outcome * symbol == 0))
		return(-1);
	return (outcome * symbol);
}
