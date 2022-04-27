import time
import pygame
import math


class Brain:
   def __init__(self, database):
      self.database = database

   def run(self, cv=None, bcv=None):

      ######################################################################
      # ZAČÁTEK BLOKU
      # V tomto bloku můžete inicializovat proměnné mimo cyklus
      ######################################################################

      # my_amazing_var = 0
      # my_regular_var = 0

      ######################################################################
      # KONEC BLOKU
      ######################################################################

      while self.isRunning():
         with cv:
            cv.wait()

         '''
            1. Jak ovládat auto?

                Funkce pro zrychlení auta s volitelným parametrem "num".
                Num musí být v rozsahu 0-5. Pokud není "num" specifikován,
                použije se výchozí hodnota 5.

                self.faster(num)

                Funkce pro zpomalení auta s volitelným parametrem "num".
                Num musí být v rozsahu 0-5. Pokud není "num" specifikován,
                použije se výchozí hodnota 5.

                self.slower(num)

                Funkce pro zatočení doprava s volitelným parametrem "num".
                Num musí být v rozsahu 0-10. Pokud není "num" specifikován,
                použije se výchozí hodnota 10°.

                self.right(num)

                Funkce pro zatočení doleva s volitelným parametrem "num".
                Num musí být v rozsahu 0-10. Pokud není "num" specifikován,
                použije se výchozí hodnota 10°.

                self.left(num)


            2. Jak přistupovat k informacím o autě?

                Rychlost auta v rozsahu [0-15]:
                self.getCarSpeed()

                Data z lidaru na autě uložená v poli délky 180 prvků v rozsahu [0-300]:
                self.getLidarData()

                Natočení auta v rozsahu [0-360°]:
                self.getCarDirection()

                Souřadnice auta uložené ve struktuře tuple:
                self.getCarPosition()

            '''
         ####################################################################
         # ZAČÁTEK BLOKU
         # Zde implementujte váš algoritmus
         ####################################################################

         
         distribution = 0
         distanceSum = 0
         minDistance = 300
         for direction in range(0, 90):
            distribution += (90 - direction) * self.getLidarData()[direction]
            distanceSum += self.getLidarData()[direction]
            minDistance = min(minDistance, self.getLidarData()[direction])
         for direction in range(90, 180):
            distribution += -(direction - 90) * self.getLidarData()[direction]
            distanceSum += self.getLidarData()[direction]
            minDistance = min(minDistance, self.getLidarData()[direction])
         angleDifference = int(distribution / distanceSum)
         # distance slowing
         changeSpeed = 5
         if self.getLidarData()[90] < 100 and abs(angleDifference) > 9 and self.getCarSpeed() > 8:
            changeSpeed = -3
         elif self.getLidarData()[90] < 120 and abs(angleDifference) > 8 and self.getCarSpeed() > 9:
            changeSpeed = -2
         elif self.getLidarData()[90] < 140 and abs(angleDifference) > 7 and self.getCarSpeed() > 10:
            changeSpeed = -1

         realRotation = angleDifference
         if realRotation < -10:
            realRotation = -10
         elif realRotation > 10:
            realRotation = 10
         if angleDifference == 0 and self.getLidarData()[90] < 100: #2ways, cannot go forward
            realRotation = 10
         
         if realRotation > 0:
            if self.getLidarData()[10] < 35:
               print(self.getLidarData()[10])
               self.left(7)
            elif self.getLidarData()[10] < 40:
               print(self.getLidarData()[10])
               self.left(6)
            elif self.getLidarData()[10] < 45:
               print(self.getLidarData()[10])
               self.left(5)
            else:
               self.right(realRotation)
         else:
            if self.getLidarData()[170] < 35:
               print(self.getLidarData()[170])
               self.right(7)
            elif self.getLidarData()[170] < 40:
               print(self.getLidarData()[170])
               self.right(6)
            elif self.getLidarData()[170] < 45:
               print(self.getLidarData()[170])
               self.right(5)
            else:
               self.left(abs(realRotation))

         if changeSpeed < 0:
            self.slower(abs(changeSpeed))
         else:
            self.faster(changeSpeed)
         ####################################################################
         # KONEC BLOKU
         ####################################################################

         with bcv:
            bcv.notifyAll()

   ####################################################################
   # CAR CONTROL
   ####################################################################

   def faster(self, val: int = 5):
      self.database.control.faster(val)

   def slower(self, val: int = 5):
      self.database.control.slower(val)

   def right(self, val: int = 10):
      self.database.control.right(val)

   def left(self, val: int = 10):
      self.database.control.left(val)

   ####################################################################
   # CAR SENSORS
   ####################################################################
   def getCarPosition(self):
      return self.database.car.position

   def getCarSpeed(self):
      return self.database.car.speed

   def getCarDirection(self):
      return self.database.car.direction

   def getLidarData(self):
      return self.database.lidar.data

   ####################################################################
   # SIMULATION INFO
   ####################################################################
   def isRunning(self):
      return not self.database.stop

   def getTimestamp(self):
      return self.database.timestamp

   def getRunTime(self):
      return self.database.run_time

   def getRunDistance(self):
      return self.database.run_dist
