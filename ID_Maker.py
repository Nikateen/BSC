from bs4 import BeautifulSoup
import requests
import os
from pathlib import Path

z=Path()
currentWorkingDirectory = Path(str(z.resolve()))  
inputFile = currentWorkingDirectory / "jerry.txt"

def cls():
    os.system('cls' if os.name == 'nt' else 'clear')

def soup_cleaner(s):
    s = s.replace(
        '<?xml version="1.0" encoding="utf-8" ?><html><body><transcript>', ''
        )
    s = s.replace("\n"," ",-1)
    s = s.replace('">',' ">',-1)
    s = s.replace("."," ",-1)
    s = s.replace("?"," ",-1)
    s = s.replace(","," ",-1)
    s = s.replace("!"," ",-1)

    s = s.replace('</transcript></body></html>', '')
    s = s.replace("&amp;#39;", "'", -1)
    s = s.replace("</text>", "</text>\n", -1)
    s = s.lower()

    return s

def Writer(x):
    x=x[:-1] #removing trailing \n
    url = ("http://video.google.com/timedtext?lang=en&v=%s" % (x))
    HEADERS = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_1) '
        'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.110'
        'Safari/537.36'
        }
    response = requests.get(url, headers=HEADERS)
    soup = BeautifulSoup(response.text, 'lxml')
    soup = soup_cleaner(str(soup))

    ID = currentWorkingDirectory / "IDs" / ("%s.txt" % x)
    with ID.open("w+") as f:
        f.write(str(soup))
        f.close()



#----------------------------------------------------------------------------
if not Path.exists(currentWorkingDirectory / "IDs"):
    x = currentWorkingDirectory / "IDs"
    x.mkdir()
    # '/IDs'
else:
    pass

ID_List=[]
with inputFile.open("r") as f:
    ID_List=f.readlines()
    f.close()


COUNT=1
NUM_OF_VID = len(ID_List)

for ID in ID_List:
    Writer(ID)
    cls()
    print(
        str(COUNT) + " of " + str(NUM_OF_VID) +
        " videos converted into word lists.")
    COUNT +=1