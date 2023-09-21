
import requests, json

# Define the URL you want to request
url = "http://127.0.0.1:8080/fwww/"


### create table
query_params = { "req": "create table if not exists vtab ( key: zid uuid, value: msg char(32) )" }
requests.get(url, params = query_params)

### insert data
query_params = { "req": "insert into vtab values ( 'hello world 1' )" } 
requests.get(url, params = query_params)

query_params = { "req": "insert into vtab values ( 'hello world 2' )" } 
requests.get(url, params = query_params)

query_params = { "request": "insert into vtab values ( 'hello world 3' )" } 
requests.get(url, params = query_params)

### select data
query_params = { "request": "select * from vtab" }
response = requests.get(url, params = query_params)

# Check if the request was successful (status code 200)
if response.status_code == 200:
    #print(response.text)
    json_data = json.loads(response.text)
    i = 0
    for irec in json_data:
        istr = str(i)
        recs = irec[istr]
        rec = json.loads( recs )
        print(f"zid: {rec[0]['zid']}")
        print(f"msg: {rec[1]['msg']}")
        i += 1
else:
    # Print an error message if the request was not successful
    print(f"Request failed with status code {response.status_code}")

