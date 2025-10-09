def isWinner(x, nums):
    """
    Determine the winner of each round of the prime game and
    return the name of the player with the most total wins.

    Args:
        x (int): number of rounds
        nums (List[int]): list of n values per round

    Returns:
        str or None: "Maria", "Ben", or None if tie/undetermined
    """
    # Basic guards
    if not x or not nums:
        return None

    # Use only the first x rounds, per problem statement
    rounds = nums[:x]
    max_n = 0
    for n in rounds:
        if n > max_n:
            max_n = n

    if max_n < 2:
        # No primes in any round; Ben wins all (or tie if all n<2 but x>0)
        # Evaluate properly to handle possible ties.
        maria_wins = 0
        ben_wins = len(rounds)
        if maria_wins > ben_wins:
            return "Maria"
        if ben_wins > maria_wins:
            return "Ben"
        return None

    # Sieve of Eratosthenes up to max_n
    is_prime = [True] * (max_n + 1)
    is_prime[0] = False
    if max_n >= 1:
        is_prime[1] = False

    p = 2
    while p * p <= max_n:
        if is_prime[p]:
            step = p
            start = p * p
            for multiple in range(start, max_n + 1, step):
                is_prime[multiple] = False
        p += 1

    # Prefix count of primes
    prime_count = [0] * (max_n + 1)
    running = 0
    for i in range(2, max_n + 1):
        if is_prime[i]:
            running += 1
        prime_count[i] = running

    # Tally wins
    maria = 0
    ben = 0
    for n in rounds:
        # If no primes up to n, Ben wins (Maria can't move)
        if prime_count[n] % 2 == 1:
            maria += 1
        else:
            ben += 1

    if maria > ben:
        return "Maria"
    if ben > maria:
        return "Ben"
    return None
