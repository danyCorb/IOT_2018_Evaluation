import requests
import json
from datetime import datetime
import time

# fonction d'envoie des data vers mblab
def sendDataToDB(temperture, idRaspberry):
  date = str(datetime.now())
  url = 'https://api.mlab.com/api/1/databases/testiot/collections/test?apiKey=vWIzv7LA8PHHlJvAIfFUcze6O0FubFEF'
  data = {'idRaspberry': idRaspberry, 'temperature': temperture, 'date': date}
  headers = {'content-type': 'application/json'}
  response = requests.post(url, data=json.dumps(data), headers=headers)
  return response.text

# fonction temporaire en attendant celle de Pierre
def getData():
  tab = []
  tab.append(12)
  tab.append(1)
  return tab

# fonction de triage des données et envoi vers la DB
def sendData(dataTab):
  for data in dataTab:
    sendDataToDB(data[0], data[1])
  return

# debut programme
tabData = []
start = time.time()

# boucle principale
while 1 == 1:
  # toute les 5 minutes
  if time.time() - start > 300:
    sendData(tabData)
    start = time.time()
    tabData = []
  # toute les 100 milisec
  time.sleep(0.1)
  tabData.append(getData())
