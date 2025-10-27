import xmlrpc.client
import time 

session = xmlrpc.client.ServerProxy('http://localhost:9000')

session.inputText('mainWindow/userField', 'christoph')
session.inputText('mainWindow/passwordField', 'secret') 
session.mouseClick('mainWindow/"Login"')

time.sleep(0.200)
session.takeScreenshot('mainWindow', '/tmp/screenshot.png')
