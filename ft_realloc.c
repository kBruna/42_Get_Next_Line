# include "get_next_line.h"
# include <stdio.h>

t_link	*ft_realloc(t_link *buffer)
{
	int		ctrl;
	int		index;
	char	*p;

	ctrl = 0;
	p = buffer->content;
	while (p && p[ctrl] != '\n' && p[ctrl] != '\0')
		ctrl++;
	if (p[ctrl] == '\0')
	{
		buffer = buffer->next;
		//ft_get_clean(buffer->prev);
		return (buffer);
	}
	index = 0;
	ctrl++;
	while (p && p[ctrl] != '\n' && p[ctrl] != '\0')
	{
		buffer->content[index] = p[ctrl];
		ctrl++;
	}
	buffer->content[index] = '\0';
	if (index == 0)
		buffer = buffer->next;
	return (buffer);
}

int	main(void)
{
	t_link *s;

	s = malloc(sizeof(t_link));
	if (!s)
		return (1);
	s->content = malloc(sizeof(char) * 15);
	if (!s->content)
		return (1);
	s->next = NULL;
	s->prev = NULL;
	s->content = "Teste1\nTeste2";
	printf("Entrada: \t%s\n", s->content);
	s = ft_realloc(s);
	printf("Saida: \t%s\n", s->content);
	free(s->content);
	free(s);

	return (0);
}