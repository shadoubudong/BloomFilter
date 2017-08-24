#ifndef HASH_FUN_H_
#define HASH_FUN_H_

size_t BKDRHash(const char *str)
{
	size_t seed = 131;
	size_t hash = 0;

	while (*str != '\0')
		hash = hash*seed + (*str++);

	return (hash & 0x7FFFFFFF);
}

size_t SDBMHash(const char *str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = 65599 * hash + ch;
	}
	return hash;
}

size_t RSHash(const char *str)
{
	register size_t hash = 0;
	size_t magic = 63689;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * magic + ch;
		magic *= 378551;
	}
	return hash;
}

size_t APHash(const char *str)
{
	register size_t hash = 0;
	size_t ch;
	for (long i = 0; ch = (size_t)*str++; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
		}
	}
	return hash;
}

size_t JSHash(const char *str)
{
	if (!*str)
		return 0;

	register size_t hash = 1315423911;
	while (size_t ch = (size_t)*str++)
	{
		hash ^= ((hash << 5) + ch + (hash >> 2));
	}
	return hash;
}

#endif // HASH_FUN_H_
