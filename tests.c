static char	*read_letter(char *word, char c)
{
	char	letter[2];

	letter[0] = c;
	letter[1] = '\0';
	return (appends(word, letter));
}

char	*read_word(char *input, int *i)
{
	char	*word;
	char	*seg;

	word = malloc(1);
	if (!word)
		return (NULL);
	word[0] = '\0';
	while (input[*i] && !is_operator(input[*i]))
	{
		if (is_quote(input[*i]))
		{
			seg = read_one(input, i);
			if (!seg)
				return (word);
			word = appends(word, seg);
			free(seg);
		}
		else if (!ft_isspace(input[*i]))
		{
			word = read_letter(word, input[*i]);
			(*i)++;
		}
		else
			break ;
	}
	return (word);
}
