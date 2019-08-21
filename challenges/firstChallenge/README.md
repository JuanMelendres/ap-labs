First Code Challenge
====================

Given a string, find the length of the longest substring without repeating characters.

Example 1
---------
```
Input: "abcabcbb"
Output: 3
```

**Explanation:** The answer is `abc`, with the length of 3.


Example 2:
----------
```
Input: "bbbbb"
Output: 1
```

**Explanation:** The answer is `b`, with the length of 1.


Example 3:
----------
```
Input: "pwwkew"
Output: 3
```
**Explanation:** The answer is `wke`, with the length of 3.
Note that the answer must be a substring, `pwke` is a subsequence and not a substring.


Build Requirements
------------------
```
Java 8
  Any bash or command line
```


How to build
------------
```
  Here is the main function that returns the length of the longest substring.
  public static int longestSubStr(String a) {
    boolean[] flag = new boolean[256];
    int rest = 0; // Result value
    int aux = 0; // auxiliar for operations
    char[] arr = a.toCharArray();
    if (a != null) {
      for (int i = 0; i < arr.length; i++) {
        char current = arr[i];
        if (flag[current]) {
          rest = Math.max(rest, i - aux);
          for (int k = aux; k < i; k++) {
            if (arr[k] == current) {
              aux = k + 1;
              break;
            }
            flag[arr[k]] = false;
          }
        }
        else {
          flag[current] = true;
        }
      }
      rest = Math.max(arr.length - aux, rest);
      return rest;
    }
    return 0;
  }
```


How to Run
----------
```
  Execute the .java file in any command line
    javac name_of_file.java
    java name_of_file
```


General instructions
--------------------
1. Don't forget to do a `pull --rebase origin master` before anything.
2. Submit your code to your personal fork.
3. Don't forget to update this `README.md` file with your project's `requirements`, `build` and `how to run` sections.
4. Have fun and don't forget the next section.
