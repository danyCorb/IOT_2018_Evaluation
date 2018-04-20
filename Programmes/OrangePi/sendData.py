import requests
import json
import serial
from datetime import datetime
import time

# fonction d'envoie des data vers mblab
def sendDataToDB(temperture, idRaspberry, date):
  url = 'https://api.mlab.com/api/1/databases/testiot/collections/test?apiKey=vWIzv7LA8PHHlJvAIfFUcze6O0FubFEF'
  data = {'idRaspberry': idRaspberry, 'temperature': temperture, 'date': date}
  headers = {'content-type': 'application/json'}
  response = requests.post(url, data=json.dumps(data), headers=headers)
  return response.text

# fonction temporaire en attendant celle de Pierre
def getData():
  donnee = str(ser.readline())
  donnee = donnee.replace("\n","")
  tab = donnee.split(" ")
  tab.append(str(datetime.now()))
  return tab

# fonction de triage des donnees et envoi vers la DB
def sendData(dataTab):
  for data in dataTab:
    sendDataToDB(data[0], data[1],data[2])
  return

# debut programme
tabData = []
start = time.time()
ser = serial.Serial('/dev/ttyACM0', 9600)

# boucle principale
while 1 == 1:
  # toute les 5 minutes
  if time.time() - start > (60*5):
    sendData(tabData)
    start = time.time()
    tabData = []
  # toute les 100 milisec
  time.sleep(0.1)
  tabData.append(getData())

