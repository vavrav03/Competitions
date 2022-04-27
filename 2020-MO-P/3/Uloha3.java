/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package P;

import java.util.Random;

/**
 *
 * @author Vavra
 */
public class Uloha3 {

   static class Result {

      int eatenCakes;
      int startingPosition;

      public Result(int eatenCakes, int startingPosition) {
         this.eatenCakes = eatenCakes;
         this.startingPosition = startingPosition;
      }

      @Override
      public String toString() {
         return "{eatenCakes=" + eatenCakes + ", startingPosition=" + startingPosition + '}';
      }
   }

   public static Result maxCakesAndStartingPosition(int[] cakePrices, int money) {
      int lastMaxStartingPosition = 0;
      int currLength = 0;
      int currentSum = 0;
      int i = 0;
      for (; i < cakePrices.length; i++) {
         if ((currentSum + cakePrices[i]) <= money) {
            currentSum += cakePrices[i];
            lastMaxStartingPosition = i - currLength;
            currLength++;
         } else {
            currentSum = currentSum - cakePrices[i - currLength] + cakePrices[i];
         }
      }
      return new Result(currLength, lastMaxStartingPosition + 1); //Pracuji s indexy začínajícími na nule
   }

   static int[] milionArray() {
      Random random = new Random();
      int[] array = new int[1_000_000];
      for (int i = 0; i < array.length; i++) {
         array[i] = random.nextInt(300) + 1;
      }
      return array;
   }

   public static void main(String[] args) {
      System.out.println(maxCakesAndStartingPosition(new int[]{10, 1}, 10));
      System.out.println(maxCakesAndStartingPosition(new int[]{1, 9, 8, 2, 5, 9, 9, 1, 5, 3, 1, 8}, 30));
      System.out.println(maxCakesAndStartingPosition(new int[]{2, 1, 2, 3, 2, 2, 1}, 6));
   }
}
