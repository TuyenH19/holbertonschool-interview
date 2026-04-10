#!/usr/bin/python3
"""Recursive Reddit keyword counter."""

import json
import urllib.error
import urllib.request


class NoRedirectHandler(urllib.request.HTTPRedirectHandler):
    """Prevent urllib from following redirects."""

    def redirect_request(self, req, fp, code, msg, hdrs, newurl):
        return None

    def http_error_302(self, req, fp, code, msg, hdrs):
        return fp

    def http_error_301(self, req, fp, code, msg, hdrs):
        return fp


def _build_counts(words, counts=None):
    if counts is None:
        counts = {}
    if not words:
        return counts
    word = words[0].lower()
    counts[word] = counts.get(word, 0)
    return _build_counts(words[1:], counts)


def _count_tokens(tokens, counts):
    if not tokens:
        return counts
    token = tokens[0].lower()
    if token in counts:
        counts[token] += 1
    return _count_tokens(tokens[1:], counts)


def _process_children(children, counts):
    if not children:
        return counts
    child = children[0]
    title = child.get('data', {}).get('title', '')
    words = title.split()
    _count_tokens(words, counts)
    return _process_children(children[1:], counts)


def _collect_items(counts, keys=None, collected=None):
    if collected is None:
        collected = []
    if keys is None:
        keys = list(counts.keys())
    if not keys:
        return collected
    key = keys[0]
    value = counts[key]
    if value > 0:
        collected.append((key, value))
    return _collect_items(counts, keys[1:], collected)


def _print_items(items):
    if not items:
        return
    word, value = items[0]
    print(f"{word}: {value}")
    _print_items(items[1:])


def _print_counts(counts):
    items = _collect_items(counts)
    if not items:
        return
    items = sorted(items, key=lambda item: (-item[1], item[0]))
    _print_items(items)


def _fetch_hot(subreddit, after, opener):
    url = f"https://www.reddit.com/r/{subreddit}/hot.json?limit=100"
    if after:
        url += f"&after={after}"
    request = urllib.request.Request(
        url,
        headers={"User-Agent": "holberton:count_words:v1.0 (by /u/holberton)"},
    )
    try:
        response = opener.open(request)
    except urllib.error.HTTPError:
        return None
    code = getattr(response, "getcode", lambda: None)()
    if code is None or 300 <= code < 400:
        return None
    try:
        return json.load(response)
    except (json.JSONDecodeError, ValueError):
        return None


def count_words(subreddit, word_list, after=None, counts=None):
    if counts is None:
        counts = _build_counts(word_list)
    opener = urllib.request.build_opener(NoRedirectHandler)
    response = _fetch_hot(subreddit, after, opener)
    if response is None:
        return None
    data = response.get("data") or {}
    children = data.get("children", [])
    counts = _process_children(children, counts)
    next_after = data.get("after")
    if next_after:
        return count_words(subreddit, word_list, next_after, counts)
    _print_counts(counts)
    return counts


if __name__ == "__main__":
    import sys

    if len(sys.argv) < 3:
        print("Usage: {} <subreddit> <list of keywords>".format(sys.argv[0]))
    else:
        count_words(sys.argv[1], [x for x in sys.argv[2].split()])
