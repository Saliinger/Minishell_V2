#include "../../../include/minishell.h"

char *get_name(char *s)
{
    int i = 0;
    int start = 0;
    int end = 0;
    char *name;

	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
    start = i;
    while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
    end = i - start + 1;
    name = (char *) malloc(sizeof(char) * end + 1);
    ft_strlcpy(name,s + start, end);
    return (name);
}

char *tiny_expand(char *s, t_minishell *minishell)
{
    char *res;
    char *name;
    t_export_list *var;

    if (*s == '$')
    {
        name = get_name(s);
        var = find_export_node(name + 1, minishell->exportList);
        if (!var || !var->value)
        {
            res = ft_strdup(s + ft_strlen(name));
            free(s);
            free(name);
            return (res);
        }
        res = ft_strdup(var->value);
        res = ft_strjoin_frees1(res, s + ft_strlen(name));
    }
    else
        return (s);
    free(name);
    free(s);
    return (res);
}