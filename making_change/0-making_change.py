def makeChange(coins, total):
    """
    Return the fewest number of coins needed to meet 'total' using an
    infinite supply of the given coin denominations.
    - coins: list[int] of positive integers
    - total: int
    """
    # Trivial cases
    if total <= 0:
        return 0
    if not coins:
        return -1

    # Filter out coins larger than total and remove duplicates
    coins = sorted(set(c for c in coins if 0 < c <= total))
    if not coins:
        return -1

    # Large sentinel (larger than any possible coin count)
    INF = total + 1

    # dp[x] = min coins to make sum x
    dp = [INF] * (total + 1)
    dp[0] = 0

    # Unbounded knapsack (min coins)
    for c in coins:
        for x in range(c, total + 1):
            # If we can make (x - c), try taking coin c once more
            if dp[x - c] + 1 < dp[x]:
                dp[x] = dp[x - c] + 1

    return dp[total] if dp[total] != INF else -1
