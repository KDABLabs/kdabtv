import xmlrpc.client
session = xmlrpc.client.ServerProxy('http://localhost:9000')


# By ID
session.MouseClick('mainWindow/rowLayout/userField', 'christoph')
session.MouseClick('mainWindow/userField', 'christoph')

# New Changes in Spix make this possible ↓↓↓
# By displayed Text
session.MouseClick('mainWindow/"Cancel"')
session.MouseClick('mainWindow/Dialog/"Cancel"')

# By Child index
session.MouseClick('mainWindow/Rectangle#2')

# By Properties
session.MouseClick('mainWindow/color="#00ff00"')
session.MouseClick('mainWindow/width=100')


