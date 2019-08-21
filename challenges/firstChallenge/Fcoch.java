import java.lang.Math;
import java.util.Scanner;

public class Fcoch {
  /*
    * This function returns the length of the longest substring without repeating characters.
    * Recive a string and return a integer value.
  */
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
  /*
    * Main method
  */
  public static void main(String[] args) {
    String word;
    System.out.print("Input: ");
    Scanner sc = new Scanner(System.in);
    word = sc.nextLine();
    int length = longestSubStr(word);
    System.out.println("Output: " + length);
  }
}
