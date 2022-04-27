/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package P;

import java.util.Arrays;
import java.util.Random;

/**
 *
 * @author Vavra
 */
public class Uloha4 {

   static class Drive {

      private int[] drive;
      private int B;
      private int N;

      public Drive(int B, int[][] matrix) {
         this.drive = new int[100_000];
         this.N = matrix.length;
         for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix.length; j++) {
               drive[matrix.length * i + j] = matrix[i][j];
            }
         }
         System.out.println("");
         this.B = B;
      }

      public int[] read(int blockIndex) {
         int[] block = new int[B];
         for (int i = 0; i < B; i++) {
            block[i] = drive[i + blockIndex * B];
         }
         return block;
      }

      public void write(int blockIndex, int[] block) {
         for (int i = 0; i < B; i++) {
            drive[i + blockIndex * B] = block[i];
         }
      }

      public void printDrive() {
         for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
               System.out.print(drive[i * N + j] + " ");
            }
            System.out.println("");
         }
      }
   }

   private static void printMatrix(int[][] matrix) {
      for (int i = 0; i < matrix.length; i++) {
         for (int j = 0; j < matrix.length; j++) {
            System.out.print(matrix[i][j] + " ");
         }
         System.out.println("");
      }
   }

   private static int[][] createRandomMatrix(int N) {
      Random random = new Random();
      int[][] matrix = new int[N][N];
      for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
            matrix[i][j] = random.nextInt(9) + 1;
         }
      }
      return matrix;
   }

   public static void main(String[] args) {
      int B = 3;
      int N = 9;
      int[][] matrix = createRandomMatrix(N);
      Drive drive = new Drive(B, matrix);
      int M = 7;
      int[] block;
      drive.printDrive();
//      System.out.println(""); ALG 1
//      for(int i = 0; i < N; i++){
//         for(int j = 0; j < N/B; j++){
//            block = drive.read(i * N/B + j);
//            for(int x = 0; x < B; x++){
//               System.out.print(block[x] + " ");
//            }
//         }
//         System.out.println("");
//      }      
//      System.out.println("");

//      for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//            System.out.print(drive.read((j * N + i) / B)[i % B] + "");
//         }
//         System.out.println("");
//      }
//      int[] helpArray = new int[M - B];
//      for (int i = 0; i < N; i++) { //sloupec
//         for (int j = 0; j < N; j++) { //radek
//            block = drive.read((j * N + 1)/ B); //[i % B]
//         }
//         System.out.println("");
//      }
//      for (int i = 0; i < matrix.length / 2; i++) {
//         for (int j = i; j < matrix.length - i - 1; j++) {
//            temp = matrix[i][j];
//            matrix[i][j] = matrix[matrix.length - 1 - j][i];
//            matrix[matrix.length - 1 - j][i] = matrix[matrix.length - 1 - i][matrix.length - 1 - j];
//            matrix[matrix.length - 1 - i][matrix.length - 1 - j] = matrix[j][matrix.length - 1 - i];
//            matrix[j][matrix.length - 1 - i] = temp;
//         }
//      }      
      int[][] memory = new int[B][B];
      for (int i = 0; i < N / B / 2; i++) { //radek B^2 bloku
         for (int j = i; j < N / B - i - 1; j++) { //sloupec B^2 bloku
            readBlockOfBlocks(i, j, N, B, memory, drive);
            rotateInnerBlock(B, memory);
            for (int x = 0; x < B; x++) {
               drive.write(N * N / B + x, memory[x]);
            }

            readBlockOfBlocks(N / B - 1 - j, i, N, B, memory, drive);
            rotateInnerBlock(B, memory);
            writeBlockOfBlocks(i, j, N, B, memory, drive);

            readBlockOfBlocks(N / B - 1 - i, N / B - 1 - j, N, B, memory, drive);
            rotateInnerBlock(B, memory);
            writeBlockOfBlocks(N / B - 1 - j, i, N, B, memory, drive);

            readBlockOfBlocks(j, N / B - 1 - i, N, B, memory, drive);
            rotateInnerBlock(B, memory);
            writeBlockOfBlocks(N / B - 1 - i, N / B - 1 - j, N, B, memory, drive);

            for (int x = 0; x < B; x++) {
               memory[x] = drive.read(N * N / B + x);
            }
            writeBlockOfBlocks(j, N / B - 1 - i, N, B, memory, drive);

         }
      }
      if(N / B % 2 == 1){
         readBlockOfBlocks(N / B / 2, N / B / 2, N, B, memory, drive);
         rotateInnerBlock(B, memory);
         writeBlockOfBlocks(N / B / 2, N / B / 2, N, B, memory, drive);
      }
//      drive.printDrive();
   }

   public static void rotateInnerBlock(int B, int[][] memory) {
      int temp;
      for (int r = 0; r < B / 2; r++) {
         for (int q = r; q < B - r - 1; q++) {
            temp = memory[r][q];
            memory[r][q] = memory[B - 1 - q][r];
            memory[B - 1 - q][r] = memory[B - 1 - r][B - 1 - q];
            memory[B - 1 - r][B - 1 - q] = memory[q][B - 1 - r];
            memory[q][B - 1 - r] = temp;
         }
      }
   }

   public static void readBlockOfBlocks(int i, int j, int N, int B, int[][] memory, Drive drive) {
//      System.out.print("i=" + i + ", j=" + j + ": ");
      for (int x = 0; x < B; x++) { //radek B bloku v B^2 bloku
//         System.out.print(getDriveIndex(i, j, N, B, x) + " ");
         memory[x] = drive.read(getDriveIndex(i, j, N, B, x));
      }
//      System.out.println("");
   }

   public static void writeBlockOfBlocks(int i, int j, int N, int B, int[][] memory, Drive drive) {
      for (int x = 0; x < B; x++) { //radek B bloku v B^2 bloku
         drive.write(getDriveIndex(i, j, N, B, x), memory[x]);
      }
   }

   public static int getDriveIndex(int i, int j, int N, int B, int x) {
      return j + (B * i + x) * N / B;
   }
}
