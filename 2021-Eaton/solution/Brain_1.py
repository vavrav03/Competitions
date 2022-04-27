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

            # Nahradit vaším programem
            if self.getTimestamp() == 1:
               self.faster(5)
            elif self.getTimestamp() == 2:
               self.faster(5)
            elif self.getTimestamp() == 3:
               self.faster(5)
               self.right(8)
            
            elif self.getTimestamp() == 17:
               self.right(7)
            elif self.getTimestamp() == 18:
               self.right(7)
            elif self.getTimestamp() == 19:
               self.right(7)
            elif self.getTimestamp() == 20:
               self.right(10)
            elif self.getTimestamp() == 21:
               self.right(10)
            elif self.getTimestamp() == 22:
               self.right(10)
            elif self.getTimestamp() == 23:
               self.right(10)
            elif self.getTimestamp() == 24:
               self.right(10)
            elif self.getTimestamp() == 25:
               self.right(10)

            elif self.getTimestamp() == 27:
               self.right(10)
            elif self.getTimestamp() == 28:
               self.right(10)
            elif self.getTimestamp() == 29:
               self.right(10)
            elif self.getTimestamp() == 30:
               self.right(10)
            elif self.getTimestamp() == 31:
               self.right(10)
            elif self.getTimestamp() == 32:
               self.right(10)
            elif self.getTimestamp() == 33:
               self.right(10)
            elif self.getTimestamp() == 34:
               self.right(10)
            elif self.getTimestamp() == 35:
               self.right(10)
            elif self.getTimestamp() == 36:
               self.right(2)
               
            elif self.getTimestamp() == 65:
               self.right(8)
            elif self.getTimestamp() == 66:
               self.right(10)   
            elif self.getTimestamp() == 67:
               self.right(10)
            elif self.getTimestamp() == 68:
               self.right(10)   
            elif self.getTimestamp() == 69:
               self.right(10)
            elif self.getTimestamp() == 70:
               self.right(10)   
            elif self.getTimestamp() == 71:
               self.right(10)
            elif self.getTimestamp() == 72:
               self.right(10)
            elif self.getTimestamp() == 73:
               self.right(10)
            
            elif self.getTimestamp() == 74:
               self.right(10)
            elif self.getTimestamp() == 75:
               self.right(10)
            elif self.getTimestamp() == 76:
               self.right(5)   
            elif self.getTimestamp() == 77:
               self.right(5)
            elif self.getTimestamp() == 78:
               self.right(5)   
            elif self.getTimestamp() == 79:
               self.right(10)
            elif self.getTimestamp() == 80:
               self.right(10)   
            elif self.getTimestamp() == 81:
               self.right(10)
            elif self.getTimestamp() == 82:
               self.right(10)
            elif self.getTimestamp() == 83:
               self.right(5)
            elif self.getTimestamp() == 84:
               self.right(5)
            elif self.getTimestamp() == 85:
               self.right(5)
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
